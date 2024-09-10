/*
 *	Warning list 를 화일로 부터 읽어들인다.
 */
int import_list(char *filename)
{
	FILE	*fp;
	char	*cp0, *cp1, *cp2, *cpp[3];
	int		i, n, sw_type;
	int		len1, len2;
	int		nQuotes, nItems;

	/*	Build filter configuration strings		*/
	nItems = 0;
	while (warn_fmts[nItems].sw_type < 0)
	{
		nItems++;
		for (i = 0; i < 3; i++)
		{
	    	warn_fmts[nItems].sw_len[i] = strlen(warn_fmts[nItems].sw_str[i]);
		}
	}

	if (nVerbose > 1)
	{
		fprintf(OUTPUT_FILE, "Data File  = %s\n", filename);
		fprintf(OUTPUT_FILE, "nSupItems1 = %d\n", nItems);
	}

	if ( (fp = fopen(filename, "r")) != NULL)
	{
		(void) fgets(warn_buf, 512, fp);

		while (!feof(fp))
		{
			nQuotes = 0;
			sw_type = 1;
			n = sscanf(warn_buf, "%d", &sw_type);

			if (n == 1)
			{
				cp0 = strchr(warn_buf, '"');
			}
			else
			{
				sw_type = 0;
				cp0     = &warn_buf[0];
				while (isspace(*cp0))
				{
					cp0++;
				}
			}

			if ((cp0 != NULL) && (*cp0 == '"'))
			{
				cpp[0] = cpp[1] = cpp[2] = (char *)"";

				for (nQuotes = 0; nQuotes < 3; nQuotes++)
				{
					cp1 = (cp0 ? strchr(cp0  , '"') : NULL);
					if (cp1 == NULL) break;
					cp2 = (cp1 ? strchr(cp1+1, '"') : NULL);
					if (cp2 == NULL) break;

					cpp[nQuotes] = cp1+1;
					*cp2 = '\0';
					cp0 = cp2 + 1;
				}

				if ( (cp2 != NULL) && (nQuotes >= 2) )
				{
					if (nVerbose > 1)
					{
						fprintf(OUTPUT_FILE, "%d:[%s][%s][%s]\n", sw_type, cpp[0], cpp[1], cpp[2]);
					}

		        	warn_fmts[nItems].sw_type = sw_type;
					for (i = 0; i < 3; i++)
					{
		        		snprintf(warn_fmts[nItems].sw_str[i], 40, "%s", cpp[i]);
	    				warn_fmts[nItems].sw_len[i] = strlen(warn_fmts[nItems].sw_str[i]);
					}
					nItems++;
				}
			}

			(void) fgets(warn_buf, 512, fp);
		}

		fclose(fp);
	}

	if (nVerbose > 1)
	{
		fprintf(OUTPUT_FILE, "nSupItems2 = %d\n", nItems);
	}

	return(nItems);
}