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
#include "GPIO.h"
#include "Colors.h"
#include <stdio.h>


#define FLEX_TIMER_0_CLOCK_GATING 	0x01000000

#define FLEX_TIMER_FAULTIE  		0x80
#define FLEX_TIMER_FAULTM_0   		0x00
#define FLEX_TIMER_FAULTM_1   		0x20
#define FLEX_TIMER_FAULTM_2   		0x40
#define FLEX_TIMER_FAULTM_3   		0x60
#define FLEX_TIMER_CAPTEST  		0x10
#define FLEX_TIMER_PWMSYNC  		0x08
#define FLEX_TIMER_WPDIS    		0x04
#define FLEX_TIMER_INIT     		0x02
#define FLEX_TIMER_FTMEN    		0x01

#define FLEX_TIMER_TOF     			0x80
#define FLEX_TIMER_TOIE    			0x40
#define FLEX_TIMER_CPWMS   			0x20
#define FLEX_TIMER_CLKS_0  			0x00
#define FLEX_TIMER_CLKS_1  			0x08
#define FLEX_TIMER_CLKS_2  			0x10
#define FLEX_TIMER_CLKS_3  			0x18
#define FLEX_TIMER_PS_1    			0x00
#define FLEX_TIMER_PS_2    			0x01
#define FLEX_TIMER_PS_4    			0x02
#define FLEX_TIMER_PS_8    			0x03
#define FLEX_TIMER_PS_16    		0x04
#define FLEX_TIMER_PS_32    		0x05
#define FLEX_TIMER_PS_64    		0x06
#define FLEX_TIMER_PS_128    		0x07

#define FLEX_TIMER_PWMLOAD_CH0 		0x01
#define FLEX_TIMER_PWMLOAD_CH1 		0x02
#define FLEX_TIMER_PWMLOAD_CH2 		0x04
#define FLEX_TIMER_PWMLOAD_CH3 		0x08
#define FLEX_TIMER_PWMLOAD_CH4 		0x10
#define FLEX_TIMER_PWMLOAD_CH5 		0x20
#define FLEX_TIMER_PWMLOAD_CH6 		0x40
#define FLEX_TIMER_PWMLOAD_CH7 		0x80
#define FLEX_TIMER_LDOK        		0x200


#define  FLEX_TIMER_DMA   			0x01
#define  FLEX_TIMER_ELSA  			0x04
#define  FLEX_TIMER_ELSB  			0x08
#define  FLEX_TIMER_MSA   			0x10
#define  FLEX_TIMER_MSB   			0x20
#define  FLEX_TIMER_CHIE  			0x40
#define  FLEX_TIMER_CHF   			0x80
#define  FLEX_RESET					0x0000

typedef enum {FTM_0,FTM_1,FTM_2,FTM_3} FTMmodule;

typedef enum {FTMnC0,FTMnC1,FTMnC2,FTMnC3,FTMnC4,FTMnC5,FTMnC6,FTMnC7} FTMchannel;

typedef enum {ENABLE_WRITEPROTECTION,DISABLE_WRITEPROTECTION} WriteProtection;

typedef enum {DISABLE_FTM,ENABLE_FTM} FTM_enableControl;

typedef enum {NOCLOCK_DISABLE,SYSTEMCLOCK,FIXEDFREQCLOCK,EXTERNALCLOCK} ClockReference;

typedef enum {DISABLE_MSB, ENABLE_MSB} FTM_MSB;

typedef enum {DISABLE_MSA, ENABLE_MSA} FTM_MSA;

typedef enum {DISABLE_ELSA,ENABLE_ELSA}FTM_ELSA;

typedef enum {DISABLE_ELSB, ENABLE_ELSB}FTM_ELSB;

typedef enum {ChInterrupt_Disable,ChInterrupt_Enable} ChInterrupt;

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
	ChInterrupt ChInterruptControl;
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

/*!
 	 \brief	 This function will setup the necessary pins to their FTM in/out
 	 enable clock gating, and the data direction pin
 	 \param[in]  void.
 	 \return void
 */
void GPIOForFTMInit();
/*!
 	 \brief	 This function will enable the clock gating of the selected FTM module
 	 \param[in]  FTMmodule
 	 \return void
 */
