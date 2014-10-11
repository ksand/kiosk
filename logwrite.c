/* logwrite.c */

#include <time.h>
#include <stdio.h>

void logwrite(char *filename, char *info)
{
	time_t t;
	struct tm tmlog, *p;
	FILE *fp;

	time(&t);
	p = localtime_r(&t, &tmlog);
	fp = fopen(filename, "a");
	fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", 1900 + p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, info);
	fclose(fp);
}

