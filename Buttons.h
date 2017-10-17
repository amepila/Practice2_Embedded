/*
 * Buttons.h
 *
 *  Created on: Oct 14, 2017
 *      Author: Andres Hernandez
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"


typedef enum{
	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5
}Button_Type;

typedef struct
{
	uint8 flagButton0 : 1;
	uint8 flagButton1 : 1;
	uint8 flagButton2 : 1;
	uint8 flagButton3 : 1;
	uint8 flagButton4 : 1;
	uint8 flagButton5 : 1;
} Button_PressedFlag;


typedef enum{PORT_A,PORT_B,PORT_C,PORT_D,PORT_E}Button_PortType;

typedef struct{
	Button_PortType Button_Port;
	BitsType Bit_Type;
}Button_ConfigType;


//static void Button_clock(Button_PortType);

//static void Button_enable(Button_PortType,BitsType);

void Button_statusFlag(GPIO_portNameType gpio, BitsType bit);

uint8 Button_getFlag(Button_Type button);

void Button_clearFlag(Button_Type button);

void Buttons_init(const Button_ConfigType*);


#endif /* BUTTONS_H_ */
