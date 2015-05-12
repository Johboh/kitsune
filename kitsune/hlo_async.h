#ifndef HLO_ASYNC_H
#define HLO_ASYNC_H
#include "FreeRTOS.h"
#include "semphr.h"
/**
 * tools for asynchronous transaction here
 */

typedef struct{
	int error;
	void * buf;
	int buf_size;
	xSemaphoreHandle sync;
}hlo_future_t;

hlo_future_t * hlo_future_create(size_t max_size);

//producer use either
int hlo_future_write(hlo_future_t * future, const void * buffer, size_t size, int opt_error);

int hlo_future_read(hlo_future_t * future, void * buf, size_t size);
//or this
int hlo_future_read_with_timeout(hlo_future_t * future,  void * buf, size_t size, int ms);



#endif
