/* parsePrecip.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parsePrecip(WEATHER_REPORT *rpt)
{
	char buf[8];

	buf[0] = rpt->currNode->code[1];
	buf[1] = rpt->currNode->code[2];
	buf[2] = '.';
	buf[3] = rpt->currNode->code[3];
	buf[4] = rpt->currNode->code[4];
	buf[5] = 0x00;
	sprintf(rpt->currNode->text, "Precipitation %s inches in the last hour", buf);
}

