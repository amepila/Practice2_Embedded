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
#include "FlexTimer.h"

/*Data type to States of the program*/
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

/*Data type to main functions*/
typedef States_MenuType(*fptrState)(uint32);


/***********************************************************************/
/******************************SET OF CONFIGURATIONS********************/
/***********************************************************************/

/**Set of pin of Buttons**/
const Button_ConfigType Buttons_Config[6] = {
							{PORT_C,BIT3},	/**Button 1**/
							{PORT_C,BIT2},	/**Button 2**/
							{PORT_A,BIT2},	/**Button 3**/
							{PORT_B,BIT23},	/**Button 4**/
							{PORT_A,BIT1},	/**Button 5**/
							{PORT_B,BIT9}	/**Button 6**/
};

const SPI_ConfigType SPI_Config={
							SPI_DISABLE_FIFO,	/**Disable fifos of SPI**/
							SPI_LOW_POLARITY,	/**Low Polarity to SPI**/
							SPI_LOW_PHASE,		/**Low Phase to SPI**/
							SPI_MSB,			/**The MSB bit is the first to be transmitted**/
							SPI_0,				/**Channel SPI0**/
							SPI_MASTER,			/**Set like master the SPI**/
							GPIO_MUX2,			/**Set like MUX2 in GPIO**/
							SPI_BAUD_RATE_2,	/**Baudrate to SPI**/
							SPI_FSIZE_8,		/**Size of frame**/
							{GPIO_D,BIT1,BIT2}};/**GPIO for SPI**/


const ADC_ConfigType ADC_Config = {
							ADC_0,				/**ADC channel 0**/
							{ADC_CLK8,ADC_LONG,ADC_CONVER_8B,ADC_BUS_CLK},	/**Configuration of clock and conversion**/
							ADC_HW_ENABLE,		/**Enable the hardware average**/
							ADC_SAMPLE32,		/**32 samples**/
							ADC_INPUT_DADP0};	/**Input DADP0**/


const FTM_Config outputconfig = {
							DISABLE_WRITEPROTECTION,	/**Disable protection**/
							SYSTEMCLOCK,				/**Use the system clock**/
							DISABLE_FTM,				/**Disable the mode Master**/
							PS_2,						/**Prescaler to 2**/
							ENABLE_TOIF,				/**Enable the overflow interrupt**/
							ENABLE_MSB,					/**Enable MSB     Edge-Aligned**/
							DISABLE_MSA,				/**Disable MSA			PWM   **/
							DISABLE_ELSB,				/**Disable ELSB		Low True  **/
							ENABLE_ELSA,				/**Disable ELSA       Pulses  **/
							FTM_0,						/**FTM module 0**/
							FTMnC0,						/**FTM channel 0**/
							ChInterrupt_Disable			/**Disable channel interrupts**/
};

const FTM_Config inputConfig = {
							DISABLE_WRITEPROTECTION,	/**Disable protection**/
							SYSTEMCLOCK,				/**Use the system clock**/
							DISABLE_FTM,				/**Disable the mode Master**/
							PS_1,						/**Preescaler to 1**/
							ENABLE_TOIF,				/**Enable the overflow interrupt**/
							DISABLE_MSA,				/**Disable MSA**/
							DISABLE_MSB,				/**Disable MSB**/
							DISABLE_ELSB,				/**Disable ELSB**/
							ENABLE_ELSA,				/**Disable ELSA**/
							FTM_2,						/**FTM module 2**/
							FTMnC0,						/**FTM channel 0**/
							ChInterrupt_Enable			/**Enable channel interrrupt**/
};


/***********************************************************************/
/******************************Global Variables*************************/
/***********************************************************************/

/**Grades in ASCII**/
const uint8 SymbolGrades = 39;
/**Percent in ASCII**/
const uint8 SymbolPercen = 37;
/**C in ASCII**/
const uint8 wordC = 67;
/**F in ASCII**/
const uint8 wordF = 70;
/**H in ASCII**/
const uint8 wordH = 72;
/**Z in ASCII**/
const uint8 wordz = 122;
/**Initial Velocity to motor**/
uint32 VelocityMotor = 80;
/**Default Increment**/
uint8 SetIncrement = 15;
/**Flag of format (C/F) set in FALSE**/
uint8 FlagFormat = FALSE;
/**Default limit to alarm**/
uint8 SetAlarm = 30;
/**Mode manual is OFF**/
uint8 ModeManual = FALSE;

/***********************************************************************/
/*****************************MAIN FUNCTIONS****************************/
/***********************************************************************/

