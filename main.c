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
#include "FlexTimer.h"
#include "ADC.h"
#include "Colors.h"
#include "PIT.h"
#include "NVIC.h"
#include "Buttons.h"
#include "Keyboard.h"
#include "Menu.h"
#include "Configurations.h"

#define CENT			(100U)
#define MODULO			(0xFFU)
#define MODULO_CAPTURE	(0xFFFFU)
#define INIT_MOD		(0.80F)

int main(void){



	volatile uint32 ResultADC;
	float velocity;

  	States_MenuType currentState = DEFAULT;
	States_MenuType(*mainFunctions)(uint32);

	SPI_init(&SPI_Config);
	LCDNokia_init();
	LCDNokia_clear();
	Buzzer_init();
	Buttons_init(Buttons_Config);
	ADC_init(&ADC_Config);
	FlexTimer_Init(&outputconfig,INIT_MOD,MODULO);
	FlexTimer_Init(&inputConfig,1,MODULO_CAPTURE);

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
	NVIC_enableInterruptAndPriotity(FTM0_IRQ,PRIORITY_8);
	NVIC_enableInterruptAndPriotity(FTM2_IRQ,PRIORITY_9);


	/**Enable all the interrupts **/
	EnableInterrupts;
    while(1){

    	velocity = (float)VelocityMotor/CENT;
    	setDutyCycle(FTM_0, FTMnC0, velocity);
    	ResultADC = ADC_calculateResult(&ADC_Config);

    	mainFunctions = StateProgram[currentState].stateFunction;
    	currentState = mainFunctions(ResultADC);
    }
    return 0;
}
