/* parsePressure.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parsePressure(WEATHER_REPORT *rpt)
{
	char buf[8];

	buf[0] = '1';
	buf[1] = ',';
	buf[2] = '0';
	buf[3] = rpt->currNode->code[3];
	buf[4] = rpt->currNode->code[4];
	buf[5] = '.';
	buf[6] = rpt->currNode->code[5];
	buf[7] = 0x00;
	sprintf(rpt->currNode->text, "Barometric pressure %s hPa at sea level", buf);
}

