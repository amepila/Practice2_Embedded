/*
 *
 *
 */

#include <stdio.h>
#include "MK64F12.h"
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "LCDNokia5110.h"
#include "SPI.h"
#include "ADC.h"
#include "Colors.h"
#include "PIT.h"
#include "NVIC.h"
#include "Buttons.h"
#include "Keyboard.h"
#include "Menu.h"
#include "Configurations.h"


int main(void) {

	volatile uint32 resultADC;
	States_MenuType currentState = DEFAULT;

	uint8 menuLCD = 0;

	uint8 counterLinesLCD;
	uint8 enableButton = FALSE;


	SPI_init(&SPI_Config);
	LCDNokia_init();
	LCDNokia_clear();
	Buttons_init(Buttons_Config);
	ADC_init(&ADC_Config);

	/*********************************/
	/***INTERRUPTIONS CONFIGURATION***/
	/*********************************/

	/**Set the reference priority **/
	NVIC_setBASEPRI_threshold(PRIORITY_10);

	/**Set the priority**/
	NVIC_enableInterruptAndPriotity(PORTA_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTB_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTD_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTE_IRQ, PRIORITY_4);

	/**Enable all the interrupts **/
	EnableInterrupts;
    while(1){
    	currentState;

    	for(counterLinesLCD = 0; counterLinesLCD < 4; counterLinesLCD++){
     		LCDNokia_gotoXY(18,counterLinesLCD);
    		LCDNokia_sendString((uint8*)(Sub_ArrayStrings1[counterLinesLCD]));
    		delay(6500);
    	}


		if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_0)) && (TRUE == enableButton)){
			Button_clearFlag(BUTTON_0);
		}
		if((TRUE == GPIO_getIRQStatus(GPIO_C)) && (TRUE == Button_getFlag(BUTTON_1)) && (TRUE == enableButton)){
			Button_clearFlag(BUTTON_1);
		}
		if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_2)) && (TRUE == enableButton)){
			Button_clearFlag(BUTTON_2);
		}
		if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_3)) && (TRUE == enableButton)){
			Button_clearFlag(BUTTON_3);
		}
		if((TRUE == GPIO_getIRQStatus(GPIO_A)) && (TRUE == Button_getFlag(BUTTON_4)) && (TRUE == enableButton)){
			Button_clearFlag(BUTTON_4);
		}
		if((TRUE == GPIO_getIRQStatus(GPIO_B)) && (TRUE == Button_getFlag(BUTTON_5)) && (TRUE == enableButton)){
			Button_clearFlag(BUTTON_5);
		}

		resultADC = ADC_calculateResult(&ADC_Config);

		LCDNokia_clear();
    }
    return 0;
}
