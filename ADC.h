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

/*Data Type to define the ADC modules*/

/**Data Type to choose the ADC channel**/
typedef enum{ADC_0, ADC_1}ADC_ChannelType;
/**Data Type to choose the Clock Divide in the ADC**/
typedef enum{ADC_CLK1,ADC_CLK2,ADC_CLK4,ADC_CLK8}ADC_ClkDivType;
/**Data Type to choose the sample time**/
typedef enum{ADC_SHORT,ADC_LONG}ADC_SampleTimeType;
/**Data Type to choose the conversion mode**/
typedef enum{ADC_CONVER_8B,
			ADC_CONVER_10B,
			ADC_CONVER_12B,
			ADC_CONVER_16B
			}ADC_ConverModeType;
/**Data Type to choose the input clock**/
typedef enum{ADC_BUS_CLK,
			ADC_ALT_CLK2,
			ADC_ALT_CLK1,
			ADC_ADACK
			}ADC_InputClkType;
/**Data type to enable the Hardware average**/
typedef enum{ADC_HW_DISABLE,ADC_HW_ENABLE}ADC_HwAverageType;
/**Data type to choose the sampling**/
typedef enum{ADC_SAMPLE4,
			ADC_SAMPLE8,
			ADC_SAMPLE16,
			ADC_SAMPLE32
			}ADC_HwSelectType;
/**Data Type to elect the input channel**/
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

/**Data type that contains the configuration of ADC-Register 1 **/
typedef struct{
	ADC_ClkDivType ADC_ClkDiv;
	ADC_SampleTimeType ADC_SampleTime;
	ADC_ConverModeType ADC_ConverMode;
	ADC_InputClkType ADC_InputClk;
}ADC_ConfReg1Type;

/*Data Type to define the ADC configuration*/
typedef struct{
	ADC_ChannelType ADC_Channel;
	ADC_ConfReg1Type ADC_ConfReg1;
	ADC_HwAverageType ADC_HwAverage;
	ADC_HwSelectType ADC_HwSelect;
	ADC_InputChannelType ADC_InputChannel;
}ADC_ConfigType;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This enable the ADC channel
 	 \param[in] channel Selected channel
 	 \return void
 */
//static void ADC_enable(ADC_ChannelType channel);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This assigns  the clock divide
 	 \param[in] channel Selected channel
 	 \param[in] clkdivide Selected clock divide
 	 \return void
 */
//static void ADC_clkDivide(ADC_ChannelType channel, ADC_ClkDivType clkdivide);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This assigns the time of the sample
 	 \param[in] channel Selected channel
 	 \param[in] sample	Selected sample
 	 \return void
 */
//static void ADC_sampleTime(ADC_ChannelType channel, ADC_SampleTimeType sample);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This realizes the conversion in bits
 	 \param[in] channel Selected channel
 	 \param[in] mode Selected mode
 	 \return void
 */
//static void ADC_conversionMode(ADC_ChannelType channel, ADC_ConverModeType mode);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This assigns the clock to ADC
 	 \param[in] channel Selected channel
 	 \param[in] clk Selected clock
 	 \return value
 */
//static void ADC_inputClk(ADC_ChannelType channel, ADC_InputClkType clk);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This enables/disables the hardware average
 	 \param[in] channel Selected channel
 	 \param[in] hwAverage Enable/Disable Hardware average
 	 \return void
 */
//static void ADC_hardwareAverage(ADC_ChannelType channel, ADC_HwAverageType hwAverage);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This selects the number of samples
 	 \param[in] channel Selected channel
 	 \param[in] hwSelect Number of samples
 	 \return void
 */
//static void ADC_hardwareSelect(ADC_ChannelType channel, ADC_HwSelectType hwSelect);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This selects the input of ADC
 	 \param[in] channel Selected channel
 	 \param[in] input Selected input
 	 \return void
 */
//static void ADC_inputChannel(ADC_ChannelType channel, ADC_InputChannelType input);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This calculate the result of the device connected in the port
 	 \param[in] ADC_ConfigType* Selected input
 	 \return The ADC value
 */
uint32 ADC_calculateResult(const ADC_ConfigType*);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This initializes the general configuration of ADC
 	 \param[in] ADC_ConfigType* Data of the configuration
 	 \return void
 */
void ADC_init(const ADC_ConfigType*);


#endif /* ADC_H_ */
