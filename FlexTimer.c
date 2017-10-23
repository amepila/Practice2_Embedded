/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo

 */



#include "FlexTimer.h"
#include "GPIO.h"
#include "MK64F12.h"

void GPIOForFTMInit(){
	GPIO_clockGating(GPIO_B);
	GPIO_clockGating(GPIO_C);
	GPIO_pinControlRegisterType pinControlRegisterPORTC1 = GPIO_MUX4;
	GPIO_pinControlRegisterType pinControlRegisterPORTB18 = GPIO_MUX4;
	GPIO_pinControlRegister(GPIO_B,BIT18,&pinControlRegisterPORTB18);
	GPIO_pinControlRegister(GPIO_C,BIT1,&pinControlRegisterPORTC1);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT1);
	//PIN C 5 FTM0 ch2
	GPIO_dataDirectionPIN(GPIO_B,GPIO_INPUT,BIT18);

}
void FTM_ClockGating(FTMmodule module){
	switch(module){
			case FTM_0:
				SIM->SCGC6|=TRUE<<BIT24;
				break;
			case FTM_1:
				SIM->SCGC6|=TRUE<<BIT25;
				break;

			case FTM_2:
				SIM->SCGC6|=TRUE<<BIT26;
				break;

			case FTM_3:
				SIM->SCGC3|=TRUE<<BIT25;
				break;

			default:
				break;
		}
}

void setDutyCycle(FTMmodule module, FTMchannel channel,float percent){
	switch(module){
		case FTM_0:
			FTM0->CONTROLS[channel].CnV = FTM0->MOD*percent;
			break;
		case FTM_1:
			FTM1->CONTROLS[channel].CnV = FTM1->MOD*percent;
			break;

		case FTM_2:
			FTM2->CONTROLS[channel].CnV = FTM2->MOD*percent;
			break;

		case FTM_3:
			FTM3->CONTROLS[channel].CnV = FTM3->MOD*percent;
			break;

		default:
			break;
	}
}
void FTMnWriteProtection(FTMmodule module,WriteProtection writeprotection){
	switch(module){
			case FTM_0:
				FTM0->MODE|=(writeprotection<<BIT2);
				break;

			case FTM_1:
				FTM1->MODE|=writeprotection<<BIT2;
				break;

			case FTM_2:
				FTM2->MODE|=writeprotection<<BIT2;
				break;

			case FTM_3:
				FTM3->MODE|=writeprotection<<BIT2;
				break;


		}
}
void FTM_enable(FTMmodule module,FTM_enableControl FTMenableValue){

	switch(module){
			case FTM_0:
				FTM0->MODE|=(FTMenableValue<<BIT0);
				break;

			case FTM_1:
				FTM1->MODE|=FTMenableValue<<BIT0;
				break;

			case FTM_2:
				FTM2->MODE|=FTMenableValue<<BIT0;
				break;

			case FTM_3:
				FTM3->MODE|=FTMenableValue<<BIT0;
				break;


		}
}
void FTMnclockReference(FTMmodule module,ClockReference clockReference){
	switch(module){
				case FTM_0:
					FTM0->SC|=clockReference<<BIT3;
					break;

				case FTM_1:
					FTM1->SC|=clockReference<<BIT3;
					break;

				case FTM_2:
					FTM2->SC|=clockReference<<BIT3;
					break;

				case FTM_3:
					FTM3->SC|=clockReference<<BIT3;
					break;


			}
}
void FTMnPrescaler(FTMmodule module,FTM_Prescaler prescaler){
	switch(module){
				case FTM_0:
					FTM0->SC|=prescaler;
					break;

				case FTM_1:
					FTM1->SC|=prescaler;
					break;

				case FTM_2:
					FTM2->SC|=prescaler;
					break;

				case FTM_3:
					FTM3->SC|=prescaler;
					break;


			}
	}
