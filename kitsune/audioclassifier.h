#ifndef _AUDIOCLASSIFIER_H_
#define _AUDIOCLASSIFIER_H_

#include "audio_types.h"
#include <pb.h>

#ifdef __cplusplus
extern "C" {
#endif

void AudioClassifier_Init(SegmentAndFeatureCallback_t fpNovelFeatureCallback);

uint32_t AudioClassifier_GetSerializedBuffer(pb_ostream_t * stream,const char * macbytes, uint32_t unix_time,const char * tags, const char * source);

void AudioClassifier_SegmentCallback(const int16_t * feats, const Segment_t * pSegment);
 
#ifdef __cplusplus
}
#endif


#endif

