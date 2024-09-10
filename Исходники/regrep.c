static int read_summary_log(const char *filename, int index)
{
    summary_file *curfile = NULL;
    char linebuffer[1024];
    char *linestart;
    int drivers = 0;
    FILE *file;

    /* open the logfile */
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: file '%s' not found\n", filename);
        return 1;
    }

    /* parse it */
    while (fgets(linebuffer, sizeof(linebuffer), file) != NULL)
    {
    	/* trim the leading/trailing spaces */
    	linestart = trim_string(linebuffer);

        /* is this one of our specials? */
        if (strncmp(linestart, "@@@@@", 5) == 0)
        {
        	/* advance past the signature */
        	linestart += 5;

			/* look for the driver= tag */
			if (strncmp(linestart, "driver=", 7) == 0)
			{
				curfile = parse_driver_tag(linestart + 7, index);
				if (curfile == NULL)
					goto error;
				drivers++;
			}

			/* look for the source= tag */
			else if (strncmp(linestart, "source=", 7) == 0)
			{
				/* error if no driver yet */
				if (curfile == NULL)
				{
					fprintf(stderr, "Unexpected @@@@@source= tag\n");
					goto error;
				}

				/* copy the string */
				strcpy(curfile->source, trim_string(linestart + 7));
			}

			/* look for the dir= tag */
			else if (strncmp(linestart, "dir=", 4) == 0)
			{
				char *dirname = trim_string(linestart + 4);

				/* allocate a copy of the string */
				lists[index].dir = (char *)malloc(strlen(dirname) + 1);
				if (lists[index].dir == NULL)
					goto error;
				strcpy(lists[index].dir, dirname);
				fprintf(stderr, "Directory %s\n", lists[index].dir);
			}
		}

        /* if not, consider other options */
        else if (curfile != NULL)
        {
            int foundchars = 0;
            char *curptr;

            /* look for the pngcrc= tag */
			if (strncmp(linestart, "pngcrc: ", 7) == 0)
            {
            }

			/* otherwise, accumulate the text */
			else
			{
				/* find the end of the line and normalize it with a CR */
				for (curptr = linestart; *curptr != 0 && *curptr != '\n' && *curptr != '\r'; curptr++)
					if (!isspace((UINT8)*curptr))
						foundchars = 1;
				*curptr++ = '\n';
				*curptr = 0;

				/* ignore blank lines */
				if (!foundchars)
					continue;

				/* see if we have enough room */
				if (curfile->textsize[index] + (curptr - linestart) + 1 >= curfile->textalloc[index])
				{
					curfile->textalloc[index] = curfile->textsize[index] + (curptr - linestart) + 256;
					curfile->text[index] = (char *)realloc(curfile->text[index], curfile->textalloc[index]);
					if (curfile->text[index] == NULL)
					{
						fprintf(stderr, "Unable to allocate memory for text\n");
						goto error;
					}
				}

				/* append our text */
				strcpy(curfile->text[index] + curfile->textsize[index], linestart);
				curfile->textsize[index] += curptr - linestart;
			}
		}

		/* look for the M.A.M.E. header */
		else if (strncmp(linestart, "M.A.M.E. v", 10) == 0)
		{
			char *start = linestart + 10;
			char *end;

			/* find the end */
			for (end = start; !isspace((UINT8)*end); end++) ;
			*end = 0;
			strcpy(lists[index].version, start);
			fprintf(stderr, "Parsing results from version %s\n", lists[index].version);
		}
    }

    fclose(file);
    fprintf(stderr, "Parsed %d drivers\n", drivers);
    return 0;

error:
    fclose(file);
    return 1;
}