void FTMnModuloSet(FTMmodule module,uint16 modulo){
	switch(module){
				case FTM_0:
					FTM0->MOD=modulo;

					break;

				case FTM_1:
					FTM1->MOD=modulo;
					break;

				case FTM_2:
					FTM2->MOD=modulo;
					break;

				case FTM_3:
					FTM3->MOD=modulo;
					break;
				default:
					break;

			}
}
uint16 FTMnModuloGet(FTMmodule module){
	switch(module){
				case FTM_0:
					return FTM0->MOD;

					break;

				case FTM_1:
					return FTM1->MOD;
					break;

				case FTM_2:
					return FTM2->MOD;
					break;

				case FTM_3:
					return FTM3->MOD;
					break;
				default:
					return 0;
					break;

			}
	return 0;
}

void channelModeSelect(FTMmodule module, FTMchannel channel, FTM_MSB MSB,FTM_MSA MSA,FTM_ELSA ELSA,FTM_ELSB ELSB){
	switch(module){
					case FTM_0:
						FTM0->CONTROLS[channel].CnSC|=(MSB<<BIT5);
						FTM0->CONTROLS[channel].CnSC|=(MSA<<BIT4);
						FTM0->CONTROLS[channel].CnSC|=(ELSB<<BIT3);
						FTM0->CONTROLS[channel].CnSC|=(ELSA<<BIT2);

						break;

					case FTM_1:
						FTM1->CONTROLS[channel].CnSC|=MSB<<BIT5;
						FTM1->CONTROLS[channel].CnSC|=MSA<<BIT4;
						FTM1->CONTROLS[channel].CnSC|=ELSB<<BIT3;
						FTM1->CONTROLS[channel].CnSC|=ELSA<<BIT2;
						break;

					case FTM_2:
						FTM2->CONTROLS[channel].CnSC|=MSB<<BIT5;
						FTM2->CONTROLS[channel].CnSC|=MSA<<BIT4;
						FTM2->CONTROLS[channel].CnSC|=ELSB<<BIT3;
						FTM2->CONTROLS[channel].CnSC|=ELSA<<BIT2;
						break;

					case FTM_3:
						FTM3->CONTROLS[channel].CnSC|=MSB<<BIT5;
						FTM3->CONTROLS[channel].CnSC|=MSA<<BIT4;
						FTM3->CONTROLS[channel].CnSC|=ELSB<<BIT3;
						FTM3->CONTROLS[channel].CnSC|=ELSA<<BIT2;
						break;

				}
}
void FlexTimer_updateCHValue(FTMmodule module,FTMchannel channel,float value){
	switch(module){
					case FTM_0:
						FTM0->CONTROLS[channel].CnV=FTMnModuloGet(module)*value;
						break;

					case FTM_1:
						FTM1->CONTROLS[channel].CnV=FTMnModuloGet(module)*value;
						break;

					case FTM_2:
						FTM2->CONTROLS[channel].CnV=FTMnModuloGet(module)*value;
						break;

					case FTM_3:
						FTM3->CONTROLS[channel].CnV=FTMnModuloGet(module)*value;
						break;

				}
}
void FTM0_ISR()
{
	FTM0->SC &= ~FLEX_TIMER_TOF;
	GPIOD->PDOR ^= 0xFF;
}

void FlexTimer_OutputInit(const FTM_Config* config,float initValue,uint16 initModuloValue){

	FTM_ClockGating(config->moduleSelect);
	GPIOForFTMInit();
	FTMnWriteProtection(config->moduleSelect,config->WriteProtectionControl		);
	FTM_enable(config->moduleSelect,config->FTMEnablerControl);
	FTMnModuloSet(config->moduleSelect,initModuloValue);
	channelModeSelect(config->moduleSelect,config->channelSelect,config->MSBValue,config->MSAValue,config->ELSBValue,config->ELSAValue);
	FlexTimer_updateCHValue(config->moduleSelect,config->channelSelect,initValue);
	FTMnclockReference(config->moduleSelect,config->ClockControl);
	FTMnPrescaler(config->moduleSelect,config->PrescalerControl);
}
