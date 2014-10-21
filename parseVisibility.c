/* parseVisibility.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseVisibility(WEATHER_REPORT *rpt)
{
	size_t i, length, start;
	int index, miles;
	char buf[16];

	length = strlen(rpt->currNode->code);
	index = 0;
	start = rpt->currNode->code[0] == 'P' ? 1 : 0;

	for (i = start; i < length; i++)
	{
		if (rpt->currNode->code[i] == 'S')
			break;

		buf[index] = rpt->currNode->code[i];
		index++;
	}
	
	buf[index] = 0x00;
	miles = atoi(buf);

	if (rpt->currNode->code[0] == 'P')
		if (miles == 1)
			sprintf(rpt->currNode->text, "Visibility more than %d mile", miles);
		else
			sprintf(rpt->currNode->text, "Visibility more than %d miles", miles);
	else
		if (miles == 1)
			sprintf(rpt->currNode->text, "Visibility %d mile", miles);
		else
			sprintf(rpt->currNode->text, "Visibility %d miles", miles);
}

