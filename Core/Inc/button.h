#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "systemEvent.h"

typedef struct {

	uint8_t rawPressed;

	uint8_t stablePressed;

	uint8_t lastStablePressed;

	uint8_t stuckFaultDetected;

	uint32_t shortPressCount;

	uint32_t longPressCount;

}Button_Status_t;

static void Button_pushEvent(SystemEventType_t eventType);
static void Button_pushFault(FaultCode_t fault);
static uint8_t button_readRawInput();
static void Button_debounce();
void Button_init();
void Button_update();
Button_Status_t Button_getStatus();
#endif 
