/* kiosk.h */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef KIOSK_H
#define KIOSK_H

#define ICAO_CODE  "KPOU"
#define METAR_URL  "http://weather.noaa.gov/pub/data/observations/metar/stations/"
#define TAF_URL    "http://weather.noaa.gov/pub/data/forecasts/taf/stations/"
#define METAR_PATH "./metar"
#define TAF_PATH   "./taf"
#define LOGFILE_NAME "weather.log"
#define MAX_CODE_LENGTH 16
#define MAX_TEXT_LENGTH 64
#define YES 0
#define NO  1
#define SUCCESS 0
#define FAIL    1

/* Structure to hold "ncurses" info */
typedef struct screen {
	int maxrow;
	int maxcol;
} SCREEN;

/* METAR Meteorological Aerodrome Report
 * TAF Terminal Aerodrome Forecast */
enum rectype {METAR, TAF};

/* Weather Code. Weather reports contain a linked list of weather codes. */
typedef struct weatherCode
{
	char code[MAX_CODE_LENGTH];
	char caption[MAX_CODE_LENGTH];
	char text[MAX_TEXT_LENGTH];
	char text_continued[MAX_TEXT_LENGTH];
	bool remark;
	bool show;

	/* Pointer to the next WEATHER_CODE in the linked list */
	struct weatherCode *next;
} WEATHER_CODE;

/* Weather Report */
typedef struct weatherReport
{
	enum rectype type;
	char station[5];
	char title[MAX_TEXT_LENGTH];
	char file_time_text[MAX_TEXT_LENGTH];
	time_t file_time;
	struct tm reported_time;
	time_t download_time;
	char *data;
	size_t datasize;
	WEATHER_CODE *rootNode;
	WEATHER_CODE *currNode;
} WEATHER_REPORT;

/* NOAA Reports */
void getMetar(WEATHER_REPORT*);
void getTaf(WEATHER_REPORT*);

/* Utility functions */
void logwrite(char *filename, char *info);
char *rtrim(const char *s, char buf[], size_t maxlen);
char *windfrom(const char *degrees, char buf[]);
char *namegen(char *base, char outbuf[]);

/* Function-pointer functions for parsers */
void *getparser(WEATHER_REPORT *report);
void (*parser)(WEATHER_REPORT *report);

/* Parsers */
void parseZulu(WEATHER_REPORT *report);
void parseReportedTime(WEATHER_REPORT *report);
void parseWind(WEATHER_REPORT *report);
void parseVisibility(WEATHER_REPORT *report);
void parseActivity(WEATHER_REPORT *report);
void parseTemp(WEATHER_REPORT *report);
void parseRain(WEATHER_REPORT *report);
void parseRainEnding(WEATHER_REPORT *report);
void parseSnow(WEATHER_REPORT *report);
void parseClouds(WEATHER_REPORT *report);
void parsePressure(WEATHER_REPORT *report);
void parseThunderstorm(WEATHER_REPORT *report);
void parsePrecip(WEATHER_REPORT *report);
void parseRapid(WEATHER_REPORT *report);
void parseValidity(WEATHER_REPORT *report);
void parseAltitude(WEATHER_REPORT *report);

#endif
