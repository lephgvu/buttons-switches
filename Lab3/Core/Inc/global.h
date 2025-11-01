/*
 * global.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "timer.h"
#include "display.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"

extern int status;

extern int blink_frequent;
extern int red_duration;
extern int yellow_duration;
extern int green_duration;

extern int red_sec;
extern int yellow_sec;
extern int green_sec;

extern int sevenSegBuffer[4];

#define LED_RED			0
#define LED_CHANGE		1
#define SEG_TIMER		2
#define COUNTDOWN_TIMER	3

#define INIT			10

#define RED_GREEN		20
#define RED_YELLOW		21
#define GREEN_RED		22
#define YELLOW_RED		23

#define RED 			24
#define YELLOW 			25
#define GREEN			26

#define RED_MODE 		30
#define YELLOW_MODE		31
#define GREEN_MODE		32

#endif /* INC_GLOBAL_H_ */
