/* parseActivity.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseActivity(WEATHER_REPORT *rpt)
{
	/* AUTO */
	if (strcmp(rpt->currNode->code, "AUTO") == YES)
	{
		strcpy(rpt->currNode->text, "Station has automatic recorders");
		return;
	}

	/* RMK */
	if (strcmp(rpt->currNode->code, "RMK") == YES)
	{
		strcpy(rpt->currNode->text, "Remarks follow...");
		rpt->currNode->remark = true;
		return;
	}

	/* AMD */
	if (strcmp(rpt->currNode->code, "AMD") == YES)
	{
		strcpy(rpt->currNode->text, "Amended forecast follows...");
		return;
	}

	/* TEMPO */
	if (strcmp(rpt->currNode->code, "TEMPO") == YES)
	{
		strcpy(rpt->currNode->text, "Temprary conditions follow...");
		return;
	}

	/* BR (mist) */
	if (strcmp(rpt->currNode->code, "BR") == YES)
	{
		strcpy(rpt->currNode->text, "Mist");
		return;
	}

	/* SKC */
	if (strcmp(rpt->currNode->code, "SKC") == YES)
	{
		strcpy(rpt->currNode->text, "Clear skies");
		return;
	}
	
	/* CLR */
	if (strcmp(rpt->currNode->code, "CLR") == YES)
	{
		strcpy(rpt->currNode->text, "Clear skies");
		return;
	}

	/* -RAPL */
	if (strcmp(rpt->currNode->code, "-RAPL") == YES)
	{
		strcpy(rpt->currNode->text, "Light rain with ice pellets");
		return;
	}
	
	/* -FZRAPL */
	if (strcmp(rpt->currNode->code, "-FZRAPL") == YES)
	{
		strcpy(rpt->currNode->text, "Light freezing rain with ice pellets");
		return;
	}
	
	/* VCSH */
	if (strcmp(rpt->currNode->code, "VCSH") == YES)
	{
		strcpy(rpt->currNode->text, "Precipitation within 16 kilometers (but not at) the aerodrome");
		return;
	}

	/* RASN */
	if (strcmp(rpt->currNode->code, "RASN") == YES)
	{
		strcpy(rpt->currNode->text, "Rain and snow");
		return;
	}

	/* A01 */
	if (strcmp(rpt->currNode->code, "AO1") == YES)
	{
		strcpy(rpt->currNode->text, "Automated weather station without precipitation sensor");
		return;
	}

	/* A02 */
	if (strcmp(rpt->currNode->code, "AO2") == YES)
	{
		strcpy(rpt->currNode->text, "Automated weather station with precipitation sensor");
		return;
	}

	strcpy(rpt->currNode->text, rpt->currNode->code);
}



