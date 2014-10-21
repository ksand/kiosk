/* parseSnow.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseSnow(WEATHER_REPORT *rpt)
{
	if (rpt->currNode->code[0] == 'S')
		strcpy(rpt->currNode->text, "Snow");
	else
	{
		if (rpt->currNode->code[0] == '-')
			strcpy(rpt->currNode->text, "Light snow");

		if (rpt->currNode->code[0] == '+')
			strcpy(rpt->currNode->text, "Heavy snow");
	}
}

