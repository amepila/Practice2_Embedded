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

typedef enum{PORT_A,PORT_B,PORT_C,PORT_D,PORT_E}Button_PortType;

typedef struct{
	Button_PortType Button_Port;
	BitsType Bit_Type;
}Button_ConfigType;


//static void Button_clock(Button_PortType);

//static void Button_enable(Button_PortType,BitsType);

void Buttons_init(const Button_ConfigType*);


#endif /* BUTTONS_H_ */
