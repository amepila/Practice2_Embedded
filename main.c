#include <stdio.h>
#include "MK64F12.h"
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "LCDNokia5110.h"
#include "GlobalFunctions.h"
#include "SPI.h"
#include "ADC.h"
#include "Colors.h"
#include "PIT.h"
#include "NVIC.h"
#include "Buttons.h"
#include "Keyboard.h"

/*Macros*/

/*Set of configurations*/
const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2,
							SPI_BAUD_RATE_2,
							SPI_FSIZE_8,
							{GPIO_D,BIT1,BIT2}};

const Button_ConfigType Buttons_Config[6] = {
		{PORT_C,BIT3},
		{PORT_C,BIT2},
		{PORT_A,BIT2},
		{PORT_B,BIT23},
		{PORT_A,BIT1},
		{PORT_B,BIT9}
};

const ADC_ConfigType ADC_Config = {ADC_0,
								{ADC_CLK8,ADC_LONG,ADC_CONVER_8B,ADC_BUS_CLK},
								ADC_HW_ENABLE,
								ADC_SAMPLE32,
								ADC_INPUT_DADP0};

/*State machines*/




int main(void) {
	/*Configurations and local variables*/
	volatile uint32 resultADC;
	uint8 string1[]="ITESO";

	SPI_init(&SPI_Config);
	LCDNokia_init();
	Buttons_init(Buttons_Config);
	ADC_init(&ADC_Config);

	EnableInterrupts;
    while(1){
    	/*Tasks*/
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
