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

	if(current_Value >= limit_Conf){
		GPIO_clearPIN(GPIO_C,BIT4);
	}else{
		GPIO_setPIN(GPIO_C,BIT4);
	}
}

void Buzzer_init(){
	static GPIO_pinControlRegisterType pinControlRegisterPortA = GPIO_MUX1;

	GPIO_clockGating(GPIO_C);

	GPIO_pinControlRegister(GPIO_C,BIT4,&pinControlRegisterPortA);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT4);
	GPIO_writePORT(GPIO_C,BIT4);
}

float Conversion_Fahrenheit(uint32 celsius_Temp){

	float fahrenheit_Temp;

	fahrenheit_Temp = ((float)(celsius_Temp*9)/5) + 32;
	return (fahrenheit_Temp);
}

uint32 Control_Velocity(uint32 temperature, uint8 increment, uint8 modeManual, uint32 motor){

	const uint32 limit_Vel = 85;
	static uint32 default_Temp = 20;
	static uint32 default_Vel = 80;
	uint32 diff_Temp;
	sint32 velocity;
	uint32 constant_Increment;
	uint32 mod_Temp;

	mod_Temp =  temperature % 2;
	default_Vel = motor;

	if((temperature > (default_Temp + 1)) && (FALSE == modeManual)){

		if(mod_Temp == 1){temperature -= 1;}

		if(temperature < default_Temp){
			diff_Temp = default_Temp - temperature;
		}else{
			diff_Temp = temperature - default_Temp;
		}

		constant_Increment = diff_Temp / 2;

		velocity = (default_Vel)-(constant_Increment*increment);

		if(velocity <= 0){
			velocity = 0;
		}
	}
	if((temperature < (default_Temp - 1)) && (FALSE == modeManual)){

		if(mod_Temp == 1){temperature -= 1;}

		if(temperature < default_Temp){
			diff_Temp = default_Temp - temperature;
		}else{
			diff_Temp = temperature - default_Temp;
		}
		constant_Increment = diff_Temp / 2;

		velocity = (default_Vel)+(constant_Increment*increment);

		if(velocity >= limit_Vel){
			velocity = limit_Vel;
		}
	}
	if((temperature >= (default_Temp - 1)) && (temperature <= (default_Temp + 1))){
		if(FALSE == modeManual){
			velocity = default_Vel;
			temperature = default_Temp;
		}
	}

	default_Temp = temperature;
	default_Vel = velocity;

	return (velocity);
}

uint32 Control_ManualVelocity(uint32 velocity, uint8 increment, uint8 modeIncrement){

	const sint32 limit_Max = 85;
	const sint32 limit_Min = 0;

	static sint32 default_Velocity;

	default_Velocity = velocity;

	if(FALSE == modeIncrement){
		default_Velocity -= increment;
	}
	if(TRUE == modeIncrement){
		default_Velocity += increment;
	}

	if(default_Velocity < limit_Min){default_Velocity = limit_Min;}
	if(default_Velocity > limit_Max){default_Velocity = limit_Max;}

	return (default_Velocity);
}


uint32 Calculate_Frequency(uint16 value){

	const sint16 Range10K = 2100;
	const sint16 Range15K = 1400;
	const sint16 Range20K = 1024;
	const sint16 Range25K = 840;
	const sint16 Range30K = 700;
	const sint16 Range35K = 600;
	const sint16 Range40K = 525;
	const sint16 Range45K = 466;
	const sint16 Range50K = 420;
	const sint16 Range55K = 381;
	const sint16 Range60K = 350;
	const sint16 Range65K = 323;
	const sint16 Range70K = 300;
	const sint16 Range75K = 280;
	const sint16 Range80K = 262;
	const sint16 Range85K = 247;
	const sint16 Range90K = 233;
	const sint16 Range95K = 221;
	const sint16 Range100K = 210;


	static uint32 frequency = 0;

	if((value > 200)&&(value < 2150)){
		if((value > Range10K - 250) && (value < Range10K + 250)){
			frequency = 10000;
		}
		if((value > Range15K - 200) && (value < Range15K + 200)){
			frequency = 15000;
		}
		if((value > Range20K - 200) && (value < Range20K + 200)){
			frequency = 20000;
		}
		if((value > Range25K - 200) && (value < Range25K + 200)){
			frequency = 25000;
		}
		if((value > Range30K - 150) && (value < Range30K + 150)){
			frequency = 30000;
		}
		if((value > Range35K - 100) && (value < Range35K + 100)){
			frequency = 35000;
		}
		if((value > Range40K - 100) && (value < Range40K + 100)){
			frequency = 40000;
		}
		if((value > Range45K - 50) && (value < Range45K + 50)){
			frequency = 45000;
		}
		if((value > Range50K - 50) && (value < Range50K + 50)){
			frequency = 50000;
		}
		if((value > Range55K - 25) && (value < Range55K + 25)){
			frequency = 55000;
		}
		if((value > Range60K - 25) && (value < Range60K + 25)){
			frequency = 60000;
		}
		if((value > Range65K - 25) && (value < Range65K + 25)){
			frequency = 65000;
		}
		if((value > Range70K - 25) && (value < Range70K + 25)){
			frequency = 70000;
		}
		if((value > Range75K - 20) && (value < Range75K + 20)){
			frequency = 75000;
		}
		if((value > Range80K - 20) && (value < Range80K + 20)){
			frequency = 80000;
		}
		if((value > Range85K - 20) && (value < Range85K - 20)){
			frequency = 85000;
		}
		if((value > Range90K - 20) && (value < Range90K + 20)){
			frequency = 90000;
		}
		if((value > Range95K - 15) && (value < Range95K + 15)){
			frequency = 95000;
		}
		if((value > Range100K - 15) && (value < Range100K + 15)){
			frequency = 100000;
		}
	}else{
		frequency = 0;
	}
	return frequency;
}

