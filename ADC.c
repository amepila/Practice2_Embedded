/*
 * ADC.c
 *
 *  Created on: Oct 12, 2017
 *      Author: Andres Hernandez
 */

#include "ADC.h"

static void ADC_enable(ADC_ChannelType channel){
	/*Selector of the ADC channel*/
	switch(channel){
	/**ADC0 is selected**/
	case ADC_0:
        SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;/**Bit 27 of SIM_SCGC6 is set**/
        break;
     /**ADC1 is selected**/
	case ADC_1:
		SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;/**Bit 27 of SIM_SCG6 is set**/
		break;
	default:
		break;
	}
}

static void ADC_clkDivide(ADC_ChannelType channel, ADC_ClkDivType clkdivide){

	/*Selector of ADC clock divide*/
	switch(clkdivide){
	/**Clock divide 1 is selected**/
	case ADC_CLK1:
		/**ADC0 is selected**/
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(0);/**0 at bit 5 is set**/
		}
		/**ADC0 is selected**/
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(0);/**0 at bit 5 is set**/
		}
		break;
	/**Clock divide 1 is selected**/
	case ADC_CLK2:
		/**ADC0 is selected**/
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(1);/**1 at bit 5 is set**/
		}
		/**ADC1 is selected**/
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(1);/**1 at bit 5 is set**/
		}
		break;
	/**Clock divide 1 is selected**/
	case ADC_CLK4:
		/**ADC0 is selected**/
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(2);/**2 at bit 5 is set**/
		}
		/**ADC1 is selected**/
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(2);/**2 at bit 5 is set**/
		}
		break;
	/**Clock divide 1 is selected**/
	case ADC_CLK8:
		/**ADC0 is selected**/
		if(ADC_0 == channel){
			ADC0->CFG1 |= ADC_CFG1_ADIV(3);/**3 at bit 5 is set**/
		}
		/**ADC0 is selected**/
		if(ADC_1 == channel){
			ADC1->CFG1 |= ADC_CFG1_ADIV(3);/**3 at bit 5 is set**/
		}
		break;
	default:
		break;
	}
}

static void ADC_sampleTime(ADC_ChannelType channel, ADC_SampleTimeType sample){

	/*Selector of ADC channel*/
	switch(channel){
	/**ADC0 is selected**/
	case ADC_0:
		if(ADC_SHORT == sample){
			/**Enable the short sample**/
			ADC0->CFG1 &= ~(ADC_CFG1_ADLSMP_MASK);
		}
		if(ADC_LONG == sample){
			/**Enable the long sample**/
			ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;
		}
		break;
	/**ADC1 is selected**/
	case ADC_1:
		if(ADC_SHORT == sample){
			/**Enable the short sample**/
			ADC1->CFG1 &= ~(ADC_CFG1_ADLSMP_MASK);
		}
		if(ADC_LONG == sample){
			/**Enable the long sample**/
			ADC1->CFG1 |= ADC_CFG1_ADLSMP_MASK;
		}
		break;
	default:
		break;
	}
}

static void ADC_conversionMode(ADC_ChannelType channel, ADC_ConverModeType mode){

	/*Selector of Conversion Mode*/
	switch(mode){
	/**Enable the 8 bits of conversion**/
	case ADC_CONVER_8B:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_MODE(0);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_MODE(0);
		}
		break;
	/**Enable the 10 bits of conversion**/
	case ADC_CONVER_10B:
		if(ADC_0 == channel){
			/**AD0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_MODE(1);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_MODE(1);
		}
		break;
	/**Enable the 12 bits of conversion**/
	case ADC_CONVER_12B:
		if(ADC_0 == channel){
			/**AD0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_MODE(2);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_MODE(2);
		}
		break;
	/**Enable the 16 bits of conversion**/
	case ADC_CONVER_16B:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_MODE(3);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_MODE(3);
		}
		break;
	default:
		break;
	}
}

static void ADC_inputClk(ADC_ChannelType channel, ADC_InputClkType clk){

	/*Selector of input clock*/
	switch(clk){
	/**Bus clock is selected**/
	case ADC_BUS_CLK:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_ADICLK(0);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_ADICLK(0);
		}
		break;
	/**Alt clock 2 is selected**/
	case ADC_ALT_CLK2:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_ADICLK(1);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_ADICLK(1);
		}
		break;
	/**Alt clock 1 is selected**/
	case ADC_ALT_CLK1:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_ADICLK(2);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_ADICLK(2);
		}
		break;
	/**Adack is selected**/
	case ADC_ADACK:
		if(ADC_0 == channel){
			/**AD0 is selected**/
			ADC0->CFG1 |= ADC_CFG1_ADICLK(3);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->CFG1 |= ADC_CFG1_ADICLK(3);
		}
		break;
	default:
		break;
	}
}

static void ADC_hardwareAverage(ADC_ChannelType channel, ADC_HwAverageType hwAverage){

	/*Selector of Hardware Average*/
	switch(hwAverage){
	/**Disable the Hardware Average**/
	case ADC_HW_DISABLE:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->SC3 &= ~(ADC_SC3_AVGE_MASK);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->SC3 &= ~(ADC_SC3_AVGE_MASK);
		}
		break;
	/**Enable the Hardware Average**/
	case ADC_HW_ENABLE:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->SC3 |= ADC_SC3_AVGE_MASK;
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->SC3 |= ADC_SC3_AVGE_MASK;
		}
		break;
	default:
		break;
	}
}

