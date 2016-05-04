#include "hlo_audio_tools.h"
#include "hlo_audio_manager.h"
#include "task.h"
#include "kit_assert.h"
#include "hellofilesystem.h"
#include "hlo_pipe.h"
#include "octogram.h"
#include "audio_types.h"
#include "audiofeatures.h"
#include "hlo_async.h"
#include <stdbool.h>

////-------------------------------------------
//recorder sample app
#define CHUNK_SIZE 1024
int audio_sig_stop = 0;
void hlo_audio_recorder_task(void * data){
	int ret;
	uint8_t chunk[CHUNK_SIZE];
	hlo_stream_t *fs, * mic;
	mic = hlo_open_mic_stream(0);
	fs = fs_stream_open_wlimit((char*)data, 48000 * 6); //max six seconds of audio

	while( (ret = hlo_stream_transfer_between(mic,fs,chunk, sizeof(chunk),4)) > 0){
		if(audio_sig_stop){
			break;
		}
	}

	hlo_stream_close(fs);
	hlo_stream_close(mic);
	DISP("Recorder Task Finished %d\r\n", ret);
}
typedef struct{
	unsigned long current;
	unsigned long target;
	unsigned long ramp_up_ms;
	unsigned long ramp_down_ms;
}ramp_ctx_t;
/**
 * this task is responsible for gradually changing the volume until target == 0
 */
extern xSemaphoreHandle i2c_smphr;
extern bool set_volume(int v, unsigned int dly);

static void _change_volume_task(hlo_future_t * result, void * ctx){
	volatile ramp_ctx_t * v = (ramp_ctx_t*)ctx;
	while( v->target || v->current ){
		if(v->current > v->target){
			vTaskDelay(v->ramp_down_ms);
			v->current--;
		}else if(v->current < v->target){
			v->current++;
			vTaskDelay(v->ramp_up_ms);
		}else{
			vTaskDelay(10);
			continue;
		}
		//fallthrough if volume adjust is needed
		LOGI("Setting volume %u at %u\n", v->current, xTaskGetTickCount());
		if( xSemaphoreTakeRecursive(i2c_smphr, 100)) {
			//set vol
			vTaskDelay(5);
			set_volume(v->current, 0);
			vTaskDelay(5);
			xSemaphoreGiveRecursive(i2c_smphr);

		}else{
			//set volume failed, instantly exit out of this async worker.
			hlo_future_write(result, NULL, 0, -1);
		}

	}
	hlo_future_write(result, NULL, 0, 0);
}
////-------------------------------------------
//playback sample app
void hlo_audio_playback_task(AudioPlaybackDesc_t * desc){
	int ret;
	uint8_t chunk[CHUNK_SIZE];

	if(!desc || !desc->stream){
		return;
	}
	portTickType end = xTaskGetTickCount() + desc->durationInSeconds * 1000;
	ramp_ctx_t vol;
	vol.current = 0;
	vol.target = desc->volume;
	vol.ramp_up_ms = desc->fade_in_ms / (desc->volume + 1);
	vol.ramp_down_ms = desc->fade_out_ms / (desc->volume + 1);

	hlo_stream_t * spkr = hlo_open_spkr_stream(2*CHUNK_SIZE);
	hlo_stream_t * fs = desc->stream;

	hlo_future_t * vol_task = (hlo_future_t*)hlo_future_create_task_bg(_change_volume_task,(void*)&vol,1024);

	while( (ret = hlo_stream_transfer_between(fs,spkr,chunk, sizeof(chunk),2)) > 0){
		if(audio_sig_stop || xTaskGetTickCount() >= end){
			//signal ramp down
			vol.target = 0;
		}
		if(hlo_future_read(vol_task,NULL,0,0) >= 0){
			//future task has completed
			break;
		}
	}
	audio_sig_stop = 0;
	vol.target = 0;
	hlo_future_destroy(vol_task);
	hlo_stream_close(fs);
	hlo_stream_close(spkr);
	if(desc->onFinished){
		desc->onFinished(desc->context);
	}
	DISP("Playback Task Finished %d\r\n", ret);

}
////-------------------------------------------
//octogram sample app
#define PROCESSOR_BUFFER_SIZE ((AUDIO_FFT_SIZE)*3*2)
#define OCTOGRAM_DURATION 500
void hlo_audio_octogram_task(void * data){
	Octogram_t octogramdata = {0};
	int ret,i;
	int32_t duration = 500;
	Octogram_Init(&octogramdata);
	OctogramResult_t result;
	int16_t * samples = pvPortMalloc(PROCESSOR_BUFFER_SIZE);
	hlo_stream_t * input = (hlo_stream_t*)data;//hlo_open_mic_stream(CHUNK_SIZE*2, 1);
	if(!samples){
		goto exit;
	}
	while( (ret = hlo_stream_transfer_all(FROM_STREAM,input,(uint8_t*)samples,PROCESSOR_BUFFER_SIZE,4)) > 0){
		//convert from 48K to 16K
		for(i = 0; i < 256; i++){
			int32_t sum = samples[i] + samples[AUDIO_FFT_SIZE+i] + samples[(2*AUDIO_FFT_SIZE)+i];
			samples[i] = (int16_t)(sum / 3);
		}
		Octogram_Update(&octogramdata,samples);
		DISP(".");
		if(duration-- < 0){
			DISP("\r\n");
			Octogram_GetResult(&octogramdata, &result);
			LOGF("octogram log energies: ");
			for (i = 0; i < OCTOGRAM_SIZE; i++) {
				if (i != 0) {
					LOGF(",");
				}
				LOGF("%d",result.logenergy[i]);
			}
			LOGF("\r\n");
			break;
		}
	}
	vPortFree(samples);
exit:
	DISP("Octogram Task Finished %d\r\n", ret);
	hlo_stream_close(input);
}
////-------------------------------------------
//feature xtraction sample app

