/* parseReportedTime.c */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "kiosk.h"

/*
 * The "reported time" is the date and time embedded in the METAR/TAF file itself.
 * It is always the first line of the file, is in the format YYYY/MM/DD HH:MM, and
 * is the UTC time.
 *
 * The time is also reported in the METAR/TAF element ending with the letter "Z", 
 * which is the code for "Zulu Time". Zulu time is the same thing as UTC time.
 *
 * This function parses the reported time. The function parseZulu.c parses the
 * Zulu time.
 *
 * */

void parseReportedTime(WEATHER_REPORT *rpt)
{
	int day, month, year, hour, minute;
	char buf[8];

	if (strlen(rpt->currNode->code) == 10)
	{
		buf[0] = rpt->currNode->code[5];
		buf[1] = rpt->currNode->code[6];
		buf[2] = 0x00;
		month = atoi(buf);

		buf[0] = rpt->currNode->code[8];
		buf[1] = rpt->currNode->code[9];
		buf[2] = 0x00;
		day = atoi(buf);
		
		buf[0] = rpt->currNode->code[0];
		buf[1] = rpt->currNode->code[1];
		buf[2] = rpt->currNode->code[2];
		buf[3] = rpt->currNode->code[3];
		buf[4] = 0x00;
		year = atoi(buf);

		rpt->reported_time.tm_mon = month - 1;
		rpt->reported_time.tm_mday = day;
		rpt->reported_time.tm_year = year - 1900;
	}
	else
	{
		buf[0] = rpt->currNode->code[0];
		buf[1] = rpt->currNode->code[1];
		buf[3] = 0x00;
		hour = atoi(buf);

		buf[0] = rpt->currNode->code[3];
		buf[1] = rpt->currNode->code[4];
		buf[3] = 0x00;
		minute = atoi(buf);
		
		month = rpt->reported_time.tm_mon + 1;
		day = rpt->reported_time.tm_mday;
		year = rpt->reported_time.tm_year + 1900;
		sprintf(rpt->currNode->text, "%02d/%02d/%d %02d:%02d %s", month, day, year, hour, minute, "UTC");
		strcpy(rpt->currNode->caption, "REPORT TIME");		
		rpt->reported_time.tm_hour = hour;
		rpt->reported_time.tm_min = minute;
	}
}
