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

typedef States_MenuType(*fptrState)(void);





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
/*****************************MAIN FUNCTIONS****************************/
/***********************************************************************/

States_MenuType stateDefault(){

	uint8 counterLinesLCD;
	States_MenuType state = DEFAULT;

	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings1[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = MENU;
		Button_clearFlag(BUTTON_0);
	}


	return state;
}

States_MenuType stateMenu(){

	uint8 counterLinesLCD;
	States_MenuType state = MENU;

	for(counterLinesLCD = 0; counterLinesLCD < 5; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings2[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		state = ALARM;
		Button_clearFlag(BUTTON_1);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		state = FORMAT;
		Button_clearFlag(BUTTON_2);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		state = INCREMENT;
		Button_clearFlag(BUTTON_3);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4))){

		state = MANUAL;
		Button_clearFlag(BUTTON_4);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5))){

		state = FREQUENCY;
		Button_clearFlag(BUTTON_5);
	}

	return state;
}

States_MenuType stateAlarm(){

	uint8 counterLinesLCD;
	States_MenuType state = ALARM;


	for(counterLinesLCD = 0; counterLinesLCD < 3; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings3[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = MENU;
		Button_clearFlag(BUTTON_0);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){


		Button_clearFlag(BUTTON_1);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){


		Button_clearFlag(BUTTON_2);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){


		Button_clearFlag(BUTTON_3);
	}

	return state;
}

States_MenuType stateFormat(){

	uint8 counterLinesLCD;
	States_MenuType state = FORMAT;

	for(counterLinesLCD = 0; counterLinesLCD < 3; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings4[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = MENU;
		Button_clearFlag(BUTTON_0);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		Button_clearFlag(BUTTON_1);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		Button_clearFlag(BUTTON_2);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		Button_clearFlag(BUTTON_3);
	}

	return state;
}

States_MenuType stateIncrement(){

	uint8 counterLinesLCD;
	States_MenuType state = INCREMENT;

	for(counterLinesLCD = 0; counterLinesLCD < 3; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings5[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = MENU;
		Button_clearFlag(BUTTON_0);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		Button_clearFlag(BUTTON_1);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		Button_clearFlag(BUTTON_2);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		Button_clearFlag(BUTTON_3);
	}

	return state;
}

States_MenuType stateManual(){

	uint8 counterLinesLCD;
	States_MenuType state = MANUAL;

	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings6[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = MENU;
		Button_clearFlag(BUTTON_0);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		Button_clearFlag(BUTTON_1);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		Button_clearFlag(BUTTON_2);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		Button_clearFlag(BUTTON_3);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4))){

		Button_clearFlag(BUTTON_4);
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5))){

		Button_clearFlag(BUTTON_5);
	}

	return state;

}

States_MenuType stateFrequency(){

	uint8 counterLinesLCD;
	States_MenuType state = FREQUENCY;

	for(counterLinesLCD = 0; counterLinesLCD < 3; counterLinesLCD++){
			LCDNokia_gotoXY(18,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings7[counterLinesLCD]));
		delay(6500);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = MENU;
		Button_clearFlag(BUTTON_0);
	}

	return state;
}

/******************************************************************************/
/****************************Pointer to function*******************************/
/******************************************************************************/


fptrState State_Functions[7] = {
		stateDefault,
		stateMenu,
		stateAlarm,
		stateFormat,
		stateIncrement,
		stateManual,
		stateFrequency
};

/***********************************************************************/
/******************************STATE MACHINES***************************/
/***********************************************************************/

typedef const struct State{
	States_MenuType currentState;
	States_MenuType (*fptr_Function)(void);
	const struct State* next[2];
}StateType;





#endif /* CONFIGURATIONS_H_ */
