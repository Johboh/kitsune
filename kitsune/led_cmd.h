#ifndef LED_CMD_H
#define LED_CMD_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#define NUM_LED 12
#define LED_MAX 254

typedef struct{
	unsigned int rgb;
}led_color_t;

void led_to_rgb(const led_color_t * c, unsigned int *r, unsigned int* g, unsigned int* b);
led_color_t led_from_rgb( int r, int g, int b);
void led_set(led_color_t * dst, led_color_t src, int num);
void led_copy(led_color_t * dst, const led_color_t * src, int num);

typedef bool (*led_user_animation_handler)(led_color_t * out, int * out_delay, void * user_context, int rgb_array_size);
typedef struct{
	led_user_animation_handler handler;
	void * context;
	uint8_t priority;
	led_color_t initial_state[NUM_LED];
}user_animation_t;

int Cmd_led_clr(int argc, char *argv[]);
int Cmd_led(int argc, char *argv[]);
int led_init(void);

void led_idle_task( void * params );
void led_task( void * params );

//helper api

int led_set_color(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b, int fade_in, int fade_out, unsigned int ud, int rot);
/**
 * returns -1 if error, else animation id
 */
int led_transition_custom_animation(const user_animation_t * user);
int led_get_animation_id(void);

void led_get_user_color(uint8_t* out_red, uint8_t* out_green, uint8_t* out_blue);
void led_set_user_color(uint8_t red, uint8_t green, uint8_t blue);
int led_set_color(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b,
		int fade_in, int fade_out,
		unsigned int ud,
		int rot);
int led_ready();
bool led_wait_for_idle(unsigned int wait);
unsigned int led_delay( unsigned int dly );

#ifdef __cplusplus
}
#endif
#endif
