/*
 * ADC.c
 *
 *  Created on: Oct 12, 2017
 *      Author: Andres Hernandez
 */

#include "ADC.h"

static void ADC_enable(ADC_ChannelType channel){
	switch(channel){
	case ADC_0:
        SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
        break;
	case ADC_1:
		SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;
		break;
	default:
		break;
	}
}

static void ADC_clkDivide(ADC_ChannelType channel, ADC_ClkDivType clkdivide){
	switch(clkdivide){
	case ADC_CLK1:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(0);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(0);
		}
		break;
	case ADC_CLK2:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(1);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(1);
		}
		break;
	case ADC_CLK4:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(2);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(2);
		}
		break;
	case ADC_CLK8:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(3);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(3);
		}
		break;
	default:
		break;
	}
}

static void ADC_sampleTime(ADC_ChannelType channel, ADC_SampleTimeType sample){
	switch(channel){
	case ADC_0:
		if(ADC_SHORT == sample){
			ADC0->CFG1 &= ~(ADC_CFG1_ADLSMP_MASK);
		}
		if(ADC_LONG == sample){
			ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;
		}
		break;
	case ADC_1:
		if(ADC_SHORT == sample){
			ADC1->CFG1 &= ~(ADC_CFG1_ADLSMP_MASK);
		}
		if(ADC_LONG == sample){
			ADC1->CFG1 |= ADC_CFG1_ADLSMP_MASK;
		}
		break;
	default:
		break;
	}
}

static void ADC_conversionMode(ADC_ChannelType channel, ADC_ConverModeType mode){
	switch(mode){
	case ADC_CONVER_8B:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_MODE(0);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_MODE(0);
		}
		break;
	case ADC_CONVER_10B:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_MODE(1);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_MODE(1);
		}
		break;
	case ADC_CONVER_12B:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_MODE(2);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_MODE(2);
		}
		break;
	case ADC_CONVER_16B:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_MODE(3);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_MODE(3);
		}
		break;
	default:
		break;
	}
}

static void ADC_inputClk(ADC_ChannelType channel, ADC_InputClkType clk){
	switch(clk){
	case ADC_BUS_CLK:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADICLK(0);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADICLK(0);
		}
		break;
	case ADC_ALT_CLK2:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADICLK(1);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADICLK(1);
		}
		break;
	case ADC_ALT_CLK1:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADICLK(2);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADICLK(2);
		}
		break;
	case ADC_ADACK:
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADICLK(3);
		}
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADICLK(3);
		}
		break;
	default:
		break;
	}
}

static void ADC_hardwareAverage(ADC_ChannelType channel, ADC_HwAverageType hwAverage){
	switch(hwAverage){
	case ADC_HW_DISABLE:
		if(ADC_0 == channel){
			ADC0->SC3 &= ~(ADC_SC3_AVGE_MASK);
		}
		if(ADC_1 == channel){
			ADC1->SC3 &= ~(ADC_SC3_AVGE_MASK);
		}
		break;
	case ADC_HW_ENABLE:
		if(ADC_0 == channel){
			ADC0->SC3 |= ADC_SC3_AVGE_MASK;
		}
		if(ADC_1 == channel){
			ADC1->SC3 |= ADC_SC3_AVGE_MASK;
		}
		break;
	default:
		break;
	}
}

static void ADC_hardwareSelect(ADC_ChannelType channel, ADC_HwSelectType hwSelect){
	switch(hwSelect){
	case ADC_SAMPLE4:
		if(ADC_0 == channel){
			ADC0->SC3 |= ADC_SC3_AVGS(0);
		}
		if(ADC_1 == channel){
			ADC1->SC3 |= ADC_SC3_AVGS(0);
		}
		break;
	case ADC_SAMPLE8:
		if(ADC_0 == channel){
			ADC0->SC3 |= ADC_SC3_AVGS(1);
		}
		if(ADC_1 == channel){
			ADC1->SC3 |= ADC_SC3_AVGS(1);
		}
		break;
	case ADC_SAMPLE16:
		if(ADC_0 == channel){
			ADC0->SC3 |= ADC_SC3_AVGS(2);
		}
		if(ADC_1 == channel){
			ADC1->SC3 |= ADC_SC3_AVGS(2);
		}
		break;
	case ADC_SAMPLE32:
		if(ADC_0 == channel){
			ADC0->SC3 |= ADC_SC3_AVGS(3);
		}
		if(ADC_1 == channel){
			ADC1->SC3 |= ADC_SC3_AVGS(3);
		}
		break;
	default:
		break;
	}

}

