/* kiosk.c (chart) */

#include <curses.h>

int main(int argc, char *argv[])
{
	char c, buf[16];
	int i, code;

	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	attrset(COLOR_PAIR(1));
	code = 32;

	while (1)
	{
		while (1)
		{
			sprintf(buf, "%4d ", code);
			addstr(buf);
			sprintf(buf, "0x%04x ", code);
			addstr(buf);
			attron(A_BOLD);
			addch(code);
			attroff(A_BOLD);
			addstr("\n");
			code ++;

			if (code % 25 == 0)
				break;
		}
		addch(0x00bb);
		addstr("\n");
		attrset(COLOR_PAIR(2));
		addstr("Press q to quit\n");
		attrset(COLOR_PAIR(1));
		refresh();
		c = getchar();
		
		if (c == 'q' || c == 'Q')
			break;

		clear();
	}

	endwin();
	return 0;
}