/**The First state that shows the velocity and temperature**/
/**return The state of program**/
States_MenuType stateDefault(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Saves the value of temperature in Fahrenheit**/
	float resultFah;
	/**Value of the state**/
	States_MenuType state = DEFAULT;

	/**The buzzer is set when reaches the limit**/
	Buzzer_setAlarm(resultADC, SetAlarm);
	/**The value in fahrenheit is calculated**/
	resultFah = Conversion_Fahrenheit(resultADC);
	/**Velocity motor is calculated in base to the temperature**/
	VelocityMotor = Control_Velocity(resultADC, SetIncrement, ModeManual, VelocityMotor);

	/**Loop to print in the LCD**/
	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){

		/**Fixed position**/
		LCDNokia_gotoXY(7,counterLinesLCD);
		/**Print the menu of the state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings1[counterLinesLCD]));

		/**In the second line print the velocity of motor**/
		if(1 == counterLinesLCD){
			/**Print the value of velocity**/
			LCDNokia_printValue(VelocityMotor);
			/**Print the character of percent**/
			LCDNokia_sendChar(SymbolPercen);
		}
		/**In the last line print the value of temperature in celsius**/
		if((3 == counterLinesLCD) && (FALSE == FlagFormat)){
			/**Print the value in celsius**/
			LCDNokia_printValue(resultADC);
			/**Print the grade character**/
			LCDNokia_sendChar(SymbolGrades);
			/**Print the letter C***/
			LCDNokia_sendChar(wordC);
		}
		/**If the format is fahrenheint then print this float value**/
		if((3 == counterLinesLCD) && (TRUE == FlagFormat)){
			/**Print the float value**/
			LCDNokia_printFloatValue(resultFah);
			/**Print the grade character**/
			LCDNokia_sendChar(SymbolGrades);
			/**Print the letter F**/
			LCDNokia_sendChar(wordF);
		}
	}

	/**If the button 0 is pressed then change of state**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){
		/**Change to Menu State**/
		state = MENU;
		/**Clear the interrupter of button**/
		Button_clearFlag(BUTTON_0);
		/**Clear the status of Button**/
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD before change of state**/
		LCDNokia_clear();
	}
	return state;
}

/**The state menu shows the options to change of state**/
/**return the state**/
States_MenuType stateMenu(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Value of status**/
	States_MenuType state = MENU;

	/**Loop to print in the LCD**/
	for(counterLinesLCD = 0; counterLinesLCD < 5; counterLinesLCD++){
		/**Fixed position**/
		LCDNokia_gotoXY(0,counterLinesLCD);
		/**Print the menu of the state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings2[counterLinesLCD]));
	}

	/**The button 0 return the default menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){
		/**Change of direction**/
		state = DEFAULT;
		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**The button 1 go on to the Alarm menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){
		/**Change of direction**/
		state = ALARM;
		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**The button 2 go gon to the Format menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){
		/**Change direction**/
		state = FORMAT;
		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**The button 3 go on to the Increment menu***/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){
		/**Change direction**/
		state = INCREMENT;
		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**The button 4 go on to the Manual menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4))){
		/**Change direction**/
		state = MANUAL;
		/**Clear interrupts**/
		Button_clearFlag(BUTTON_4);
		GPIO_clearIRQStatus(GPIO_A);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**The button 5 go gon to the Frequency menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5))){
		/**Change the direction**/
		state = FREQUENCY;
		/***Clear interrupts**/
		Button_clearFlag(BUTTON_5);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	return state;
}

/**This menus shows the Alarm Menu to set up the alarm**/
States_MenuType stateAlarm(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Value of status**/
	States_MenuType state = ALARM;
	/**Temporal value that saves the value of alarm**/
	static uint32 tmpConfig_Alarm;
	/**This variable detects if the increment/decrement buttons are pressed**/
	static uint8 detectorInit = FALSE;

	/**If there isn't pressed buttons then the alarm doesn't change**/
	if(detectorInit == FALSE){tmpConfig_Alarm = SetAlarm;}

	/**Loop to print LCD**/
	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
		/**Fixed position**/
		LCDNokia_gotoXY(7,counterLinesLCD);
		/**Print the menu of the state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings3[counterLinesLCD]));
		/**In the second line print the values**/
		if(1 == counterLinesLCD){
			/**Print the value of alarma**/
			LCDNokia_printValue(tmpConfig_Alarm);
			/**Printf grades character**/
			LCDNokia_sendChar(SymbolGrades);
		}
	}

	/**If the button 0 is pressed then back to default menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		/**Return to default state**/
		state = DEFAULT;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 1 is pressed, decrements the alarm**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		/**This variable no yet affect the Alarm**/
		tmpConfig_Alarm--;
		/**Flag change to true**/
		detectorInit = TRUE;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 2 is pressed, increments the alarm**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		/**This variable no yet affect the Alarm**/
		tmpConfig_Alarm++;
		/**Flag change to true**/
		detectorInit = TRUE;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 3 is pressed, set the new value of Alarm**/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		/**The variable is rewrite with a new value **/
		SetAlarm = tmpConfig_Alarm;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	return state;
}

