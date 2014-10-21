/* namegen.c */

#include <string.h>
#include <stdio.h>
#include <time.h>

char *namegen(char *base, char name[])
{
	time_t curtime;
	struct tm *loctime;

	/* Get the current time */
	curtime = time(NULL);

	/* Convert to tm structure */
	loctime = localtime(&curtime);

	sprintf(name, "%s.%d%02d%02d%02d%02d%02d.TXT", base, loctime->tm_year + 1900, loctime->tm_mon + 1, loctime->tm_mday, loctime->tm_hour, loctime->tm_min, loctime->tm_sec);
	return name;
}
