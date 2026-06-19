#include "eventQueue.h"

#define MAX_QUEUE_SIZE 8

static SystemEvent_t queue[MAX_QUEUE_SIZE];
static uint8_t head;
static uint8_t tail;
static uint8_t count;
static uint8_t overflowFlag;
static uint32_t overflowCount;

void eventQueue_init() {

	head = 0u;

	tail = 0u;

	count = 0u;

	overflowFlag = 0u;

	overflowCount = 0u;

}

uint8_t eventQueue_push(SystemEvent_t event) {

	uint8_t pushDone = 1u;

	if (count >= MAX_QUEUE_SIZE) {
	
		overflowFlag = 1u;

		overflowCount++;

		pushDone = 0u;

	}
	else {
	
		queue[tail] = event;

		count++;

		tail = (uint8_t)(tail + 1u) % MAX_QUEUE_SIZE;

	}

	return pushDone;


}

uint8_t eventQueue_pop(SystemEvent_t* event) {

	uint8_t popOk = 0u;

	if (count > 0) {
	
		*event = queue[head];

		count--;

		head = (uint8_t)(head + 1u) % MAX_QUEUE_SIZE;
	
		popOk = 1u;

	}
	
	return popOk;

}

uint8_t eventQueue_consumeOverflowFlag() {

	uint8_t flag = overflowFlag;

	overflowFlag = 0u;

	return flag;

}

uint8_t eventQueue_getOverflow() {

	return overflowCount;

}