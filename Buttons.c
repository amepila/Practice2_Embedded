/*
 * Buttons.c
 *
 *  Created on: Oct 14, 2017
 *      Author: Andres Hernandez
 */

#include "Buttons.h"

static Button_PressedFlag Button_Pressed;

static void Button_clock(Button_PortType port){
	switch(port){
	case PORT_A:
		GPIO_clockGating(GPIO_A);
		break;
	case PORT_B:
		GPIO_clockGating(GPIO_B);
		break;
	case PORT_C:
		GPIO_clockGating(GPIO_C);
		break;
	case PORT_D:
		GPIO_clockGating(GPIO_D);
		break;
	case PORT_E:
		GPIO_clockGating(GPIO_E);
		break;
	default:
		break;
	}
}

static void Button_enable(Button_PortType port, BitsType bit){

	static GPIO_pinControlRegisterType pinControlRegisterPort = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_RISING_EDGE;

	switch(port){
	case PORT_A:
		GPIO_pinControlRegister(GPIO_A,bit,&pinControlRegisterPort);
		GPIO_dataDirectionPIN(GPIO_A,GPIO_INPUT,bit);
		break;
	case PORT_B:
		GPIO_pinControlRegister(GPIO_B,bit,&pinControlRegisterPort);
		GPIO_dataDirectionPIN(GPIO_B,GPIO_INPUT,bit);
		break;
	case PORT_C:
		GPIO_pinControlRegister(GPIO_C,bit,&pinControlRegisterPort);
		GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,bit);
		break;
	case PORT_D:
		GPIO_pinControlRegister(GPIO_D,bit,&pinControlRegisterPort);
		GPIO_dataDirectionPIN(GPIO_D,GPIO_INPUT,bit);
		break;
	case PORT_E:
		GPIO_pinControlRegister(GPIO_E,bit,&pinControlRegisterPort);
		GPIO_dataDirectionPIN(GPIO_E,GPIO_INPUT,bit);
		break;
	default:
		break;
	}
}

void Button_statusFlag(GPIO_portNameType gpio, BitsType bit){
	switch(gpio){
	case GPIO_A:
		if(BIT1 == bit){
			Button_Pressed.flagButton4 = TRUE;
		}
		if(BIT2 == bit){
			Button_Pressed.flagButton2 = TRUE;
		}
		break;
	case GPIO_B:
		if(BIT9 == bit){
			Button_Pressed.flagButton5 = TRUE;
		}
		if(BIT23 == bit){
			Button_Pressed.flagButton3 = TRUE;
		}
		break;
	case GPIO_C:
		if(BIT2 == bit){
			Button_Pressed.flagButton1 = TRUE;
		}
		if(BIT3 == bit){
			Button_Pressed.flagButton0 = TRUE;
		}
		break;
	case GPIO_D:
		break;
	case GPIO_E:
		break;
	default:
		break;
	}
}

uint8 Button_getFlag(Button_Type button){

	switch(button){
	case BUTTON_0:
		return (Button_Pressed.flagButton0);
		break;
	case BUTTON_1:
		return (Button_Pressed.flagButton1);
		break;
	case BUTTON_2:
		return (Button_Pressed.flagButton2);
		break;
	case BUTTON_3:
		return (Button_Pressed.flagButton3);
		break;
	case BUTTON_4:
		return (Button_Pressed.flagButton4);
		break;
	case BUTTON_5:
		return (Button_Pressed.flagButton5);
		break;
	default:
		return FALSE;
		break;
	}
}

void Button_clearFlag(Button_Type button){
	switch(button){
	case BUTTON_0:
		Button_Pressed.flagButton0 = FALSE;
		break;
	case BUTTON_1:
		Button_Pressed.flagButton1 = FALSE;
		break;
	case BUTTON_2:
		Button_Pressed.flagButton2 = FALSE;
		break;
	case BUTTON_3:
		Button_Pressed.flagButton3 = FALSE;
		break;
	case BUTTON_4:
		Button_Pressed.flagButton4 = FALSE;
		break;
	case BUTTON_5:
		Button_Pressed.flagButton5 = FALSE;
		break;
	default:
		break;
	}
}

void Buttons_init(const Button_ConfigType* Button_Config){
	uint8 counter;

	for(counter = 0; counter < 6; counter++){
		Button_clock(Button_Config[counter].Button_Port);
		Button_enable(Button_Config[counter].Button_Port, Button_Config[counter].Bit_Type);
	}

}

void Buzzer_setAlarm(uint32 current_Value, uint32 limit_Conf){
	if(limit_Conf == current_Value){
		GPIO_clearPIN(GPIO_A,BIT0);
	}else{
		GPIO_setPIN(GPIO_A,BIT0);
	}
}

float Conversion_Fahrenheit(uint32 celsius_Temp){

	float fahrenheit_Temp;

	fahrenheit_Temp = ((float)(celsius_Temp*9)/5) + 32;
	return (fahrenheit_Temp);
}

uint32 Control_Velocity(uint32 temperature, uint8 increment, uint8 modeManual){

	const uint32 first_Temp = 20;
	const uint32 first_Vel = 80;
	const uint32 limit_Vel = 85;

	static uint32 default_Temp = 20;
	static uint32 default_Vel = 80;
	float velocity_Scale;
	uint32 diff_Temp;
	sint32 velocity;
	uint32 constant_Increment;
	uint32 mod_Temp;

	mod_Temp =  temperature % 2;

	if(mod_Temp == 1){temperature -= 1;}

	if((temperature > (default_Temp + 1)) && (FALSE == modeManual)){

		if(temperature < first_Temp){
			diff_Temp = first_Temp - temperature;
		}else{
			diff_Temp = temperature - first_Temp;
		}

		constant_Increment = diff_Temp / 2;

		velocity = (first_Vel)-(constant_Increment*increment);

		if(velocity <= 0){
			velocity = 0;
		}
	}
	if((temperature < (default_Temp - 1)) && (FALSE == modeManual)){

		if(temperature < first_Temp){
			diff_Temp = first_Temp - temperature;
		}else{
			diff_Temp = temperature - first_Temp;
		}
		constant_Increment = diff_Temp / 2;

		velocity = (first_Vel)+(constant_Increment*increment);

		if(velocity >= limit_Vel){
			velocity = limit_Vel;
		}
	}
	if((temperature >= (default_Temp - 1)) && (temperature <= (default_Temp + 1))){
		if(FALSE == modeManual){
			velocity = default_Vel;
		}
	}

	if(TRUE == modeManual){

	}

	default_Vel = velocity;
	default_Temp = temperature;

	return velocity;
}

