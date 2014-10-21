/* getMetar.c */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "kiosk.h"

void getMetar(WEATHER_REPORT *rpt)
{
	size_t i, j, maxj, bytes;
	char c;
	struct stat fs;
	char filename[FILENAME_MAX], buf[2048], option[20], archive_filename[32];
	time_t t;
	struct tm *ft;
	FILE *fp;
	bool is_remark;
	WEATHER_CODE *wc, *node, *tmpnode;

	/* Build the wget command that will download the METAR file from the server.
	 * If the file does not exist on the local drive, use --server-response, 
	 * which gives the local file the same timestamp as the server file's.
	 *
	 * If the local file already exists, use --timestamping so the server 
	 * file is only downloaded if its timestamp is newer than that of the
	 * local file. */

	/* Report Title */
	sprintf(rpt->title, "%s OBSERVATIONS", ICAO_CODE);

	/* The local file is stored in a folder defined by METAR_PATH */
	sprintf(filename, "%s/%s.TXT", METAR_PATH, ICAO_CODE);

	if (stat(filename, &fs) == SUCCESS)
	{
		/* Local file exists */
		rpt->file_time = fs.st_mtime;
		t = rpt->file_time;
		ft = localtime(&t);
		sprintf(rpt->file_time_text, "%02d/%02d/%d %02d:%02d %s (UTC %ld)", ft->tm_mon + 1, ft->tm_mday, ft->tm_year + 1900, ft->tm_hour, ft->tm_min, ft->tm_zone, ft->tm_gmtoff/3600);
		strcpy(option, "--timestamping");
	}
	else
	{
		/* Local file does not exist */
		rpt->file_time = 0;
		strcpy(option, "--server-response");
	}

	/* The shell command used to download the file from the NOAA website */
	sprintf(buf, "wget %s --dns-timeout=40 --quiet %s%s.TXT", option, METAR_URL, rpt->station);
	
	if (system(buf) == SUCCESS)
	{
		sprintf(buf, "METAR download attempt");
		logwrite(LOGFILE_NAME, buf);
		rpt->download_time = time(&t);

		/* Make a copy of the METAR file so it does not get clobbered */
		sprintf(buf, "cp --preserve=all %s.TXT %s", rpt->station, filename);
		system(buf);
		sprintf(buf, "rm %s.TXT", rpt->station);
		system(buf);

		/* Get the time stamp of the METAR file */
		if (stat(filename, &fs) == SUCCESS)
		{
			if (fs.st_mtime != rpt->file_time)
			{
				/* Archive the METAR file */
				sprintf(buf, "cp --preserve=all %s %s/%s", filename, METAR_PATH, namegen(rpt->station, archive_filename));
				system(buf);
				
				/* Set the report-file time to the new time */
				t = fs.st_mtime;
				rpt->file_time = t;
				ft = localtime(&t);
				sprintf(rpt->file_time_text, "%02d/%02d/%d %02d:%02d %s (UTC %ld)", ft->tm_mon + 1, ft->tm_mday, ft->tm_year + 1900, ft->tm_hour, ft->tm_min, ft->tm_zone, ft->tm_gmtoff/3600);
				logwrite(LOGFILE_NAME, "METAR new file");
			}
			
			/* Read the entire file into a buffer */
			bytes = (size_t)fs.st_size;
			rpt->datasize = bytes + 1;
			rpt->data = (char *)realloc(rpt->data, rpt->datasize);

			if (rpt->data == 0)
			{
				logwrite(LOGFILE_NAME, "METAR realloc fail");
				return;
			}

			/* Open the file for reading */
			fp = fopen(filename, "r");
			fread_unlocked(rpt->data, bytes, 1, fp);
			fclose(fp);

			/* If the linked list already exists, free its memory and reset the root pointer */
			if (rpt->rootNode != NULL)
			{
				node = rpt->rootNode;
				while (node->next != 0)
				{
					tmpnode = node;
					node = node->next;
					free(tmpnode);
				}
				free(node);
			}

			/* Break up the report into individual components and store them in a linked list */
			rpt->rootNode = (WEATHER_CODE *)malloc(sizeof(WEATHER_CODE));
			rpt->rootNode->next = 0;
			maxj = sizeof(buf);
			j = 0;
			
			for (i = 0; i < rpt->datasize; i++)
			{
				c = rpt->data[i];
				if (c == ' ' || c == '\n' || i == bytes)
				{
					if (j > 0)
					{
						buf[j] = 0x00;

						if (rpt->rootNode->next == 0)
							wc = rpt->rootNode;
						else
							wc = wc->next;

						wc->next = (WEATHER_CODE *)malloc(sizeof(WEATHER_CODE));
						strcpy(wc->code, buf);
						wc->remark = false;
						wc->show = true;
						j = 0;
					}
				}
				else
				{
					if (j < maxj)
					{
						buf[j] = c;
						j++;
					}
				}
			}
			wc->next = 0;
		}

		/* Run through the linked list and translate the codes */
		rpt->currNode = rpt->rootNode;
		is_remark = false;

		do {
			parser = getparser(rpt);
			if (parser != NULL)
			{
				strcpy(rpt->currNode->caption, rpt->currNode->code);
				parser(rpt);
			}
			else
				rpt->currNode->show = false;
			rpt->currNode = rpt->currNode->next;
		} while (rpt->currNode != NULL);
	}
	else
	{
		sprintf(buf, "METAR wget fail");
		logwrite(LOGFILE_NAME, buf);
	}
}
