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

	SPI_init(&SPI_Config);
	LCDNokia_init();
	Buttons_init(Buttons_Config);
	ADC_init(&ADC_Config);

	/*********************************/
	/***INTERRUPTIONS CONFIGURATION***/
	/*********************************/

	/**Set the reference priority **/
	NVIC_setBASEPRI_threshold(PRIORITY_10);
	/**Set the priority of PORT A **/
	NVIC_enableInterruptAndPriotity(PORTA_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTB_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTD_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(PORTE_IRQ, PRIORITY_4);
	/**Enable all the interrupts **/
	EnableInterrupts;
    while(1){

		LCDNokia_clear();
 		LCDNokia_gotoXY(25,0);
		LCDNokia_sendString(string1);
		delay(6500);

		LCDNokia_clear();
		LCDNokia_gotoXY(25,2);
		LCDNokia_sendChar('1');
		delay(6500);

		resultADC = ADC_calculateResult(&ADC_Config);
    }
    return 0;
}
