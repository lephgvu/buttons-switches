/*
 * display.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Admin
 */
#include "display.h"

// ------------------ clearAllLEDs() ------------------//
void clearAllLEDs(){
	HAL_GPIO_WritePin(GPIOA, RED1_Pin|YELLOW1_Pin|GREEN1_Pin|RED2_Pin|YELLOW2_Pin|GREEN2_Pin, GPIO_PIN_SET);
}


// ------------------ setLEDs() ------------------//
void setLEDs(int led){
	clearAllLEDs();
	switch(led){
		case RED_GREEN:
			HAL_GPIO_WritePin(GPIOA, RED1_Pin|GREEN2_Pin, GPIO_PIN_RESET);
			break;

		case RED_YELLOW:
			HAL_GPIO_WritePin(GPIOA, RED1_Pin|YELLOW2_Pin, GPIO_PIN_RESET);
			break;

		case GREEN_RED:
			HAL_GPIO_WritePin(GPIOA, GREEN1_Pin|RED2_Pin, GPIO_PIN_RESET);
			break;

		case YELLOW_RED:
			HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin|RED2_Pin, GPIO_PIN_RESET);
			break;

		default:
			break;
	}
}


// ------------------ blinkLEDs() ------------------//
void blinkLEDs(int led){
	switch (led){
		case RED:
			HAL_GPIO_TogglePin(GPIOA, RED1_Pin|RED2_Pin);
			break;

		case YELLOW:
			HAL_GPIO_TogglePin(GPIOA, YELLOW1_Pin|YELLOW2_Pin);
			break;

		case GREEN:
			HAL_GPIO_TogglePin(GPIOA, GREEN1_Pin|GREEN2_Pin);
			break;
	}
}


// ------------------ clearENs() ------------------//
void clearENs(){
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
}


// ------------------ clear7SEG() ------------------//
void clear7SEG(){
	HAL_GPIO_WritePin(GPIOB,
					  A1_Pin|B1_Pin|C1_Pin|D1_Pin|E1_Pin|F1_Pin|G1_Pin|
					  A2_Pin|B2_Pin|C2_Pin|D2_Pin|E2_Pin|F2_Pin|G2_Pin,
					  GPIO_PIN_SET);
}


// ------------------ clear7SEG_1() ------------------//
void clear7SEG_1(){
	HAL_GPIO_WritePin(GPIOB, A1_Pin|B1_Pin|C1_Pin|D1_Pin|E1_Pin|F1_Pin|G1_Pin, GPIO_PIN_SET);
}


// ------------------ clear7SEG_2() ------------------//
void clear7SEG_2(){
	HAL_GPIO_WritePin(GPIOB, A2_Pin|B2_Pin|C2_Pin|D2_Pin|E2_Pin|F2_Pin|G2_Pin, GPIO_PIN_SET);
}


// ------------------ turnAll7SEG() ------------------//
void turnAll7SEG(){
	HAL_GPIO_WritePin(GPIOB,
					  A1_Pin|B1_Pin|C1_Pin|D1_Pin|E1_Pin|F1_Pin|G1_Pin|
					  A2_Pin|B2_Pin|C2_Pin|D2_Pin|E2_Pin|F2_Pin|G2_Pin,
					  GPIO_PIN_RESET);
}


// ------------------ turnAll7SEG_1() ------------------//
void turnAll7SEG_1(){
	HAL_GPIO_WritePin(GPIOB, A1_Pin|B1_Pin|C1_Pin|D1_Pin|E1_Pin|F1_Pin|G1_Pin, GPIO_PIN_RESET);
}


// ------------------ turnAll7SEG_2() ------------------//
void turnAll7SEG_2(){
	HAL_GPIO_WritePin(GPIOB, A2_Pin|B2_Pin|C2_Pin|D2_Pin|E2_Pin|F2_Pin|G2_Pin, GPIO_PIN_RESET);
}


// ------------------ update7SegBuffer() ------------------//
void update7SegBuffer(int timer, int mode){
	sevenSegBuffer[0] = timer/10;
	sevenSegBuffer[1] = timer%10;
	sevenSegBuffer[2] = mode/10;
	sevenSegBuffer[3] = mode%10;
}


// ------------------ display7SEG() ------------------//
void display7SEG(int seg, int num){
	if (seg == 1){
		turnAll7SEG_1();
		switch (num){
			case 0:
				HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_SET);
				break;
			case 1:
				clear7SEG_1();
				HAL_GPIO_WritePin(GPIOB, B1_Pin|C1_Pin, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB, C1_Pin|F1_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB, E1_Pin|F1_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOB, A1_Pin|D1_Pin|E1_Pin, GPIO_PIN_SET);
				break;
			case 5:
				HAL_GPIO_WritePin(GPIOB, B1_Pin|E1_Pin, GPIO_PIN_SET);
				break;
			case 6:
				HAL_GPIO_WritePin(GPIOB, B1_Pin, GPIO_PIN_SET);
				break;
			case 7:
				clear7SEG_1();
				HAL_GPIO_WritePin(GPIOB, A1_Pin|B1_Pin|C1_Pin, GPIO_PIN_RESET);
				break;
			case 8:
				break;
			case 9:
				HAL_GPIO_WritePin(GPIOB, E1_Pin, GPIO_PIN_SET);
				break;
			default:
				clear7SEG();
				break;
		}
	} else if (seg == 2){
		turnAll7SEG_2();
		switch (num){
			case 0:
				HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_SET);
				break;
			case 1:
				clear7SEG_2();
				HAL_GPIO_WritePin(GPIOB, B2_Pin|C2_Pin, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB, C2_Pin|F2_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB, E2_Pin|F2_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOB, A2_Pin|D2_Pin|E2_Pin, GPIO_PIN_SET);
				break;
			case 5:
				HAL_GPIO_WritePin(GPIOB, B2_Pin|E2_Pin, GPIO_PIN_SET);
				break;
			case 6:
				HAL_GPIO_WritePin(GPIOB, B2_Pin, GPIO_PIN_SET);
				break;
			case 7:
				clear7SEG_2();
				HAL_GPIO_WritePin(GPIOB, A2_Pin|B2_Pin|C2_Pin, GPIO_PIN_RESET);
				break;
			case 8:
				break;
			case 9:
				HAL_GPIO_WritePin(GPIOB, E2_Pin, GPIO_PIN_SET);
				break;
			default:
				clear7SEG();
				break;
		}
	}
}

// ------------------ update7SEG() ------------------//
void update7SEG(int index){
	switch (index){
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
			display7SEG(1, sevenSegBuffer[index]);
			break;

		case 1:
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
			display7SEG(1, sevenSegBuffer[index]);
			break;

		case 2:
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
			display7SEG(2, sevenSegBuffer[index]);
			break;

		case 3:
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
			display7SEG(2, sevenSegBuffer[index]);
			break;

		default:
			break;
	}
}


