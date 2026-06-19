#ifndef EVENTQUEUE.H
#define EVENTQUEUE.H

#include <stdint.h>
#include <systemEvent.h>

void eventQueue_init(void);
uint8_t eventQueue_push(SystemEvent_t event);
uint8_t eventQueue_pop(SystemEvent_t* event);
uint8_t eventQueue_consumeOverflowFlag(void);
uint8_t eventQueue_getOverflow(void);


#endif

