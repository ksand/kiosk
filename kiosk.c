/* kiosk.c */

#include <curses.h>
#include <stdlib.h>

void routines();

int main(int argc, char *argv[])
{
	initscr();

	while (1)
	{
		box(stdscr, ACS_VLINE, ACS_HLINE);
		refresh();
		sleep(5);
	
		/* border(0x00ba,0x00ba,0x00cd,0x00cd,0x00c9,0x00bb,0x00c8,0x00bc); */
		border(ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
		refresh();
		sleep(5);
	
	}

	endwin();
	return 0;
}
