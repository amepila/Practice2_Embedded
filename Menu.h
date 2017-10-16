/*
 * Menu.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Andres Hernandez
 */

#ifndef MENU_H_
#define MENU_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "Buttons.h"
#include "SPI.h"


	uint8 DefaultMenu1[]="Velocidad";
	uint8 DefaultMenu2[]=" %";
	uint8 DefaultMenu3[]="Temperatura";
	uint8 DefaultMenu4[]=" 'C";

	uint8 MainMenu1[]="1)Alarma";
	uint8 MainMenu2[]="2)Formato temp";
	uint8 MainMenu3[]="3)% de inc";
	uint8 MainMenu4[]="4)Ctrl manual";
	uint8 MainMenu5[]="5)Frecuencimetro";

	uint8 AlarmMenu1[]="Alarma";
	uint8 AlarmMenu2[]=" '";
	uint8 AlarmMenu3[]="(-)B1 (+)B2 (OK)B3";

	uint8 FormatMenu1[]="Formato temp";
	uint8 FormatMenu2[]="Temp = 'C";
	uint8 FormatMenu3[]="(C)B1 (F)B2 (OK)B3";

	uint8 IncMenu1[]="% de Inc";
	uint8 IncMenu2[]=" %";
	uint8 IncMenu3[]="(-)B1 (+)B2 (OK)B3";

	uint8 ManualMenu1[]="Ctrl Manual";
	uint8 ManualMenu2[]=" %";
	uint8 ManualMenu3[]="(ON)B1 (OFF)B2 (OK)B3";
	uint8 ManualMenu4[]="(-)B4 (+)B5";

	uint8 FrequencyMenu1[]="Frecuencia";
	uint8 FrequencyMenu2[]="(Hz)";
	uint8 FrequencyMenu3[]=" ";





	uint8 *Sub_ArrayStrings1[4]= {
			DefaultMenu1,
			DefaultMenu2,
			DefaultMenu3,
			DefaultMenu4
	};

	uint8 *Sub_ArrayStrings2[5]= {
			MainMenu1,
			MainMenu2,
			MainMenu3,
			MainMenu4,
			MainMenu5
	};

	uint8 *Sub_ArrayStrings3[3]= {
			AlarmMenu1,
			AlarmMenu2,
			AlarmMenu3
	};

	uint8 *Sub_ArrayStrings4[3]= {
			FormatMenu1,
			FormatMenu2,
			FormatMenu3
	};

	uint8 *Sub_ArrayStrings5[3]= {
			IncMenu1,
			IncMenu2,
			IncMenu3
	};

	uint8 *Sub_ArrayStrings6[4]= {
			ManualMenu1,
			ManualMenu2,
			ManualMenu3,
			ManualMenu4
	};

	uint8 *Sub_ArrayStrings7[3]= {
			FrequencyMenu1,
			FrequencyMenu2,
			FrequencyMenu3
	};



	uint8 **Array_Strings[7] = {
			Sub_ArrayStrings1,
			Sub_ArrayStrings2,
			Sub_ArrayStrings3,
			Sub_ArrayStrings4,
			Sub_ArrayStrings5,
			Sub_ArrayStrings6,
			Sub_ArrayStrings7
	};


#endif /* MENU_H_ */
