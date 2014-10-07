/* kiosk.c (chart) */

#include <curses.h>

int main(int argc, char *argv[])
{
	char c;

	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	attrset(COLOR_PAIR(1));

	while (1)
	{
		addch(0x00bb);
		refresh();
		c = getchar();
		break;
	}

	endwin();
	return 0;
}
