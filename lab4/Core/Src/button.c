/*
 * button.c
 *
 *  Created on: Nov 29, 2022
 *      Author: HP
 */


#include"button.h"

int button1_flag = 0;

int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE;

int TimeOutForKeyPress =  200;

int isButton1Pressed() {
	if (button1_flag == 1) {
		button1_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(){
	//TODO
	button1_flag = 1;
}
//nhieu nut nhan, dung mang, o ham HALGPIOReadPin dung them if de phan loai nut, sau do for cho full ham getKeyInput() (xem them tren Internet)
void getKeyInput(){
  KeyReg2 = KeyReg1;
  KeyReg1 = KeyReg0;
  KeyReg0 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
  if ((KeyReg1 == KeyReg0) && (KeyReg1 == KeyReg2)){
    if (KeyReg2 != KeyReg3){
      KeyReg3 = KeyReg2;
      if (KeyReg2 == PRESSED_STATE){
        subKeyProcess();
        TimeOutForKeyPress = 200;
      }
    }
    else {
        TimeOutForKeyPress --;
        if (TimeOutForKeyPress == 0){
          KeyReg3 = NORMAL_STATE;
        }
    }
  }
}
