/* kiosk.c */

#include <curses.h>
#include <stdlib.h>

/* colors idefined in /usr/include/ncurses.h
#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7 */

void routines();

int main(int argc, char *argv[])
{
	initscr();
	start_color();

	while (1)
	{
		/* This is one way to draw a border */
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		color_set(1, NULL);
		box(stdscr, ACS_VLINE, ACS_HLINE);
		refresh();
		sleep(2);

		/* Clear the screen */
		clear();
		refresh();
		sleep(2);
	
		/* This is another way to draw a border */
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		color_set(2, NULL);
		border(ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
		refresh();
		sleep(2);
	
		/* Clear the screen */
		clear();
		refresh();
		sleep(2);
	}

	endwin();
	return 0;
}
