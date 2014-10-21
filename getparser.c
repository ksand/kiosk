/* getparser.c */

#include "kiosk.h"
#include <regex.h>
#include <stdlib.h>

void *getparser(WEATHER_REPORT *rpt)
{
	char *s;
	regex_t compiled;

	s = rpt->currNode->code;

	/* TAF */
	if (strcmp(s, "TAF") == YES)
		return NULL;
	
	/* Weather Station */
	if (strcmp(s, rpt->station) == YES)
		return NULL;

	/* UTC Zulu time */
	if (regcomp(&compiled, "Z$", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseZulu;
		}
	
	/* Reported Time (date/time on the first line of a METAR or TAF file */
	if (regcomp(&compiled, "^[0-9][0-9][0-9][0-9][/][0-9][0-9][/][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			parseReportedTime(rpt);
			return NULL;
		}

	/* Reported Time (date/time on the first line of a METAR or TAF file */
	if (regcomp(&compiled, "^[0-9][0-9]:[0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseReportedTime;
		}

	/* Wind velocity */
	if (regcomp(&compiled, "^[0-9][0-9][0-9][0-9][0-9]KT", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseWind;
		}

	/* Wind velocity with gusts dddffGffKT */
	if (regcomp(&compiled, "^[0-9][0-9][0-9][0-9][0-9]G[0-9][0-9]KT", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseWind;
		}

	/* Variable wind direction VRBddKT */
	if (regcomp(&compiled, "^VRB[0-9][0-9]KT", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseWind;
		}
	
	/* Visibility in statute miles */
	if (regcomp(&compiled, "SM$", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseVisibility;
		}

	/* Temperature and dew point */
	if (regcomp(&compiled, "^[0-9][0-9]/[0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseTemp;
		}
	
	/* Subzero temperature and dew point */
	if (regcomp(&compiled, "^M[0-9][0-9]/[0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseTemp;
		}
	
	/* Temperature and subzero dew point */
	if (regcomp(&compiled, "^[0-9][0-9]/M[0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseTemp;
		}
	
	/* Subzero temperature and subzero dew point */
	if (regcomp(&compiled, "^M[0-9][0-9]/M[0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseTemp;
		}

	/* Temperature remark Taaaabbbb */
	if (regcomp(&compiled, "^T[0-1][0-9][0-9][0-9][0-1][0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseTemp;
		}
	
	/* RA (rain) */
	if (regcomp(&compiled, "RA$", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseRain;
		}
	
	/* RAE (rain ending) */
	if (regcomp(&compiled, "RAE$", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseRainEnding;
		}
	
	/* SN (snow) */
	if (regcomp(&compiled, "SN$", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseSnow;
		}
	
	/* Altimenter */
	if (regcomp(&compiled, "^A[0-9][0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return NULL;
		}
	
	/* Few clouds and elevation in feet */
	if (regcomp(&compiled, "^FEW[0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseClouds;
		}
	
	/* Broken clouds and elevation in feet */
	if (regcomp(&compiled, "^BKN[0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseClouds;
		}
	
	/* Overcast and elevation in feet */
	if (regcomp(&compiled, "^OVC[0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseClouds;
		}
	
	/* Scattered clouds and elevation in feet */
	if (regcomp(&compiled, "^SCT[0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseClouds;
		}
	
	/* SLP remark (barometric pressure at sea level) hPa is "hectopascal" which is equivalent to "millibar" */
	if (regcomp(&compiled, "^SLP[0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parsePressure;
		}
	
	/* TSB remark (thunderstorm) */
	if (regcomp(&compiled, "^TSB[0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseThunderstorm;
		}
	
	/* Precipitation in last hour in inches */
	if (regcomp(&compiled, "^P[0-9][0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parsePrecip;
		}
	
	
	/* From Record  FMddhhmm Indicates a rapid change in prevailing conditions */
	if (regcomp(&compiled, "^FM[0-9][0-9][0-9][0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseRapid;
		}

	/* Forecast validity period in DDHH format */
	if (regcomp(&compiled, "^[0-9][0-9][0-9][0-9]/[0-9][0-9][0-9][0-9]", REG_EXTENDED) == SUCCESS)
		if (regexec(&compiled, s, 0, NULL, 0) == SUCCESS)
		{
			regfree(&compiled);
			return parseValidity;
		}


	return parseActivity;
}
