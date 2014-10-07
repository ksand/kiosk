/* routines.c */

#include <curses.h>
#include "kiosk.h"

#define DIVISOR 10000000
#define TRYLIMIT 10000

void initColorPairs()
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	return;
}

/*
 * genRand()
 *
 * Generates the dimensions and position of a window.
 * */

void genRand(struct windims *wd)
{
	int num, min, max, counter;

	/* Generate random height. It has to be at least 3 rows high
	 * and has to fit within the border and leave a row at the
	 * bottom to print a status line.
	 * */
	min = 3;
	max = wd->maxrow - 3;
	counter = 0;
	while (1)
	{
		counter++;
		num = rand();
		num /= DIVISOR;

		if (num >= min && num <= max)
		{
			wd->height = num;
			break;
		}

		if (counter > TRYLIMIT)
		{
			wd->height = max;
			break;
		}
	}

	/* Generate random row. The row must allow the window to
	 * fit on the screen, leaving a row at the bottom
	 * to print a status line.
	 * */
	min = 2;
	max = wd->maxrow - wd->height - 3;
	counter = 0;
	while (1)
	{
		counter++;
		num = rand();
		num /= DIVISOR;

		if (num >= min && num <= max)
		{
			wd->row = num;
			break;
		}

		if (counter > TRYLIMIT)
		{
			wd->row = min;
			break;
		}
	}

	/* Generate random width. It has to be at least 3 columns wide
	 * and has to fit within the border
	 * */
	min = 3;
	max = wd->maxcol - 2;
	counter = 0;
	while (1)
	{
		counter++;
		num = rand();
		num /= DIVISOR;

		if (num >= min && num <= max)
		{
			wd->width = num;
			break;
		}

		if (counter > TRYLIMIT)
		{
			wd->width = max;
			break;
		}
	}
	
	/* Generate random column. The column must allow the window to
	 * fit on between the borders.
	 * */
	min = 1;
	max = wd->maxcol - wd->width - 2;
	counter = 0;
	while (1)
	{
		counter++;
		num = rand();
		num /= DIVISOR;

		if (num >= min && num <= max)
		{
			wd->col = num;
			break;
		}

		if (counter > TRYLIMIT)
		{
			wd->col = min;
			break;
		}
	}
}
