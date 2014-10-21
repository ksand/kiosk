/* parseTimestamp.c */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "kiosk.h"

void parseTimestamp(WEATHER_REPORT *rpt)
{
	int day, hour, minute, month, year;
	time_t t;
	struct tm *ft;

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

	t = rpt->file_time;
	ft = localtime(&t);
	month = ft->tm_mon + 1;
	year = ft->tm_year;
	sprintf(rpt->currNode->text, "%02d/%02d/%d %02d:%02d %s", month, day, year + 1900, hour, minute, "UTC");
}
