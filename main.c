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
#include "NVIC.h"
#include "Buttons.h"
#include "Menu.h"
#include "Configurations.h"

/*Factor to convert the velocity in float*/
#define CENT			(100U)
/*The modulo of output FTM*/
#define MODULO			(0xFFU)
/*The modulo of input FTM*/
#define MODULO_CAPTURE	(0xFFFFU)
/*Init mode to output FTM*/
#define INIT_MOD		(0.80F)

int main(void){

	volatile uint32 ResultADC;
	float velocity;

	/**First state in the program**/
  	States_MenuType currentState = DEFAULT;
	States_MenuType(*mainFunctions)(uint32);

	/**Configurations of devices**/
	SPI_init(&SPI_Config);
	LCDNokia_init();
	LCDNokia_clear();
	Buzzer_init();
	Buttons_init(Buttons_Config);
	ADC_init(&ADC_Config);
	FlexTimer_Init(&outputconfig,INIT_MOD,MODULO);
	FlexTimer_Init(&inputConfig,1,MODULO_CAPTURE);

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

    	/**Calculate the velocity of motor**/
    	velocity = (float)VelocityMotor/CENT;
    	/**Calculate the pwm signal**/
    	setDutyCycle(FTM_0, FTMnC0, velocity);
    	/**Calculate the ADC**/
    	ResultADC = ADC_calculateResult(&ADC_Config);

    	/**Machine states based on tags**/
    	mainFunctions = StateProgram[currentState].stateFunction;
    	currentState = mainFunctions(ResultADC);
    }
    return 0;
}
