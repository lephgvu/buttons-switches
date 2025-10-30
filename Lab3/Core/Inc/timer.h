/*
 * timer.h
 *
 *  Created on: Oct 29, 2025
 *      Author: Admin
 */
#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "global.h"

void setTimer(int index, int duration);
int isTimerExpired(int index);
void timerRun();

#endif /* INC_TIMER_H_ */
