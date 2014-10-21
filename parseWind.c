/* parseWind.c */

/*
 * Wind speed and direction
 * ^[0-9][0-9][0-9][0-9][0-9]KT
 *
 * Wind with gusts
 * ^[0-9][0-9][0-9][0-9][0-9]G[0-9][0-9]KT
 *
 * Variable winds
 * ^VRB[0-9][0-9]KT
 *
 * */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseWind(WEATHER_REPORT *rpt)
{
	char buf[8], direction[8], mph[16], gust_mph[16], tmp[16];
	int knots, gust_knots = 0;

	/* Variable winds */
	if (rpt->currNode->code[0] == 'V' && rpt->currNode->code[1] == 'R' && rpt->currNode->code[2] == 'B')
	{
		buf[0] = rpt->currNode->code[3];
		buf[1] = rpt->currNode->code[4];
		buf[2] = 0x00;
		knots = atoi(buf);
		sprintf(mph, "%6.1f", knots * 1.15078);
		sprintf(rpt->currNode->text, "Wind variable at %s mph (%d knots)", rtrim(mph, tmp, 10), knots);
		return;
	}
	
	/* Wind gusts */
	if (strlen(rpt->currNode->code) == 10)
	{
		buf[0] = rpt->currNode->code[6];
		buf[1] = rpt->currNode->code[7];
		buf[2] = 0x00;
		gust_knots = atoi(buf);
		sprintf(gust_mph, "%6.1f", gust_knots * 1.15078);
	}

	/* Wind velocity */
	buf[0] = rpt->currNode->code[0];
	buf[1] = rpt->currNode->code[1];
	buf[2] = rpt->currNode->code[2];
	buf[3] = 0x00;
	windfrom(buf, direction);
	buf[0] = rpt->currNode->code[3];
	buf[1] = rpt->currNode->code[4];
	buf[2] = 0x00;
	knots = atoi(buf);
	sprintf(mph, "%6.1f", knots * 1.15078);
	
	if (gust_knots > 0)
		sprintf(rpt->currNode->text, "Wind from the %s at %s mph, gusts up to %s mph", direction, rtrim(mph, tmp, 10), rtrim(gust_mph, tmp, 10));
	else
		sprintf(rpt->currNode->text, "Wind from the %s at %s mph (%d knots)", direction, rtrim(mph, tmp, 10), knots);

}

