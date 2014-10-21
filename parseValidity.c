/* parseValidity.c */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "kiosk.h"

const char *ord[] = {"", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", 
	"10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", 
	"21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th", "31st"};

/* Forecast validity period in DDHH format */

void parseValidity(WEATHER_REPORT *rpt)
{
	int day1, hour1, day2, hour2;
	char buf[4];

	/* Day 1 */	
	buf[0] = rpt->currNode->code[0];
	buf[1] = rpt->currNode->code[1];
	buf[2] = 0x00;
	day1 = atoi(buf);

	/* Hour 1 */
	buf[0] = rpt->currNode->code[2];
	buf[1] = rpt->currNode->code[3];
	buf[2] = 0x00;
	hour1 = atoi(buf);

	/* Day 2 */
	buf[0] = rpt->currNode->code[5];
	buf[1] = rpt->currNode->code[6];
	buf[2] = 0x00;
	day2 = atoi(buf);

	/* Hour 2 */
	buf[0] = rpt->currNode->code[7];
	buf[1] = rpt->currNode->code[8];
	buf[2] = 0x00;
	hour2 = atoi(buf);

	sprintf(rpt->currNode->text, "Valid From %s at %02d:00 to the %s at %02d:00 UTC", ord[day1], hour1, ord[day2], hour2);
}
