/* 
 * rtrim.c
 *
 * Trim leading whitespace */

#include <stdlib.h>

char *rtrim(const char *s, char buf[], size_t maxlen)
{
	size_t i, index;
	i = index = 0;

	while (s[i] != 0x00 && i < maxlen)
	{
		if (s[i] == 0x20 || s[i] == 0x09 || s[i] == 0x0a || s[i] == 0x0b || s[i] == 0x0c || s[i] == 0x0d)
			i++;
		else
		{
			buf[index] = s[i];
			index++;
			i++;
		}
	}
	buf[index] = 0x00;
	return buf;
}


