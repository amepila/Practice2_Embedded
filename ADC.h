/*
 * ADC.h
 *
 *  Created on: Oct 12, 2017
 *      Author: Andres Hernandez
 */

#ifndef ADC_H_
#define ADC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/*Type to define the ADC modules*/
typedef enum{ADC_0, ADC_1}ADC_ChannelType;

typedef enum{ADC_CLK1,ADC_CLK2,ADC_CLK4,ADC_CLK8}ADC_ClkDivType;

typedef enum{ADC_SHORT,ADC_LONG}ADC_SampleTimeType;

typedef enum{ADC_CONVER_8B,
			ADC_CONVER_10B,
			ADC_CONVER_12B,
			ADC_CONVER_16B
			}ADC_ConverModeType;

typedef enum{ADC_BUS_CLK,
			ADC_ALT_CLK2,
			ADC_ALT_CLK1,
			ADC_ADACK
			}ADC_InputClkType;

typedef enum{ADC_HW_DISABLE,ADC_HW_ENABLE}ADC_HwAverageType;

typedef enum{ADC_SAMPLE4,
			ADC_SAMPLE8,
			ADC_SAMPLE16,
			ADC_SAMPLE32
			}ADC_HwSelectType;

typedef enum{ADC_INPUT_DADP0,
			ADC_INPUT_DADP1,
			ADC_INPUT_DADP2,
			ADC_INPUT_DADP3,
			ADC_INPUT_AD4,
			ADC_INPUT_AD5,
			ADC_INPUT_AD6,
			ADC_INPUT_AD7,
			ADC_INPUT_AD8,
			ADC_INPUT_AD9,
			ADC_INPUT_AD10,
			ADC_INPUT_AD11,
			ADC_INPUT_AD12,
			ADC_INPUT_AD13,
			ADC_INPUT_AD14,
			ADC_INPUT_AD15,
			ADC_INPUT_AD16,
			ADC_INPUT_AD17,
			ADC_INPUT_AD18,
			ADC_INPUT_AD19,
			ADC_INPUT_AD20,
			ADC_INPUT_AD21,
			ADC_INPUT_AD22,
			ADC_INPUT_AD23,
			ADC_INPUT_TEMPSENSOR,
			ADC_INPUT_BANDGAP,
			ADC_INPUT_VREFSH,
			ADC_INPUT_VREFSL,
			ADC_INPUT_DISABLE
			}ADC_InputChannelType;

typedef struct{
	ADC_ClkDivType ADC_ClkDiv;
	ADC_SampleTimeType ADC_SampleTime;
	ADC_ConverModeType ADC_ConverMode;
	ADC_InputClkType ADC_InputClk;
}ADC_ConfReg1Type;

/*Type to define the ADC configuration*/
typedef struct{
	ADC_ChannelType ADC_Channel;
	ADC_ConfReg1Type ADC_ConfReg1;
	ADC_HwAverageType ADC_HwAverage;
	ADC_HwSelectType ADC_HwSelect;
	ADC_InputChannelType ADC_InputChannel;
}ADC_ConfigType;

uint32 ADC_calculateResult(const ADC_ConfigType*);

void ADC_init(const ADC_ConfigType*);


#endif /* ADC_H_ */
