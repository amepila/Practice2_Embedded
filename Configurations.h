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
#include "Colors.h"
#include "FlexTimer.h"


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

typedef States_MenuType(*fptrState)(uint32);


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


const FTM_Config outputconfig = {
							DISABLE_WRITEPROTECTION,
							SYSTEMCLOCK,
							DISABLE_FTM,
							PS_2,//4
							ENABLE_TOIF,
							ENABLE_MSB,
							DISABLE_MSA,
							DISABLE_ELSB,
							ENABLE_ELSA,
							FTM_0,
							FTMnC0,
							ChInterrupt_Disable
};

const FTM_Config inputConfig = {
							DISABLE_WRITEPROTECTION,
							SYSTEMCLOCK,
							DISABLE_FTM,
							PS_2,
							ENABLE_TOIF,
							DISABLE_MSA,
							DISABLE_MSB,
							DISABLE_ELSB,
							ENABLE_ELSA,
							FTM_2,
							FTMnC0,
							ChInterrupt_Enable
};


/***********************************************************************/
/******************************Global Variables*************************/
/***********************************************************************/
const uint8 SymbolGrades = 39;
const uint8 SymbolPercen = 37;
const uint8 wordC = 67;
const uint8 wordF = 70;

uint32 VelocityMotor = 80;

uint8 SetIncrement = 15;
uint8 FlagFormat = FALSE;
uint8 SetAlarm = 30;
uint8 ModeManual = FALSE;

/***********************************************************************/
/*****************************MAIN FUNCTIONS****************************/
/***********************************************************************/


States_MenuType stateDefault(uint32 resultADC){

	uint8 counterLinesLCD;
	float resultFah;
	States_MenuType state = DEFAULT;

	Buzzer_setAlarm(resultADC, SetAlarm);
	resultFah = Conversion_Fahrenheit(resultADC);
	VelocityMotor = Control_Velocity(resultADC, SetIncrement, ModeManual, VelocityMotor);

	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){

		LCDNokia_gotoXY(7,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings1[counterLinesLCD]));

		if(1 == counterLinesLCD){

			LCDNokia_printValue(VelocityMotor);
			LCDNokia_sendChar(SymbolPercen);
		}
		if((3 == counterLinesLCD) && (FALSE == FlagFormat)){

			LCDNokia_printValue(resultADC);
			LCDNokia_sendChar(SymbolGrades);
			LCDNokia_sendChar(wordC);
		}
		if((3 == counterLinesLCD) && (TRUE == FlagFormat)){

			LCDNokia_printFloatValue(resultFah);
			LCDNokia_sendChar(SymbolGrades);
			LCDNokia_sendChar(wordF);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}

	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){
		state = MENU;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	return state;
}

States_MenuType stateMenu(uint32 resultADC){

	uint8 counterLinesLCD;
	States_MenuType state = MENU;

	for(counterLinesLCD = 0; counterLinesLCD < 5; counterLinesLCD++){
		LCDNokia_gotoXY(0,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings2[counterLinesLCD]));

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}

	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){
		state = DEFAULT;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){
		state = ALARM;
		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){
		state = FORMAT;
		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){
		state = INCREMENT;
		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4))){
		state = MANUAL;
		Button_clearFlag(BUTTON_4);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5))){
		state = FREQUENCY;
		Button_clearFlag(BUTTON_5);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}
	return state;
}

States_MenuType stateAlarm(uint32 resultADC){

	uint8 counterLinesLCD;
	States_MenuType state = ALARM;
	static uint32 tmpConfig_Alarm;
	static uint8 detectorInit = FALSE;

	if(detectorInit == FALSE){tmpConfig_Alarm = SetAlarm;}

	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
		LCDNokia_gotoXY(7,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings3[counterLinesLCD]));

		if(1 == counterLinesLCD){

			LCDNokia_printValue(tmpConfig_Alarm);
			LCDNokia_sendChar(SymbolGrades);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}

	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = DEFAULT;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		tmpConfig_Alarm--;
		detectorInit = TRUE;

		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		tmpConfig_Alarm++;
		detectorInit = TRUE;

		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		SetAlarm = tmpConfig_Alarm;

		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}

	return state;
}

