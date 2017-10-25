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
	uint8 DefaultMenu2[]=" ";
	uint8 DefaultMenu3[]="Temperatura";
	uint8 DefaultMenu4[]=" ";

	uint8 MainMenu1[]="1)Alarma";
	uint8 MainMenu2[]="2)Format tmp";
	uint8 MainMenu3[]="3)% de inc";
	uint8 MainMenu4[]="4)Ctrl Mnl";
	uint8 MainMenu5[]="5)Frec";

	uint8 AlarmMenu1[]="Alarma";
	uint8 AlarmMenu2[]=" ";
	uint8 AlarmMenu3[]="(-)B1(+)B2";
	uint8 AlarmMenu4[]="(OK)B3";

	uint8 FormatMenu1[]="Format tmp";
	uint8 FormatMenu2[]="Temp= ";
	uint8 FormatMenu3[]="(C)B1(F)B2";
	uint8 FormatMenu4[]="(OK)B3";

	uint8 IncMenu1[]="% de Inc";
	uint8 IncMenu2[]=" ";
	uint8 IncMenu3[]="(-)B1";
	uint8 IncMenu4[]="(+)B2(OK)B3";

	uint8 ManualMenu1[]="Ctrl Manual";
	uint8 ManualMenu2[]=" ";
	uint8 ManualMenu3[]="(ON)B1";
	uint8 ManualMenu4[]="(OFF)B2";
	uint8 ManualMenu5[]="(OK)B3";
	uint8 ManualMenu6[]="(-)B4(+)B5";

	uint8 FrequencyMenu1[]="Frecuencia";
	uint8 FrequencyMenu2[]="(Hz)";
	uint8 FrequencyMenu3[]="";


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

	uint8 *Sub_ArrayStrings3[4]= {
			AlarmMenu1,
			AlarmMenu2,
			AlarmMenu3,
			AlarmMenu4
	};

	uint8 *Sub_ArrayStrings4[4]= {
			FormatMenu1,
			FormatMenu2,
			FormatMenu3,
			FormatMenu4
	};

	uint8 *Sub_ArrayStrings5[4]= {
			IncMenu1,
			IncMenu2,
			IncMenu3,
			IncMenu4
	};

	uint8 *Sub_ArrayStrings6[6]= {
			ManualMenu1,
			ManualMenu2,
			ManualMenu3,
			ManualMenu4,
			ManualMenu5,
			ManualMenu6
	};

	uint8 *Sub_ArrayStrings7[2]= {
			FrequencyMenu1,
			FrequencyMenu2,
			FrequencyMenu3
	};

#endif /* MENU_H_ */