void FTM_ClockGating(FTMmodule);
/*!
 	 \brief	 Enable or disables the access to the FTM memory registers
 	 \param[in]  FTMmodule
 	 \return void
 */
void FTM_enable(FTMmodule, FTM_enableControl);
/*!
 	 \brief Enable or disables the write protection for the selected FTM module
 	 \param[in]  FTMmodule.
 	 \param[in]	 FTM_enableControl
 	 \return void
 */
void FTMnWriteProtection(FTMmodule module, WriteProtection writeprotection);//
/*!
 	 \brief	 Selects the clock that will feed the chosen FTM module.
 	 \param[in]  FTMmodule.
 	 \param[in]	 ClockReference
 	 \return void
 */
void FTMnclockReference(FTMmodule module,ClockReference);//
/*!
 	 \brief Selects the prescaler value for the chosen FTM module.
 	 \param[in]  FTMmodule.
 	 \param[in] ClockReference
 	 \return void
 */
void FTMnPrescaler(FTMmodule module,FTM_Prescaler);
/*!
 	 \brief Loads a value to the modulo of the chosen FTM module.
 	 \param[in]  FTMmodule.
 	 \param[in] uint16 modulo value
 	 \return void
 */
void FTMnModuloSet(FTMmodule module,uint16);//
/*!
 	 \brief Selects the configuration for a chosen channel inside the chosen module
 	 \param[in] FTMmodule
 	 \param[in] FTMchannel
 	 \param[in] FTM_MSB
 	 \param[in] FTM_MSA
 	 \param[in] FTM_ELSB
 	 \param[in] FTM_ELSA
 	 \return void
 */
void channelModeSelect(FTMmodule module, FTMchannel channel, FTM_MSB,FTM_MSA,FTM_ELSA,FTM_ELSB);
/*!
 	 \brief Loads a starting value for the chosen channel in the chosen channel
	 multiplying the mod times a decimal
 	 \param[in]  FTMmodule.
 	 \param[in] float
 	 \return void
 */
void FlexTimer_updateCHValue(FTMmodule,FTMchannel,float);
/*!
 	 \brief Enables the channel interrupt
 	 \param[in]  FTMmodule.
 	 \param[in] FTMchannel
 	 \param[in] ChInterrupt either enable or disable
 	 \return void
 */
void channelInterruptEnable(FTMmodule,FTMchannel,ChInterrupt);
/*!
 	 \brief Set the duty cycle multiplying the modulo times a percentage in float
 	 and storing it at the Channel count value
 	 \param[in]  FTMmodule.
 	 \param[in] FTMchannel
 	 \param[in] float
 	 \return void
 */
void setDutyCycle(FTMmodule,FTMchannel,float percent);
/*!
 	 \brief Initialize the chosen module and channel, with an initial percent, and a chosen
 	 modulo value
 	 \param[in]  FTM_Config* configuration structure that is recieved from the main
 	 \param [in] float the initial percent from the modulo to start the channel count value
 	 \param[in] uint16 The base modulo value
 	 \return void
 */
void FlexTimer_Init(const FTM_Config* config,float initValue,uint16 initModuloValue);
/*!
 	 \brief Get the value of the chosen module modulo
 	 \param[in] FTMmodule
 	 \return void
 */
uint16 FTMnModuloGet(FTMmodule module);
/*!
 	 \brief Get channel interrupt status of the chosen module and channel
 	 \param[in] FTMmodule
 	 \return void
 */
uint8 getChannelInterrupt(FTMmodule module, FTMchannel channel);
/*!
 	 \brief Get the value of CnV (count value) of the chosen module and channel
 	 \param[in] FTMmodule
 	 \param[in] FTMchannel
 	 \return void
 */
uint16 getCountValue(FTMmodule module, FTMchannel channel);
/*!
 	 \brief Set the current count value at channel interrupt
 	 \return void
 */
void setCurrentCountValue(uint16);
/*!
 	 \brief Obtain a control value for the input caputure, this function will return 0
 	 at the first interrupt and 1 at the second, after that the value will reset.
 	 \return uint16
 */
uint16 getControlValueControl();
/*!
 	 \brief Obtain the current count value that will be used for the frequency calculations
 	 \return uint16
 */
uint16 getCurrentCountValue();
uint16 getCnVDifference();

#endif /* FLEXTIMER_H_ */
