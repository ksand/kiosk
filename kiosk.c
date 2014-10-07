/* kiosk.c */

#include <curses.h>
#include <stdlib.h>
#include "kiosk.h"

#define DELAY_SECONDS 2

void genRand(struct windims *wd);
void initColorPairs();

int main(int argc, char *argv[])
{
	int colorpair, row, col;
	struct windims wd;
	WINDOW *win;
	
	initscr();
	start_color();
	initColorPairs();

	colorpair = 1;

	while (1)
	{
		/* Draw a border */
		color_set(colorpair, NULL);
		box(stdscr, ACS_VLINE, ACS_HLINE);
		getmaxyx(stdscr, row, col);
		wd.maxrow = row;
		wd.maxcol = col;
		color_set(7, NULL);
		mvprintw(row - 2, 2, "%d rows %d cols", row, col);
		refresh();
		sleep(DELAY_SECONDS);
		
		/* Cycle through the colors 1-7 */
		colorpair++;
		
		if (colorpair > 7)
			colorpair = 1;
		
		/* Generate random window specs */
		genRand(&wd);

		/* Display the window dimensions on the bottom row */
		color_set(7, NULL);
		mvprintw(row - 2, 2, "row=%d col=%d height=%d width=%d", wd.row, wd.col, wd.height, wd.width);

		/* Create a new window */
		win = newwin(wd.height, wd.width, wd.row, wd.col);
		wbkgdset(win, COLOR_PAIR(colorpair));
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		sleep(DELAY_SECONDS);

		/* Destroy the window */
		wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
		wrefresh(win);
		delwin(win);
		clear();
		refresh();
		sleep(DELAY_SECONDS);
	}

	endwin();
	return 0;
}