static int64_t _callCounter;
static void DataCallback(const AudioFeatures_t * pfeats) {
	//AudioProcessingTask_AddFeaturesToQueue(pfeats);
	//DISP("audio feature: logEg: %d, overbg: %dr\n", pfeats->logenergy, pfeats->logenergyOverBackroundNoise);
}
static void StatsCallback(const AudioOncePerMinuteData_t * pdata) {
	LOGI("audio disturbance: background=%d, peak=%d\n",pdata->peak_background_energy,pdata->peak_energy);
}

void hlo_audio_feature_extraction_task(void * data){
	hlo_stream_t * input = (hlo_stream_t*)data;
	AudioFeatures_Init(DataCallback,StatsCallback);
	int16_t * samples = pvPortMalloc(PROCESSOR_BUFFER_SIZE);
	int i,ret;
	if(!samples){
		goto exit;
	}
	while( (ret = hlo_stream_transfer_all(FROM_STREAM,input,(uint8_t*)samples,PROCESSOR_BUFFER_SIZE,4)) > 0){
		for(i = 0; i < 256; i++){
			int32_t sum = samples[i] + samples[AUDIO_FFT_SIZE+i] + samples[(2*AUDIO_FFT_SIZE)+i];
			samples[i] = (int16_t)(sum / 3);
		}
		AudioFeatures_SetAudioData(samples,_callCounter++);
		if(audio_sig_stop){
			break;
		}
	}
	vPortFree(samples);
exit:
	DISP("Audio Feature Task Finished %d\r\n", ret);
	hlo_stream_close(input);

}
////-----------------------------------------
//commands
extern hlo_stream_t * open_stream_from_path(char * str, uint8_t input);
int Cmd_audio_record_start(int argc, char *argv[]){
	audio_sig_stop = 0;
	hlo_audio_recorder_task("rec.raw");
	return 0;
}
int Cmd_audio_record_stop(int argc, char *argv[]){
	audio_sig_stop = 1;
	return 0;

}
int Cmd_audio_record_replay(int argc, char *argv[]){
	DISP("Playing back %s ...\r\n", argv[1]);
	AudioPlaybackDesc_t desc;
	desc.durationInSeconds = 10;
	desc.fade_in_ms = 1000;
	desc.fade_out_ms = 1000;
	desc.stream = fs_stream_open_media(argv[1],0);
	desc.volume = 50;
	desc.onFinished = NULL;
	audio_sig_stop = 0;
	hlo_audio_playback_task(&desc);
	return 0;
}
int Cmd_audio_octogram(int argc, char *argv[]){
	audio_sig_stop = 0;
	//hlo_app_audio_octogram_task(random_stream_open());

	hlo_audio_octogram_task(open_stream_from_path(argv[1],2));
	return 0;
}
int Cmd_audio_features(int argc, char *argv[]){
	audio_sig_stop = 0;
	hlo_audio_feature_extraction_task(open_stream_from_path(argv[1],1));
	return 0;
}

