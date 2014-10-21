/* parseRain.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseRain(WEATHER_REPORT *rpt)
{
	if (rpt->currNode->code[0] == 'R')
		strcpy(rpt->currNode->text, "Rain");
	else
	{
		if (rpt->currNode->code[0] == '-')
			strcpy(rpt->currNode->text, "Light rain");

		if (rpt->currNode->code[0] == '+')
			strcpy(rpt->currNode->text, "Heavy rain");
	}
}

