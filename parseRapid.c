/* parseRapid.c */

#include <string.h>
#include <stdio.h>
#include <time.h>
#include "kiosk.h"

/* Rapid change in weather conditions */

void parseRapid(WEATHER_REPORT *rpt)
{
	time_t t;
	char buf[4];
	struct tm *tmlocal, tmutc;
	
	/* The time used in the NOAA report is UTC */
	buf[0] = rpt->currNode->code[2];
	buf[1] = rpt->currNode->code[3];
	buf[2] = 0x00;
	tmutc.tm_mday = atoi(buf);

	buf[0] = rpt->currNode->code[4];
	buf[1] = rpt->currNode->code[5];
	buf[2] = 0x00;
	tmutc.tm_hour = atoi(buf) - 1;

	buf[0] = rpt->currNode->code[6];
	buf[1] = rpt->currNode->code[7];
	buf[2] = 0x00;
	tmutc.tm_min = atoi(buf);

	tmutc.tm_mon = rpt->reported_time.tm_mon;
	tmutc.tm_year = rpt->reported_time.tm_year;
	tmutc.tm_sec = 0;

	/* Convert UTC to local time */
	putenv("TZ=UTC");
	t = mktime(&tmutc);
	unsetenv("TZ");
	tmlocal = localtime(&t);

	sprintf(rpt->currNode->text, "Changing at %02d/%02d/%d %02d:%02d %s", tmlocal->tm_mon + 1, tmlocal->tm_mday, tmlocal->tm_year + 1900, tmlocal->tm_hour + 1, tmlocal->tm_min, tmlocal->tm_zone);
}

