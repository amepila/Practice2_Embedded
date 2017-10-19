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

  	States_MenuType currentState = DEFAULT;
	States_MenuType(*mainFunctions)(void);

	SPI_init(&SPI_Config);
	LCDNokia_init();
	LCDNokia_clear();
	Buttons_init(Buttons_Config);
	ADC_init(&ADC_Config);

	/*DEBUG*/
	setAllRGB();

	/*********************************/
	/***INTERRUPTIONS CONFIGURATION***/
	/*********************************/

	/**Set the reference priority **/
	NVIC_setBASEPRI_threshold(PRIORITY_10);

	/**Set the priority**/
	NVIC_enableInterruptAndPriotity(PORTA_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTB_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_4);

	/**Enable all the interrupts **/
	EnableInterrupts;
    while(1){
    	mainFunctions = StateProgram[currentState].stateFunction;
    	currentState = mainFunctions();
    }
    return 0;
}