/**This menus shows the format menu to change of Celsius to Fahrenheint**/
States_MenuType stateFormat(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Value of temperature in fahrenheint**/
	float tempFah;
	/**Current state**/
	States_MenuType state = FORMAT;
	/**The detector of temperature is set in false**/
	static uint8 detectorInit = FALSE;
	/**The detector of button is set in false**/
	static uint8 tmpDetector = FALSE;

	/**The conversion of fahrenheit**/
	tempFah = Conversion_Fahrenheit(resultADC);

	/**Loop to print LCD**/
	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){

		/**Fixed position in LCD**/
		LCDNokia_gotoXY(0,counterLinesLCD);
		/**Print the menu of the state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings4[counterLinesLCD]));

		/**In the second line print the values**/
		if(1 == counterLinesLCD){

			/**Readjust the position**/
			LCDNokia_gotoXY(35,counterLinesLCD);

			/**Detector in false represents the Celsius**/
			if(FALSE == detectorInit){

				/**Value to print**/
				LCDNokia_printValue(resultADC);
				LCDNokia_sendChar(SymbolGrades);
				LCDNokia_sendChar(wordC);
			}
			/**Detector in true represents the Fahrenheint**/
			if(TRUE == detectorInit){

				/**Value to print**/
				LCDNokia_printFloatValue(tempFah);
				LCDNokia_gotoXY(70,counterLinesLCD);
				LCDNokia_sendChar(SymbolGrades);
				LCDNokia_sendChar(wordF);
			}
		}
	}

	/**If button 0 is pressed returns to Default state**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		/**Change the direction**/
		state = DEFAULT;
		/**Clear interrupts**/
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 1 is pressed activate the celsius mode**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		/**Change the flag to celsius**/
		tmpDetector = FALSE;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 2 is pressed activate the fahrenheint mode**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		/**Change the flag to fahrenheint**/
		tmpDetector = TRUE;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 3 is pressed set the temperature mode and change the format**/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		/**Saves the temperature mode**/
		detectorInit = tmpDetector;
		/**The flag is change in all the program**/
		FlagFormat = tmpDetector;

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	return state;
}
/**This menu change the increment to the motor velocity**/
States_MenuType stateIncrement(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Current state**/
	States_MenuType state = INCREMENT;
	/**Temporal Value to save increment**/
	static uint32 tmpConfig_Increment;
	/**Detector of button pressed**/
	static uint8 detectorInit = FALSE;

	/**If detector is false then the increment is maintained**/
	if(detectorInit == FALSE){tmpConfig_Increment = SetIncrement;}

	/**Loop to print the LCD*/
	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){

		/**Fixed position**/
		LCDNokia_gotoXY(7,counterLinesLCD);
		/**Print the menu of state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings5[counterLinesLCD]));

		/**In the line 2 print the values**/
		if(1 == counterLinesLCD){

			/**Readjust the position**/
			LCDNokia_gotoXY(32,counterLinesLCD);
			/**Print the value of increment**/
			LCDNokia_printValue(tmpConfig_Increment);
			/**Print the character of percent**/
			LCDNokia_sendChar(SymbolPercen);
		}
	}

	/**If button 0 is pressed returns to the Default menu**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		/**Changes the direction**/
		state = DEFAULT;
		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If button 1 is pressed decrement the value of increment**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		/**While increment is greater than 5**/
		if(tmpConfig_Increment > 5){
			tmpConfig_Increment -= 5;
			/**Activate the flag of button detector**/
			detectorInit = TRUE;
		}

		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 2 is pressede increment the value of increment**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		/**While increment is smaller than 100**/
		if(tmpConfig_Increment < 100){
			tmpConfig_Increment += 5;
			/**Activate the flag o button detector**/
			detectorInit = TRUE;
		}

		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 3 is pressed then confirm the value of increment**/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		/**Assign the new increment to global variable**/
		SetIncrement = tmpConfig_Increment;

		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	return state;
}

