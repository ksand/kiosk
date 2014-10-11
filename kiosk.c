/* kiosk.c */

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "kiosk.h"

#define NOAA_URL "http://weather.noaa.gov/pub/data/observations/metar/stations/"
#define ICAO_CODE "KPOU"
#define DELAY_SECONDS 600
#define BUFSIZE 1024
#define SUCCESS 0
#define LCOL 3

void klog(char *info);

int main(int argc, char *argv[])
{
	int row, col, counter;
	char scode[5];
	char buf[BUFSIZE];
	struct stat fs;
	struct windims wd;
	FILE *rpt;
	time_t t1, t2;

	/* ncurses */
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	
	/* Loop counter */
	counter = 1;

	while (1)
	{
		/* Get the screen dimensions */
		getmaxyx(stdscr, row, col);
		wd.maxrow = row;
		wd.maxcol = col;

		/* Set the display color */
		color_set(7, NULL);

		/* Set ICAO code for the weather station */
		strcpy(scode, ICAO_CODE);
		mvprintw(1, LCOL, "Station Code: %s", scode);
		
		/* Check if the local file exists */
		sprintf(buf, "%s.TXT", scode);
		if (stat(buf, &fs) == SUCCESS)
		{
			/* Local file exists. Get it's time stamp and log it */
			t1 = fs.st_mtime;
			sprintf(buf, "%s.TXT exists with timestamp %lu", scode, t1);
			mvprintw(2, LCOL, buf);
			klog(buf);
			sprintf(buf, "wget -N --dns-timeout=40 --quiet %s%s.TXT", NOAA_URL, scode);
		}
		else
		{
			/* Create new file */
			sprintf(buf,  "%s.TXT does not exist... creating new %s.TXT", scode, scode);
			mvprintw(2, LCOL, buf);
			klog(buf);
			sprintf(buf, "wget -S --dns-timeout=40 --quiet %s%s.TXT", NOAA_URL, scode);
		}

		/* Execute the wget command */

		if (system(buf) ==	SUCCESS)
		{
			mvprintw(3, LCOL, "wget succeeded %d", counter);
			counter++;
			sprintf(buf, "%s.TXT", scode);
			
			if (stat(buf, &fs) == SUCCESS)
			{
				t2 = fs.st_mtime;
				
				if (t1 != t2)
				{
					sprintf(buf, "%s.TXT exists with new timestamp %lu", scode, t2);
					klog(buf);
				}

				sprintf(buf, "%s.TXT", scode);
				rpt = fopen(buf, "r");

				if (rpt != NULL)
				{
					row = 4;
					color_set(2, NULL);
					while (fgets(buf, BUFSIZE, rpt) != NULL)
					{
						mvprintw(row, LCOL, buf);
						row++;
					}
					color_set(7, NULL);
					fclose(rpt);
				}
				else
				{
					mvprintw(4, LCOL, "Unable to open file");
				}
			}
			else
			{
				sprintf(buf, "%s.TXT does not exist", scode);
				klog(buf);
				mvprintw(4, LCOL, buf);
			}
		}
		else
		{
			sprintf(buf, "wget failed: %s", buf);
			mvprintw(3, LCOL, buf);
			klog(buf);
		}
		
		/* Draw a border */
		color_set(4, NULL);
		box(stdscr, ACS_VLINE, ACS_HLINE);
		refresh();
		sleep(DELAY_SECONDS);
	
		/* Clear the screen and wait */
		clear();
		refresh();
		sleep(30);
	}

	endwin();
	return 0;
}
