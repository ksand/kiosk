/* parseClouds.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

/*
 * FEW
 * BKN
 * OVC
 * SCT
 * */

void parseClouds(WEATHER_REPORT *rpt)
{
	int elevation;
	char buf[4];

	buf[0] = rpt->currNode->code[3];
	buf[1] = rpt->currNode->code[4];
	buf[2] = rpt->currNode->code[5];
	buf[3] = 0x00;
	elevation = atoi(buf) * 100;
	
	if (rpt->currNode->code[0] == 'F')
		sprintf(rpt->currNode->text, "Few clouds at %d feet", elevation);
	else 
		if (rpt->currNode->code[0] == 'B')
			sprintf(rpt->currNode->text, "Broken clouds at %d feet", elevation);
		else
			if (rpt->currNode->code[0] == 'O')
				sprintf(rpt->currNode->text, "Overcast at %d feet", elevation);
			else
				sprintf(rpt->currNode->text, "Scattered clouds at %d feet", elevation);
}	
	
