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


	const uint8 DefaultMenu1[]="Velocidad";
	const uint8 DefaultMenu2[]=" 80%";
	const uint8 DefaultMenu3[]="Temperatura";
	const uint8 DefaultMenu4[]=" 20'C";

	const uint8 MainMenu1[]="1)Alarma";
	const uint8 MainMenu2[]="2)Format tmp";
	const uint8 MainMenu3[]="3)% de inc";
	const uint8 MainMenu4[]="4)Ctrl Mnl";
	const uint8 MainMenu5[]="5)Frec";

	const uint8 AlarmMenu1[]="Alarma";
	const uint8 AlarmMenu2[]=" '";
	const uint8 AlarmMenu3[]="(-)B1(+)B2";
	const uint8 AlarmMenu4[]="(OK)B3";

	const uint8 FormatMenu1[]="Format tmp";
	const uint8 FormatMenu2[]="Temp = 'C";
	const uint8 FormatMenu3[]="(C)B1(F)B2";
	const uint8 FormatMenu4[]="(OK)B3";

	const uint8 IncMenu1[]="% de Inc";
	const uint8 IncMenu2[]=" %";
	const uint8 IncMenu3[]="(-)B1";
	const uint8 IncMenu4[]="(+)B2(OK)B3";

	const uint8 ManualMenu1[]="Ctrl Manual";
	const uint8 ManualMenu2[]=" %";
	const uint8 ManualMenu3[]="(ON)B1";
	const uint8 ManualMenu4[]="(OFF)B2";
	const uint8 ManualMenu5[]="(OK)B3";
	const uint8 ManualMenu6[]="(-)B4(+)B5";

	const uint8 FrequencyMenu1[]="Frecuencia";
	const uint8 FrequencyMenu2[]="(Hz)";
	const uint8 FrequencyMenu3[]=" ";




	const uint8 *Sub_ArrayStrings1[4]= {
			DefaultMenu1,
			DefaultMenu2,
			DefaultMenu3,
			DefaultMenu4
	};

	const uint8 *Sub_ArrayStrings2[5]= {
			MainMenu1,
			MainMenu2,
			MainMenu3,
			MainMenu4,
			MainMenu5
	};

	const uint8 *Sub_ArrayStrings3[4]= {
			AlarmMenu1,
			AlarmMenu2,
			AlarmMenu3,
			AlarmMenu4
	};

	const uint8 *Sub_ArrayStrings4[4]= {
			FormatMenu1,
			FormatMenu2,
			FormatMenu3,
			FormatMenu4
	};

	const uint8 *Sub_ArrayStrings5[4]= {
			IncMenu1,
			IncMenu2,
			IncMenu3,
			IncMenu4
	};

	const uint8 *Sub_ArrayStrings6[6]= {
			ManualMenu1,
			ManualMenu2,
			ManualMenu3,
			ManualMenu4,
			ManualMenu5,
			ManualMenu6
	};

	const uint8 *Sub_ArrayStrings7[3]= {
			FrequencyMenu1,
			FrequencyMenu2,
			FrequencyMenu3
	};

#endif /* MENU_H_ */
