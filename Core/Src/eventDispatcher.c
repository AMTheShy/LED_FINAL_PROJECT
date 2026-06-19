#include "eventDispatcher.h"
#include "eventQueue.h"
#include <stdint.h>
#include "systemEvent.h"
#include "app.h"

void eventDispatcher_update() {

	SystemEvent_t currentEvent;

	if (eventQueue_consumeOverflowFlag()) {

		SystemEvent_t faultEvent = {

			.type = SYSTEM_EVENT_FAULT_DETECTED,

			.fault = FAULT_EVENT_QUEUE_OVERFLOW.

			.source = FAULT_SOURCE_EVENT_QUEUE;

		};

		//app_handle(faultEvent);

	}

	while (eventQueue_pop(&currentEvent)) {
	
		//app_handleEvent(currentEvent);

	}

}