static void ADC_inputChannel(ADC_ChannelType channel, ADC_InputChannelType input){
	switch(channel){
	case ADC_0:
		if(ADC_INPUT_DADP0 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(0);
		}
		if(ADC_INPUT_DADP1 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(1);
		}
		if(ADC_INPUT_DADP2 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(2);
		}
		if(ADC_INPUT_DADP3 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(3);
		}
		if(ADC_INPUT_AD4 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(4);
		}
		if(ADC_INPUT_AD5 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(5);
		}
		if(ADC_INPUT_AD6 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(6);
		}
		if(ADC_INPUT_AD7 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(7);
		}
		if(ADC_INPUT_AD8 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(8);
		}
		if(ADC_INPUT_AD9 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(9);
		}
		if(ADC_INPUT_AD10 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(10);
		}
		if(ADC_INPUT_AD11 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(11);
		}
		if(ADC_INPUT_AD12 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(12);
		}
		if(ADC_INPUT_AD13 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(13);
		}
		if(ADC_INPUT_AD14 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(14);
		}
		if(ADC_INPUT_AD15 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(15);
		}
		if(ADC_INPUT_AD16 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(16);
		}
		if(ADC_INPUT_AD17 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(17);
		}
		if(ADC_INPUT_AD18 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(18);
		}
		if(ADC_INPUT_AD19 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(19);
		}
		if(ADC_INPUT_AD20 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(20);
		}
		if(ADC_INPUT_AD21 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(21);
		}
		if(ADC_INPUT_AD22 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(22);
		}
		if(ADC_INPUT_AD23 == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(23);
		}
		if(ADC_INPUT_TEMPSENSOR == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(26);}

		if(ADC_INPUT_BANDGAP == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(27);
		}
		if(ADC_INPUT_VREFSH == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(29);
		}
		if(ADC_INPUT_VREFSL == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(30);
		}
		if(ADC_INPUT_DISABLE == input){
			ADC0->SC1[0] = ADC_SC1_ADCH(31);
		}
		break;
	case ADC_1:
		if(ADC_INPUT_DADP0 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(0);
		}
		if(ADC_INPUT_DADP1 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(1);
		}
		if(ADC_INPUT_DADP2 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(2);
		}
		if(ADC_INPUT_DADP3 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(3);
		}
		if(ADC_INPUT_AD4 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(4);
		}
		if(ADC_INPUT_AD5 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(5);
		}
		if(ADC_INPUT_AD6 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(6);
		}
		if(ADC_INPUT_AD7 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(7);
		}
		if(ADC_INPUT_AD8 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(8);
		}
		if(ADC_INPUT_AD9 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(9);
		}
		if(ADC_INPUT_AD10 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(10);
		}
		if(ADC_INPUT_AD11 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(11);
		}
		if(ADC_INPUT_AD12 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(12);
		}
		if(ADC_INPUT_AD13 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(13);
		}
		if(ADC_INPUT_AD14 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(14);
		}
		if(ADC_INPUT_AD15 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(15);
		}
		if(ADC_INPUT_AD16 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(16);
		}
		if(ADC_INPUT_AD17 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(17);
		}
		if(ADC_INPUT_AD18 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(18);
		}
		if(ADC_INPUT_AD19 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(19);
		}
		if(ADC_INPUT_AD20 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(20);
		}
		if(ADC_INPUT_AD21 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(21);
		}
		if(ADC_INPUT_AD22 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(22);
		}
		if(ADC_INPUT_AD23 == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(23);
		}
		if(ADC_INPUT_TEMPSENSOR == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(26);
		}
		if(ADC_INPUT_BANDGAP == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(27);
		}
		if(ADC_INPUT_VREFSH == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(29);
		}
		if(ADC_INPUT_VREFSL == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(30);
		}
		if(ADC_INPUT_DISABLE == input){
			ADC1->SC1[0] = ADC_SC1_ADCH(31);
		}
		break;
	default:
		break;
	}
}


uint32 ADC_calculateResult(const ADC_ConfigType* ADC_Config){
	uint32 result;

	ADC_inputChannel(ADC_Config->ADC_Channel, ADC_Config->ADC_InputChannel);

	while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	result = ADC0->R[0];
    return (result);
}

void ADC_init(const ADC_ConfigType* ADC_Config){
	ADC_enable(ADC_Config->ADC_Channel);
	ADC_clkDivide(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_ClkDiv);
	ADC_sampleTime(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_SampleTime);
	ADC_conversionMode(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_ConverMode);
	ADC_inputClk(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_InputClk);
	ADC_hardwareAverage(ADC_Config->ADC_Channel, ADC_Config->ADC_HwAverage);
	ADC_hardwareSelect(ADC_Config->ADC_Channel, ADC_Config->ADC_HwSelect);
}
