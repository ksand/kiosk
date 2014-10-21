/* kiosk.c */

#include <curses.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <signal.h>
#include "kiosk.h"

#define LOG_FILENAME "weather.log"
#define VIEW_SECONDS  60
#define CLEAR_SECONDS 10
#define WAIT_SECONDS  3600.000000d
#define BUFSIZE 1024
#define BLACK   0
#define RED     1
#define GREEN   2
#define YELLOW  3
#define BLUE    4
#define MAGENTA 5
#define CYAN    6
#define WHITE   7

WEATHER_REPORT metar, taf;

/* Signal Handler */
void handler(int signum)
{
	WEATHER_CODE *node, *temp;
	
	free(metar.data);
	node = metar.rootNode;
	while (node->next != 0)
	{
		temp = node;
		node = node->next;
		free(temp);
	}
	free(node);
	free(taf.data);
	if (taf.rootNode != NULL)
	{
		node = taf.rootNode;
		while (node->next != 0)
		{
			temp = node;
			node = node->next;
			free(temp);
		}
		free(node);
	}
	curs_set(1);
	endwin();
	exit(0);
}

int main(int argc, char *argv[])
{
	int row, col;
	time_t start, now;
	double elapsed;
	SCREEN screen;

	/* Signal Handler */
	signal(SIGINT, handler);

	/* NOAA Reports */
	metar.type = METAR;
	strcpy(metar.station, ICAO_CODE);
	taf.type = TAF;
	strcpy(taf.station, ICAO_CODE);

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
	curs_set(0);

	/* Start Time */
	start = time(&start);
	elapsed = 0.000000d;

	while (1)
	{
		/* Get the screen dimensions */
		getmaxyx(stdscr, row, col);
		screen.maxrow = row;
		screen.maxcol = col;

		/* METAR */

		if (elapsed == 0.000000d)
			getMetar(&metar);
			
		row = 1;
		col = 2;
		color_set(YELLOW, NULL);
		mvprintw(row, col, metar.title);
		color_set(WHITE, NULL);
		row++;

		if (metar.file_time != 0)
		{
			color_set(GREEN, NULL);
			mvprintw(row, col, "FILE TIME");
			color_set(WHITE, NULL);
			mvprintw(row, MAX_CODE_LENGTH, metar.file_time_text);
			row++;

			/* Run through the linked list and display the contents */
			metar.currNode = metar.rootNode;

			do {
				if (metar.currNode->show)
				{
					color_set(GREEN, NULL);
					mvprintw(row, col, metar.currNode->caption);
					color_set(WHITE, NULL);
					mvprintw(row, MAX_CODE_LENGTH, metar.currNode->text);
					row++;
				}
				metar.currNode = metar.currNode->next;
			} while (metar.currNode != NULL);

			/* Draw a border and show the screen */
			color_set(GREEN, NULL);
			box(stdscr, ACS_VLINE, ACS_HLINE);
			refresh();
			sleep(VIEW_SECONDS);

			/* Clear the screen */
			clear();
			refresh();
			sleep(CLEAR_SECONDS);
		}
		
		/* TAF */

		if (elapsed == 0.000000d)
			getTaf(&taf);

		row = 1;
		col = 2;
		color_set(YELLOW, NULL);
		mvprintw(row, col, taf.title);
		color_set(WHITE, NULL);
		row++;
		
		if (taf.file_time != 0)
		{
			color_set(GREEN, NULL);
			mvprintw(row, col, "FILE TIME");
			color_set(WHITE, NULL);
			mvprintw(row, MAX_CODE_LENGTH, taf.file_time_text);
			row++;

			/* Run through the linked list and display the contents */
			taf.currNode = taf.rootNode;

			do {
				if (taf.currNode->show)
				{
					color_set(GREEN, NULL);
					mvprintw(row, col, taf.currNode->caption);
					color_set(WHITE, NULL);
					mvprintw(row, MAX_CODE_LENGTH, taf.currNode->text);
					row++;
				}
				taf.currNode = taf.currNode->next;
			} while (taf.currNode != NULL);

			/* Draw a border and show the screen */
			color_set(GREEN, NULL);
			box(stdscr, ACS_VLINE, ACS_HLINE);
			refresh();
			sleep(VIEW_SECONDS);

			/* Clear the screen */
			clear();
			refresh();
			sleep(CLEAR_SECONDS);
		}
		now = time(&now);
		elapsed = difftime(now, start);
		if (elapsed > WAIT_SECONDS)
		{
			start = time(&start);
			elapsed = 0.000000d;
		}
	}
	return 0;
}
