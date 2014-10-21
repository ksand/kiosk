/* parseAltimeter.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseAltimeter(WEATHER_REPORT *rpt)
{
	float inches;
	char buf[5];

	buf[0] = rpt->currNode->code[1];
	buf[1] = rpt->currNode->code[2];
	buf[2] = rpt->currNode->code[3];
	buf[3] = rpt->currNode->code[4];
	buf[4] = 0x00;
	
	inches = atof(buf) * 0.01;
	sprintf(rpt->currNode->text, "Elevation %f inches of mecrury", inches);
}	
	