States_MenuType stateFormat(uint32 resultADC){

	uint8 counterLinesLCD;
	float tempFah;
	States_MenuType state = FORMAT;
	static uint8 detectorInit = FALSE;
	static uint8 tmpDetector = FALSE;

	tempFah = Conversion_Fahrenheit(resultADC);

	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
		LCDNokia_gotoXY(0,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings4[counterLinesLCD]));

		if(1 == counterLinesLCD){
			LCDNokia_gotoXY(35,counterLinesLCD);

			if(FALSE == detectorInit){
				LCDNokia_printValue(resultADC);
				LCDNokia_sendChar(SymbolGrades);
				LCDNokia_sendChar(wordC);
			}
			if(TRUE == detectorInit){

				LCDNokia_printFloatValue(tempFah);
				LCDNokia_gotoXY(70,counterLinesLCD);
				LCDNokia_sendChar(SymbolGrades);
				LCDNokia_sendChar(wordF);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = DEFAULT;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		tmpDetector = FALSE;

		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		tmpDetector = TRUE;

		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		detectorInit = tmpDetector;
		FlagFormat = tmpDetector;

		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}
	return state;
}

States_MenuType stateIncrement(uint32 resultADC){

	uint8 counterLinesLCD;
	States_MenuType state = INCREMENT;
	static uint32 tmpConfig_Increment;
	static uint8 detectorInit = FALSE;

	if(detectorInit == FALSE){tmpConfig_Increment = SetIncrement;}

	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
		LCDNokia_gotoXY(7,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings5[counterLinesLCD]));

		if(1 == counterLinesLCD){

			LCDNokia_gotoXY(32,counterLinesLCD);
			LCDNokia_printValue(tmpConfig_Increment);
			LCDNokia_sendChar(SymbolPercen);

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}

	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = DEFAULT;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		if(tmpConfig_Increment > 5){
			tmpConfig_Increment -= 5;
			detectorInit = TRUE;
		}

		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		if(tmpConfig_Increment < 100){
			tmpConfig_Increment += 5;
			detectorInit = TRUE;
		}


		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		SetIncrement = tmpConfig_Increment;

		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}

	return state;
}

States_MenuType stateManual(uint32 resultADC){

	uint8 counterLinesLCD;
	States_MenuType state = MANUAL;
	static uint8 tmpMode_Manual;
	uint8 modeIncrement;

	for(counterLinesLCD = 0; counterLinesLCD < 6; counterLinesLCD++){
		LCDNokia_gotoXY(7,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings6[counterLinesLCD]));

		if(1 == counterLinesLCD){
			LCDNokia_gotoXY(32,counterLinesLCD);
			LCDNokia_printValue(VelocityMotor);
			LCDNokia_sendChar(SymbolPercen);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		ModeManual = FALSE;
		state = DEFAULT;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		tmpMode_Manual = TRUE;

		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		tmpMode_Manual = FALSE;

		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		ModeManual = tmpMode_Manual;

		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4))){

		if((TRUE == ModeManual) && (VelocityMotor > 5)){
			modeIncrement = FALSE;
			VelocityMotor = Control_ManualVelocity(VelocityMotor, SetIncrement, modeIncrement);
		}

		Button_clearFlag(BUTTON_4);
		GPIO_clearIRQStatus(GPIO_A);
		LCDNokia_clear();
	}
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5))){

		if((TRUE == ModeManual) && (VelocityMotor < 100)){
			modeIncrement = TRUE;
			VelocityMotor = Control_ManualVelocity(VelocityMotor, SetIncrement, modeIncrement);
		}

		Button_clearFlag(BUTTON_5);
		GPIO_clearIRQStatus(GPIO_B);
		LCDNokia_clear();
	}
	return state;
}

States_MenuType stateFrequency(uint32 resultADC){

	uint8 counterLinesLCD;
	States_MenuType state = FREQUENCY;

	for(counterLinesLCD = 0; counterLinesLCD < 3; counterLinesLCD++){
		LCDNokia_gotoXY(7,counterLinesLCD);
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings7[counterLinesLCD]));
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		delay(2000);
	}


	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		state = DEFAULT;
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		LCDNokia_clear();

	}

	return state;
}

/***********************************************************************/
/******************************STATE MACHINES***************************/
/***********************************************************************/

typedef const struct State{
	States_MenuType (*stateFunction)(uint32);

}StateType;

const StateType StateProgram[7] =
{
		{stateDefault},
		{stateMenu},
		{stateAlarm},
		{stateFormat},
		{stateIncrement},
		{stateManual},
		{stateFrequency}
};

#endif /* CONFIGURATIONS_H_ */