/**This state shows the mode manual of motor velocity**/
States_MenuType stateManual(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Current state**/
	States_MenuType state = MANUAL;
	/**Temporal variable that saves the mode**/
	static uint8 tmpMode_Manual;
	/**Mode to increment o decrement**/
	uint8 modeIncrement;

	/**Loop to print the LCD**/
	for(counterLinesLCD = 0; counterLinesLCD < 6; counterLinesLCD++){

		/**Fixed position**/
		LCDNokia_gotoXY(7,counterLinesLCD);
		/**Printf the menu state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings6[counterLinesLCD]));

		/**In second line print the values**/
		if(1 == counterLinesLCD){
			/**Readjust the position**/
			LCDNokia_gotoXY(32,counterLinesLCD);
			/**Print the motor velocity**/
			LCDNokia_printValue(VelocityMotor);
			/**Printf the character of percent**/
			LCDNokia_sendChar(SymbolPercen);
		}
	}

	/**If the button 0 is pressed then program returns to Default state**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		/**Mode manual is set in false to continue with the temperature control**/
		ModeManual = FALSE;
		/**Change the direction**/
		state = DEFAULT;
		/**Clear interrupts**/
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 1 is pressed, the mode manual is set in 1 but doesn't affect the program**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1))){

		/**Set in true to indicate the next mode**/
		tmpMode_Manual = TRUE;
		/**Clear interrupts**/
		Button_clearFlag(BUTTON_1);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD***/
		LCDNokia_clear();
	}
	/**If the button 2 is pressed then mode manual is set in 1 but doesn't affect the program**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2))){

		/**Set in false to indicate that motor depends of temperature**/
		tmpMode_Manual = FALSE;

		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_2);
		GPIO_clearIRQStatus(GPIO_A);
		/*Clear the LCD***/
		LCDNokia_clear();
	}
	/**If the button 3 is pressed then the last image of mode manual is saved**/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3))){

		/**This assignation affects the program**/
		ModeManual = tmpMode_Manual;

		/**Clear the interrupts**/
		Button_clearFlag(BUTTON_3);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 4 is pressed then motor velocity is decrement**/
	if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4))){

		/**Safe conditional that verifies the value doesn't goes down**/
		if((TRUE == ModeManual) && (VelocityMotor > 5)){
			/**Mode decrement is active**/
			modeIncrement = FALSE;
			/**Calculate the velocity with actuals data**/
			VelocityMotor = Control_ManualVelocity(VelocityMotor, SetIncrement, modeIncrement);
		}

		/**Clear interrupts**/
		Button_clearFlag(BUTTON_4);
		GPIO_clearIRQStatus(GPIO_A);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	/**If the button 5 is pressed then motor velocity is increment**/
	if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5))){

		/**Safe conditional that verifies the value doesn't goes down**/
		if((TRUE == ModeManual) && (VelocityMotor < 100)){
			/**Enables the mode Increment**/
			modeIncrement = TRUE;
			/**Calculate the new velocity**/
			VelocityMotor = Control_ManualVelocity(VelocityMotor, SetIncrement, modeIncrement);
		}

		/**Clear the interrupters**/
		Button_clearFlag(BUTTON_5);
		GPIO_clearIRQStatus(GPIO_B);
		/**Clear the LCD**/
		LCDNokia_clear();
	}
	return state;
}

/**This state shows the value of frequency through the input capture**/
States_MenuType stateFrequency(uint32 resultADC){

	/**Counter of lines of LCD to print**/
	uint8 counterLinesLCD;
	/**Current state**/
	States_MenuType state = FREQUENCY;
	/**Initial value of frequency**/
	uint32 frequency = 0;
	/**Value in counters of input capture**/
	uint16 value_Capture;

	/**The value of input capture is assigned**/
	value_Capture = getCnVDifference();
	/**Calculate the frequency**/
	frequency = Calculate_Frequency(value_Capture);

	/**Loop to printf the LCD**/
	for(counterLinesLCD = 0; counterLinesLCD < 3; counterLinesLCD++){

		/**Fixed position**/
		LCDNokia_gotoXY(7,counterLinesLCD);
		/**Print the menu of state**/
		LCDNokia_sendString((uint8*)(Sub_ArrayStrings7[counterLinesLCD]));

		/**In the third line print the frequency**/
		if(2 == counterLinesLCD){
			LCDNokia_gotoXY(15,counterLinesLCD);
			LCDNokia_printValue(frequency);
		}
	}

	/**If Button 0 is pressed, the function returns to Default state**/
	if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0))){

		/**Change the direction**/
		state = DEFAULT;
		/**Clear interrupters**/
		Button_clearFlag(BUTTON_0);
		GPIO_clearIRQStatus(GPIO_C);
		/**Clear the LCD**/
		LCDNokia_clear();
	}

	return state;
}

/***********************************************************************/
/******************************STATE MACHINES***************************/
/***********************************************************************/

/**Data type to machine state**/
typedef const struct State{
	States_MenuType (*stateFunction)(uint32);

}StateType;

/**Simple machine state only change the tag**/
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
