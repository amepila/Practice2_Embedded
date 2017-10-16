/*
 * Menu.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Andres Hernandez
 */

#ifndef CONFIGURATIONS_H_
#define CONFIGURATIONS_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "Buttons.h"
#include "SPI.h"
#include "ADC.h"
#include "GPIO.h"
#include "Menu.h"


typedef enum{
	DEFAULT,
	MENU,
	ALARM,
	FORMAT,
	INCREMENT,
	MANUAL,
	FREQUENCY,
	PASSWORD
}States_MenuType;


/***********************************************************************/
/******************************SET OF CONFIGURATIONS********************/
/***********************************************************************/

const Button_ConfigType Buttons_Config[6] = {
							{PORT_C,BIT3},
							{PORT_C,BIT2},
							{PORT_A,BIT2},
							{PORT_B,BIT23},
							{PORT_A,BIT1},
							{PORT_B,BIT9}
};

const SPI_ConfigType SPI_Config={
							SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2,
							SPI_BAUD_RATE_2,
							SPI_FSIZE_8,
							{GPIO_D,BIT1,BIT2}};



const ADC_ConfigType ADC_Config = {
							ADC_0,
							{ADC_CLK8,ADC_LONG,ADC_CONVER_8B,ADC_BUS_CLK},
							ADC_HW_ENABLE,
							ADC_SAMPLE32,
							ADC_INPUT_DADP0};


/***********************************************************************/
/******************************STATE MACHINES***************************/
/***********************************************************************/

typedef const struct State{
	States_MenuType currentState;
	uint32 out;
	uint32 wait;

	const struct State* next[2];
}StateType;



#endif /* CONFIGURATIONS_H_ */
