#ifndef LED_ANIMATIONS_H
#define LED_ANIMATIONS_H

#include "stdbool.h"
#include "led_cmd.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_led_animation();

//call to stop all animations
void stop_led_animation(unsigned int delay);
int Cmd_led_animate(int argc, char *argv[]);

//custom animations
bool play_led_trippy(uint8_t trippy_base[3], uint8_t range[3], unsigned int timeout);
bool play_led_progress_bar(int r, int g, int b, unsigned int options, unsigned int timeout);
bool play_led_animation_solid(int r, int g, int b);
void set_led_progress_bar(uint8_t percent);
bool factory_led_test_pattern(unsigned int timeout);
bool play_led_animation_stop(void);

/*
 * this macro invokes one of the play_led_* animation
 * and blocks until either a higher animation overwrites it, or the animation ends by itself.
 */
#define ANIMATE_BLOCKING(anim, timeout) do{\
	int ret = anim;\
	while(ret >= 0 && timeout){\
		if(led_wait_for_idle(0) || ret != led_get_animation_id()){\
			break;\
		}else{\
			timeout--;\
			vTaskDelay(1);\
		}\
	}\
}while(0)
#ifdef __cplusplus
}
#endif
#endif
