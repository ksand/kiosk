/* parseThunderstorm.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseThunderstorm(WEATHER_REPORT *rpt)
{
	char buf[3];
	
	buf[0] = rpt->currNode->code[3];
	buf[1] = rpt->currNode->code[4];
	buf[2] = 0x00;
	sprintf(rpt->currNode->text, "Thunderstorms at %s minutes past the hour", buf);
}

