/* windfrom.c */

#include <string.h>
#include <stdio.h>

char *windfrom(const char *degrees, char buf[])
{
	int d;
	
	d = atoi(degrees);

	if ((d >= 0 && d < 12) || (d > 348 && d <= 360))
		strcpy(buf, "NORTH");
	else if (d > 11 && d < 34)
		strcpy(buf, "N-NE");
	else if (d > 33 && d < 57)
		strcpy(buf, "NE");
	else if (d > 56 && d < 79)
		strcpy(buf, "E-NE");
	else if (d > 78 && d < 102)
		strcpy(buf, "EAST");
	else if (d > 101 && d < 124)
		strcpy(buf, "E-SE");
	else if (d > 123 && d < 147)
		strcpy(buf, "SE");
	else if (d > 146 && d < 169)
		strcpy(buf, "S-SE");
	else if (d > 168 && d < 192)
		strcpy(buf, "SOUTH");
	else if (d > 191 && d < 214)
		strcpy(buf, "S-SW");
	else if (d > 213 && d < 237)
		strcpy(buf, "SW");
	else if (d > 236 && d < 259)
		strcpy(buf, "W-SW");
	else if (d > 258 && d < 282)
		strcpy(buf, "WEST");
	else if (d > 281 && d < 304)
		strcpy(buf, "W-NW");
	else if (d > 303 && d < 327)
		strcpy(buf, "NW");
	else if (d > 326 && d < 349)
		strcpy(buf, "N-NW");
	else
		strcpy(buf, "?");
	
	return buf;
}

