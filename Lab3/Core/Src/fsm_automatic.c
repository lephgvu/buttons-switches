/*
 * fsm_automatic.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Admin
 */
#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch (status){
	case INIT:
		clearAllLEDs();
		clearENs();
		clear7SEG();
		red_sec = red_duration/100;
		yellow_sec = yellow_duration/100;
		green_sec = green_duration/100;

		if (isButtonPressed(0)){
			setTimer(LED_CHANGE, green_duration);
			setTimer(COUNTDOWN_TIMER, 100);
			update7SegBuffer(red_sec, green_sec);
			status = RED_GREEN;
		}
		break;

	case RED_GREEN:
		setLEDs(RED_GREEN);
		countdownUpdate(&red_sec, &green_sec);

		if (isTimerExpired(LED_CHANGE)){
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update7SegBuffer(red_sec, yellow_sec);
			status = RED_YELLOW;
			setTimer(LED_CHANGE, yellow_duration);
		}
		modeChangeCheck();
		break;

	case RED_YELLOW:
		setLEDs(RED_YELLOW);
		countdownUpdate(&red_sec, &yellow_sec);

		if (isTimerExpired(LED_CHANGE)){
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update7SegBuffer(green_sec, red_sec);
			status = GREEN_RED;
			setTimer(LED_CHANGE, green_duration);
		}
		modeChangeCheck();
		break;

	case GREEN_RED:
		setLEDs(GREEN_RED);
		countdownUpdate(&green_sec, &red_sec);

		if (isTimerExpired(LED_CHANGE)){
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update7SegBuffer(yellow_sec, red_sec);
			status = YELLOW_RED;
			setTimer(LED_CHANGE, yellow_duration);
		}
		modeChangeCheck();
		break;

	case YELLOW_RED:
		setLEDs(YELLOW_RED);
		countdownUpdate(&yellow_sec, &red_sec);
		resetCountdown();
		if (isTimerExpired(LED_CHANGE)){
			resetCountdown();
			setTimer(COUNTDOWN_TIMER, 100);
			update7SegBuffer(red_sec, green_sec);
			status = RED_GREEN;
			setTimer(LED_CHANGE, green_duration);
		}
		modeChangeCheck();
		break;

	default:
		break;
	}
}

void modeChangeCheck(){
	if (isButtonPressed(0)){
		clearAllLEDs();
		red_sec = red_duration/100;
		yellow_sec = yellow_duration/100;
		green_sec = green_duration/100;
		update7SegBuffer(red_sec, 2);
		status = RED_MODE;
		setTimer(LED_CHANGE, blink_frequent);
	}
}

void countdownUpdate(int *light1, int *light2) {
    if (isTimerExpired(COUNTDOWN_TIMER)) {
        if (*light1 > 0) (*light1)--;
        if (*light2 > 0) (*light2)--;
        update7SegBuffer(*light1, *light2);
        setTimer(COUNTDOWN_TIMER, 100);
    }
}

void resetCountdown() {
    if (red_sec <= 0) red_sec = red_duration / 100;
    if (yellow_sec <= 0) yellow_sec = yellow_duration / 100;
    if (green_sec <= 0) green_sec = green_duration / 100;
}
