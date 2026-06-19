#include "main.h"
#include "systemEvent.h"
#include "softwareTimer.h"
#include "button.h"




#define BUTTON_DEBOUNCE_MS 30u
#define BUTTON_LONGCLICK_MS 2000u
#define BUTTON_STUCK_MS  10000u

static Button_Status_t buttonStatus;

static SoftwareTimer_t debounceTimer;
static SoftwareTimer_t longClickTimer;
static SoftwareTimer_t stuckTimer;

static uint8_t candidatePress;
static uint8_t debounceDone;
static uint8_t longClickFired;
static uint8_t stuckCheckFired;

static uint8_t button_readRawInput() {

	GPIO_PinState rawInput = HAL_GPIO_ReadPin(User_Button_GPIO_Port_Number, User_Button_GPIO_Pin_Number);

	return (rawInput == GPIO_PIN_SET) ? 0U : 1U;

}

static void button_init() {

	buttonStatus.rawPressed = button_readRawInput();

	buttonStatus.stablePressed = buttonStatus.rawPressed;

	buttonStatus.lastStablePressed = 0u;

	buttonStatus.stuckFaultDetected = 0u;

	buttonStatus.shortPressCount = 0u;

	buttonStatus.longPressCount = 0u;

	candidatPress = buttonStatus.stablePressed;

	debounceDone = 0u;

	longClickFired = 0u;

	stuckCheckFired = 0u;
	
	SoftwareTimer_Stop(&debounceTimer);
	SoftwareTimer_Stop(&longPressTimer);
	SoftwareTimer_Stop(&stuckTimer);

	if (buttonStatus.stablePressed != 0U)
	{
		SoftwareTimer_Start(&longPressTimer, BUTTON_LONG_PRESS_MS);

		SoftwareTimer_Start(&stuckTimer, BUTTON_STUCK_TIME_MS);

	}

}

static void button_debounce() {

	 uint8_t rawPress = button_readRawInput();

	 buttonStatus.rawPressed = rawPress;

	 if (buttonStatus.stablePressed != buttonStatus.rawPressed && candidatePress != buttonStatus.rawPressed) {
		
		 candidatePress = buttonStatus.rawPressed;
		 
		 SoftwareTimer_Start(&debounceTimer, BUTTON_DEBOUNCE_MS);
	 }

	 if (SoftwareTimer_IsExpired(&debounceTimer)) {

		 buttonStatus.lastStablePressed = buttonStatus.stablePressed;

		 buttonStatus.stablePressed = candidatePress;

		 debounceDone = 1u;

		 SoftwareTimer_Stop(&debounceTimer);

	 }else if (buttonStatus.rawPressed == buttonStatus.stablePressed) {
	 
		 candidatePress = buttonStatus.stablePressed;

		 SoftwareTimer_Stop(&debounceTimer);
			
	 }

}

static void button_update() {

	button_debounce();

	if (debounceDone) {
		
		if (buttonStatus.lastStablePressed == 0u && buttonStatus.stablePressed == 1u) {

			if (!SoftwareTimer_IsRunning(&longClickTimer) && !SoftwareTimer_IsRunning(&stuckTimer)) {
			
				SoftwareTimer_Start(&longClickTimer, BUTTON_LONGCLICK_MS);

				SoftwareTimer_Start(&stuckTimer, BUTTON_STUCK_MS);

			}	
		
			longClickFired = 1u

			stuckCheckFired = 1u;

			debounceDone = 0u;

		}

		if (buttonStatus.lastStablePressed == 1u && buttonStatus.stablePressed == 0u) {
		

			if (longClickFired && !SoftwareTimer_IsExpired(&longClickTimer)) {
			
				longClickFired = 0u;

				stuckCheckFired = 0u;

				debounceDone = 0u;

				SoftwareTimer_Stop(&longClickTimer);

				buttonStatus.shortPressCount++;

				//return event shortClick
			
			}
		
		}

	}

	if (longClickFired && SoftwareTimer_IsExpired(&longClickTimer)) {

		longClickFired = 0u;

		SoftwareTimer_Stop(&longClickTimer);

		buttonStatus.longPressCount++;

		//return event longclick

	}

	if (stuckCheckFired && buttonStatus.stablePressed && SoftwareTimer_IsExpired(&stuckTimer) ) {

		stuckCheckFired = 0u;

		SoftwareTimer_Stop(&stuckTimer);

		//return fault stuck

	}

}