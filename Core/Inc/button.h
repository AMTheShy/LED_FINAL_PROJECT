#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

typedef struct {

	uint8_t rawPressed;

	uint8_t stablePressed;

	uint8_t lastStablePressed;

	uint8_t stuckFaultDetected;

	uint32_t shortPressCount;

	uint32_t longPressCount;

}Button_Status_t;


void Button_init();
void Button_update();
Button_Status Button_getStatus();
#endif 
