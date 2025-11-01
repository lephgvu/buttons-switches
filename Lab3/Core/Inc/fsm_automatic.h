/*
 * fsm_automatic.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Admin
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"

void fsm_automatic_run();
void countDownUpdate(int *light1, int *light2);
void resetCountDown();
void modeChangeCheck();

#endif /* INC_FSM_AUTOMATIC_H_ */
