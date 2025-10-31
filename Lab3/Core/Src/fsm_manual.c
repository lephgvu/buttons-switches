/*
 * fsm_manual.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Admin
 */
#include "fsm_manual.h"

int red_tmp_duration = 0, yellow_tmp_duration = 0, green_tmp_duration = 0;

void fsm_manual_run(){
	switch (status){
		case RED_MODE:
			if (isTimerExpired(LED_CHANGE)) {
				blinkLEDs(RED);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(0)){
				if (red_tmp_duration == 0) red_tmp_duration = red_duration;
				clearAllLEDs();
				status = YELLOW_MODE;
				update7SegBuffer(yellow_sec, 3);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(1)){
				red_sec++;
				if (red_sec >= 100) red_sec = 1;
				update7SegBuffer(red_sec, 2);
			}
			if (isButtonPressed(2)){
				red_tmp_duration = red_sec * 100;
			}
			break;

		case YELLOW_MODE:
			if (isTimerExpired(LED_CHANGE)) {
				blinkLEDs(YELLOW);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(0)){
				if (yellow_tmp_duration == 0) yellow_tmp_duration = yellow_duration;
				clearAllLEDs();
				status = GREEN_MODE;
				update7SegBuffer(green_sec, 4);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(1)){
				yellow_sec++;
				if (yellow_sec >= 100) yellow_sec = 1;
				update7SegBuffer(yellow_sec, 3);
			}
			if (isButtonPressed(2)){
				yellow_tmp_duration = yellow_sec * 100;
			}
			break;

		case GREEN_MODE:
			if (isTimerExpired(LED_CHANGE)) {
				blinkLEDs(GREEN);
				setTimer(LED_CHANGE, 50);
			}
			if (isButtonPressed(1)){
				green_sec++;
				if (green_sec >= 100) green_sec = 1;
				update7SegBuffer(green_sec, 4);
			}
			if (isButtonPressed(2)){
				green_tmp_duration = green_sec * 100;
			}
			if (isButtonPressed(0)){
				if (green_tmp_duration == 0) green_tmp_duration = green_duration;
				clearAllLEDs();
				if ((green_tmp_duration + yellow_tmp_duration) == red_tmp_duration){
					red_duration = red_tmp_duration;
					yellow_duration = yellow_tmp_duration;
					green_duration = green_tmp_duration;
				}
				red_tmp_duration = yellow_tmp_duration = green_tmp_duration = 0;
				red_sec = red_duration/100;
				yellow_sec = yellow_duration/100;
				green_sec = green_duration/100;
				update7SegBuffer(red_sec, green_sec);
				status = RED_GREEN;
				setTimer(LED_CHANGE, green_duration);
				setTimer(COUNTDOWN_TIMER, 100);
			}
			break;

		default:
			break;
	}
}
