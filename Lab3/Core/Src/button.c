/*
 * button.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Admin
 */
#include "global.h"

int buttonFlag[NUM_OF_BUTTON] = {0};
int TimerForKeyPress[NUM_OF_BUTTON] = {0};
GPIO_PinState buttonBuffer[NUM_OF_BUTTON] = {RELEASED};


GPIO_PinState debounceBuffer_1[NUM_OF_BUTTON] = {RELEASED};
GPIO_PinState debounceBuffer_2[NUM_OF_BUTTON] = {RELEASED};
GPIO_PinState debounceBuffer_3[NUM_OF_BUTTON] = {RELEASED};

GPIO_TypeDef* buttonPort[NUM_OF_BUTTON] = {BTN1_GPIO_Port,
										   BTN2_GPIO_Port,
										   BTN3_GPIO_Port};

uint16_t buttonPin[NUM_OF_BUTTON] = {BTN1_Pin,
								     BTN2_Pin,
									 BTN3_Pin};

void getKeyInput(){
	for (int i=0; i < NUM_OF_BUTTON; i++){
		debounceBuffer_1[i] = debounceBuffer_2[i];
		debounceBuffer_2[i] = debounceBuffer_3[i];
		debounceBuffer_3[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
		if ((debounceBuffer_1[i] == debounceBuffer_2[i]) && (debounceBuffer_2[i] == debounceBuffer_3[i])){
			if (buttonBuffer[i] != debounceBuffer_3[i]){
				buttonBuffer[i] = debounceBuffer_3[i];
				if (buttonBuffer[i] == PRESSED){
					buttonFlag[i] = 1;
					TimerForKeyPress[i] = 100;
				}
			}
			else{
				TimerForKeyPress[i]--;
				if (TimerForKeyPress[i] <= 0)
					buttonBuffer[i] = RELEASED;
			}
		}
	}
}

int isButtonPressed(int index){
	if (index >= NUM_OF_BUTTON)
		return 0;

	if (buttonFlag[index] == 1) {
		buttonFlag[index] = 0;
		return 1;
	}
	return 0;
}


