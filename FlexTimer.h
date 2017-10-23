/**
	\file
	\brief
		This is the header file for the FlexTimer divice driver.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_


#include "MK64F12.h"
#include "DataTypeDefinitions.h"


#define FLEX_TIMER_0_CLOCK_GATING 0x01000000

#define FLEX_TIMER_FAULTIE 		0x80
#define FLEX_TIMER_FAULTM_0   	0x00
#define FLEX_TIMER_FAULTM_1   	0x20
#define FLEX_TIMER_FAULTM_2   	0x40
#define FLEX_TIMER_FAULTM_3   	0x60
#define FLEX_TIMER_CAPTEST  	0x10
#define FLEX_TIMER_PWMSYNC  	0x08
#define FLEX_TIMER_WPDIS    	0x04
#define FLEX_TIMER_INIT     	0x02
#define FLEX_TIMER_FTMEN    	0x01

#define FLEX_TIMER_TOF     		0x80
#define FLEX_TIMER_TOIE    		0x40
#define FLEX_TIMER_CPWMS   		0x20
#define FLEX_TIMER_CLKS_0  		0x00
#define FLEX_TIMER_CLKS_1  		0x08
#define FLEX_TIMER_CLKS_2  		0x10
#define FLEX_TIMER_CLKS_3  		0x18
#define FLEX_TIMER_PS_1    		0x00
#define FLEX_TIMER_PS_2    		0x01
#define FLEX_TIMER_PS_4    		0x02
#define FLEX_TIMER_PS_8    		0x03
#define FLEX_TIMER_PS_16    	0x04
#define FLEX_TIMER_PS_32    	0x05
#define FLEX_TIMER_PS_64    	0x06
#define FLEX_TIMER_PS_128    	0x07

#define FLEX_TIMER_PWMLOAD_CH0 	0x01
#define FLEX_TIMER_PWMLOAD_CH1 	0x02
#define FLEX_TIMER_PWMLOAD_CH2 	0x04
#define FLEX_TIMER_PWMLOAD_CH3 	0x08
#define FLEX_TIMER_PWMLOAD_CH4 	0x10
#define FLEX_TIMER_PWMLOAD_CH5 	0x20
#define FLEX_TIMER_PWMLOAD_CH6 	0x40
#define FLEX_TIMER_PWMLOAD_CH7 	0x80
#define FLEX_TIMER_LDOK        	0x200


#define  FLEX_TIMER_DMA   		0x01
#define  FLEX_TIMER_ELSA  		0x04
#define  FLEX_TIMER_ELSB  		0x08
#define  FLEX_TIMER_MSA   		0x10
#define  FLEX_TIMER_MSB   		0x20
#define  FLEX_TIMER_CHIE  		0x40
#define  FLEX_TIMER_CHF   		0x80


typedef enum {FTM_0,FTM_1,FTM_2,FTM_3} FTMmodule;

typedef enum {FTMnC0,FTMnC1,FTMnC2,FTMnC3,FTMnC4,FTMnC5,FTMnC6,FTMnC7} FTMchannel;

typedef enum {ENABLE_WRITEPROTECTION,DISABLE_WRITEPROTECTION} WriteProtection;

typedef enum {DISABLE_FTM,ENABLE_FTM} FTM_enableControl;

typedef enum {NOCLOCK_DISABLE,SYSTEMCLOCK,FIXEDFREQCLOCK,EXTERNALCLOCK} ClockReference;

typedef enum {DISABLE_MSB, ENABLE_MSB} FTM_MSB;

typedef enum {DISABLE_MSA, ENABLE_MSA} FTM_MSA;

typedef enum {DISABLE_ELSA,ENABLE_ELSA}FTM_ELSA;

typedef enum {DISABLE_ELSB, ENABLE_ELSB}FTM_ELSB;

typedef enum {PS_1,PS_2,PS_4,PS_8,PS_16,PS_32,PS_64,PS_128} FTM_Prescaler;

typedef enum {DISABLE_TOIF, ENABLE_TOIF} TimerOverflowInterrupt;

typedef struct {
	WriteProtection WriteProtectionControl;
	ClockReference ClockControl;
	FTM_enableControl FTMEnablerControl;
	FTM_Prescaler PrescalerControl;
	TimerOverflowInterrupt TOIFControl;
	FTM_MSB MSBValue;
	FTM_MSA MSAValue;
	FTM_ELSB ELSBValue;
	FTM_ELSA ELSAValue;
	FTMmodule moduleSelect;
	FTMchannel channelSelect;
} FTM_Config;


/*needed WPDIS
Clock gating
FTMEN
CnSC MSB|ELSB
CnV = duty cycle default would be MOD*.8
SC clock select, Prescaler select
*/

typedef struct{

}FTM_InputConfig;


void GPIOForFTMInit();
void FTM_ClockGating(FTMmodule); //
void FTM_enable(FTMmodule, FTM_enableControl); //
void FTMnWriteProtection(FTMmodule module, WriteProtection writeprotection);//
void FTMnclockReference(FTMmodule module,ClockReference);//
void FTMnPrescaler(FTMmodule module,FTM_Prescaler);//
void FTMnModuloSet(FTMmodule module,uint16);//
void channelModeSelect(FTMmodule module, FTMchannel channel, FTM_MSB,FTM_MSA,FTM_ELSA,FTM_ELSB);
void FlexTimer_updateCHValue(FTMmodule,FTMchannel,float);
void setDutyCycle(FTMmodule,FTMchannel,float percent);
void FlexTimer_OutputInit(const FTM_Config* config,float initValue,uint16 initModuloValue);
uint16 FTMnModuloGet(FTMmodule module);


#endif /* FLEXTIMER_H_ */
