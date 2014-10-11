/* routines.c */

#include <time.h>
#include <stdio.h>

void klog(char *info)
{
	time_t tlog;
	struct tm t, *logtime;
	FILE *log;

	time(&tlog);
	logtime = localtime_r(&tlog, &t);
	log = fopen("logfile", "a");
	fprintf(log, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", 1900 + logtime->tm_year, logtime->tm_mon, logtime->tm_mday, logtime->tm_hour, logtime->tm_min, logtime->tm_sec, info);
	fclose(log);
}

