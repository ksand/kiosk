/* parseTemp.c */

#include <string.h>
#include <stdio.h>
#include "kiosk.h"

void parseTemp(WEATHER_REPORT *rpt)
{
	float tf, tc, df, dc;
	int temp_centigrade, dewpoint_centigrade, temp_fahrenheit, dewpoint_fahrenheit;
	int index;
	char buf[8];

	/* Temperature Remark Tnnnnnnnn */

	if (rpt->currNode->code[0] == 'T')
	{
		if (rpt->currNode->code[1] == '1')
		{
			buf[0] = '-';
			buf[1] = rpt->currNode->code[2];
			buf[2] = rpt->currNode->code[3];
			buf[3] = '.';
			buf[4] = rpt->currNode->code[4];
			buf[5] = 0x00;
			tc = atof(buf);
			tf = (tc * 9)/5 + 32;
		}
		else
		{
			buf[0] = rpt->currNode->code[2];
			buf[1] = rpt->currNode->code[3];
			buf[2] = '.';
			buf[3] = rpt->currNode->code[4];
			buf[4] = 0x00;
			tc = atof(buf);
			tf = (tc * 9)/5 + 32;
		}

		/* Dew Point */
		if (rpt->currNode->code[5] == '1')
		{
			buf[0] = '-';
			buf[1] = rpt->currNode->code[6];
			buf[2] = rpt->currNode->code[7];
			buf[3] = '.';
			buf[4] = rpt->currNode->code[8];
			buf[5] = 0x00;
			dc = atof(buf);
			df = (dc * 9)/5 + 32;
		}
		else
		{
			buf[0] = rpt->currNode->code[6];
			buf[1] = rpt->currNode->code[7];
			buf[2] = '.';
			buf[3] = rpt->currNode->code[8];
			buf[4] = 0x00;
			dc = atof(buf);
			df = (dc * 9)/5 + 32;
		}
		sprintf(rpt->currNode->text, "Temperature %3.1f°F (%3.1f°C), Dew Point %3.1f°F (%3.1f°C)", tf, tc, df, dc);
		return;
	}

	/* Temperature in format nn/nn, Mnn/nn, nn/Mnn, Mnn/Mnn */

	if (rpt->currNode->code[0] == 'M')
	{
		buf[0] = '-';
		buf[1] = rpt->currNode->code[1];
		buf[2] = rpt->currNode->code[2];
		buf[3] = 0x00;
		index = 4;
	}
	else
	{
		buf[0] = rpt->currNode->code[0];
		buf[1] = rpt->currNode->code[1];
		buf[2] = 0x00;
		index = 3;
	}
	
	temp_centigrade = atoi(buf);
	temp_fahrenheit = (temp_centigrade * 9)/5 + 32;

	if (rpt->currNode->code[index] == 'M')
	{
		buf[0] = '-';
		buf[1] = rpt->currNode->code[index + 1];
		buf[2] = rpt->currNode->code[index + 2];
		buf[3] = 0x00;
	}
	else
	{
		buf[0] = rpt->currNode->code[index];
		buf[1] = rpt->currNode->code[index + 1];
		buf[2] = 0x00;
	}
	
	dewpoint_centigrade = atoi(buf);
	dewpoint_fahrenheit = (dewpoint_centigrade * 9)/5 + 32;
	sprintf(rpt->currNode->text, "Temperature %d°F (%d°C), Dew Point %d°F (%d°C)", temp_fahrenheit, temp_centigrade, dewpoint_fahrenheit, dewpoint_centigrade);
}
	