static void ADC_hardwareSelect(ADC_ChannelType channel, ADC_HwSelectType hwSelect){

	/**Selector of number of samples**/
	switch(hwSelect){
	/**Select 4 samples**/
	case ADC_SAMPLE4:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->SC3 |= ADC_SC3_AVGS(0);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->SC3 |= ADC_SC3_AVGS(0);
		}
		break;
	/**Select 8 samples**/
	case ADC_SAMPLE8:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->SC3 |= ADC_SC3_AVGS(1);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->SC3 |= ADC_SC3_AVGS(1);
		}
		break;
	/**Select 16 samples**/
	case ADC_SAMPLE16:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->SC3 |= ADC_SC3_AVGS(2);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->SC3 |= ADC_SC3_AVGS(2);
		}
		break;
	/**Select 32 samples**/
	case ADC_SAMPLE32:
		if(ADC_0 == channel){
			/**ADC0 is selected**/
			ADC0->SC3 |= ADC_SC3_AVGS(3);
		}
		if(ADC_1 == channel){
			/**ADC1 is selected**/
			ADC1->SC3 |= ADC_SC3_AVGS(3);
		}
		break;
	default:
		break;
	}

}

static void ADC_inputChannel(ADC_ChannelType channel, ADC_InputChannelType input){

	/**Selector of input channel**/
	switch(channel){
	/**Select ADC0**/
	case ADC_0:
		if(ADC_INPUT_DADP0 == input){
			/**DAD0 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(0);
		}
		if(ADC_INPUT_DADP1 == input){
			/**DAD1 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(1);
		}
		if(ADC_INPUT_DADP2 == input){
			/**DAD2 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(2);
		}
		if(ADC_INPUT_DADP3 == input){
			/**DAD3 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(3);
		}
		if(ADC_INPUT_AD4 == input){
			/**AD4 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(4);
		}
		if(ADC_INPUT_AD5 == input){
			/**AD5 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(5);
		}
		if(ADC_INPUT_AD6 == input){
			/**AD6 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(6);
		}
		if(ADC_INPUT_AD7 == input){
			/**AD7 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(7);
		}
		if(ADC_INPUT_AD8 == input){
			/**AD8 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(8);
		}
		if(ADC_INPUT_AD9 == input){
			/**AD9 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(9);
		}
		if(ADC_INPUT_AD10 == input){
			/**AD10 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(10);
		}
		if(ADC_INPUT_AD11 == input){
			/**AD11 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(11);
		}
		if(ADC_INPUT_AD12 == input){
			/**AD12 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(12);
		}
		if(ADC_INPUT_AD13 == input){
			/**AD13 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(13);
		}
		if(ADC_INPUT_AD14 == input){
			/**AD14 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(14);
		}
		if(ADC_INPUT_AD15 == input){
			/**AD15 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(15);
		}
		if(ADC_INPUT_AD16 == input){
			/**AD16 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(16);
		}
		if(ADC_INPUT_AD17 == input){
			/**AD17 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(17);
		}
		if(ADC_INPUT_AD18 == input){
			/**AD18 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(18);
		}
		if(ADC_INPUT_AD19 == input){
			/**AD19 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(19);
		}
		if(ADC_INPUT_AD20 == input){
			/**AD20 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(20);
		}
		if(ADC_INPUT_AD21 == input){
			/**AD21 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(21);
		}
		if(ADC_INPUT_AD22 == input){
			/**AD22 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(22);
		}
		if(ADC_INPUT_AD23 == input){
			/**AD23 is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(23);
		}
		if(ADC_INPUT_TEMPSENSOR == input){
			/**Temp sensor is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(26);}

		if(ADC_INPUT_BANDGAP == input){
			/**Bandgap is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(27);
		}
		if(ADC_INPUT_VREFSH == input){
			/**Vrefsh is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(29);
		}
		if(ADC_INPUT_VREFSL == input){
			/**Vrefsl is selected**/
			ADC0->SC1[0] = ADC_SC1_ADCH(30);
		}
		if(ADC_INPUT_DISABLE == input){
			/**Disable input**/
			ADC0->SC1[0] = ADC_SC1_ADCH(31);
		}
		break;
	/**Select ADC1**/
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

	/*Variable that saves the value of the input pin*/
	uint32 result;

	/**Select the input channel to be read**/
	ADC_inputChannel(ADC_Config->ADC_Channel, ADC_Config->ADC_InputChannel);

	/**Wait while the conversion is completed**/
	while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	/**Result saves the value of register that contains the reading sensor**/
	result = ADC0->R[0];
	/*Return the temperature*/
    return (result);
}

void ADC_init(const ADC_ConfigType* ADC_Config){

	/**Enable the channel**/
	ADC_enable(ADC_Config->ADC_Channel);
	/**Selects the clock divide**/
	ADC_clkDivide(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_ClkDiv);
	/**Selects the length of the sample**/
	ADC_sampleTime(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_SampleTime);
	/**Selects the conversion in bits**/
	ADC_conversionMode(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_ConverMode);
	/**Selects the input channel**/
	ADC_inputClk(ADC_Config->ADC_Channel, ADC_Config->ADC_ConfReg1.ADC_InputClk);
	/**Enable the hardware average**/
	ADC_hardwareAverage(ADC_Config->ADC_Channel, ADC_Config->ADC_HwAverage);
	/**Select the sampling number**/
	ADC_hardwareSelect(ADC_Config->ADC_Channel, ADC_Config->ADC_HwSelect);
}
