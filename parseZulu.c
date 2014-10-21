/* parseZulu.c */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "kiosk.h"

/*
 * This function makes a critical assumption, that the reported_time field
 * of the WEATHER_REPORT structure has already been parsed. This should always be
 * the case because reported_time is the first line in a METAR/TAF report
 * so it should always fall first in the order. Future versions should
 * put in a safety check
 *
 * */

void parseZulu(WEATHER_REPORT *rpt)
{
	char buf[4];
	int day, hour, minute, month, year;

	buf[0] = rpt->currNode->code[0];
	buf[1] = rpt->currNode->code[1];
	buf[2] = 0x00;
	day = atoi(buf);

	buf[0] = rpt->currNode->code[2];
	buf[1] = rpt->currNode->code[3];
	buf[2] = 0x00;
	hour = atoi(buf);

	buf[0] = rpt->currNode->code[4];
	buf[1] = rpt->currNode->code[5];
	buf[2] = 0x00;
	minute = atoi(buf);

	month = rpt->reported_time.tm_mon + 1;
	year = rpt->reported_time.tm_year;
	sprintf(rpt->currNode->text, "%02d/%02d/%d %02d:%02d %s", month, day, year + 1900, hour, minute, "UTC");
}
