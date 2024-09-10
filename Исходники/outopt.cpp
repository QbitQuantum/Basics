static int nextspecs (char ***field)
{
    static char **fld = NULL;
    static FILE *fp = NULL;
    static int  eof = 0;
    static int  fld_size = 0;
    static int  line_number = 0;
    int nfield = 0;

/*	all done if end of file found on prior call	*/

    if (eof)
    {
        fclose (fp);
        free (fld);
        return (0);
    }

/*	initialize on the first call	*/

    if (fp == NULL)
    {
		fopen_s(&fp, "output.opt", "r"); 
        if (fp == NULL)
			error_stop ("cannot open file", "output.opt");
		fld_size = 100;
        fld = (char **) malloc ((unsigned) fld_size * sizeof (char *));
		if (fld == NULL)
			error_stop ("cannot allocate vector fld", "for output.opt specs");
    }

/*	get specs from the next non-blank line	*/

    while (1)
    {
        char buf[200];
	char cur_line[50];
	char *line;
	int cur_fld_len;
	int line_continued;
	int eol_found = 0;

    /*	    read the next line	*/

	line = fgets (buf, 200, fp);
	++line_number;
	sprintf_s (cur_line, sizeof(cur_line), "line %d of file output.opt", line_number);
	if (line == NULL)
	{
	    eof = 1;
	    break;
	}

    /*	    find the fields on the line     */
	
	cur_fld_len = 0;
	line_continued = 0;
	while (*line)
	{
	    if (*line == '"')
	    {
	        if (cur_fld_len > 0)
				error_stop ("embedded quote on", cur_line);
	        while (++line)
			{
				if (*line == '\0' || *line == '\n')
					error_stop ("missing quote on", cur_line);
				if (*line == '"')
				{
					*line = ' ';
					break;
				}
				++cur_fld_len;
			}
	    }

	    if ((*line == '/' && *(line + 1) == '/') || *line == '\n')
	        eol_found = 1;

	    if (*line == '+' && *(line + 1) == '+')
	    {
	        eol_found = 1;
			line_continued = 1;
		{
		    char *p = line + 2;
		    while (*p && *p != '\n')
		    {
				if (*p == '/' && *(p + 1) == '/') 
					break;
		        if (*p != ' ' && *p != '\t')
					error_stop ("characters after ++ on", cur_line);
		        ++p;
		    }
		}
	    }

	    if (*line == ' ' || *line == '\t' || eol_found)
	    {
	        if (cur_fld_len > 0)
			{
				if (nfield == fld_size)
				{
					fld_size += 100;
					fld = (char **) realloc (fld, (unsigned) fld_size *
			                                      sizeof (char *));
					if (fld == NULL)
						error_stop ("cannot reallocate vector fld on",
			                                             cur_line);
				}
				fld[nfield] = (char *) malloc ((unsigned) cur_fld_len + 1);
				if (fld[nfield] == NULL)
					error_stop ("cannot allocate space for option spec on",
			                                              cur_line);
				*line = '\0';
				strcpy_s(fld[nfield++], cur_fld_len + 1, line - cur_fld_len);
				cur_fld_len = 0;
			}
	    }
	    else
	        ++cur_fld_len;

  	    if (eol_found)
	        break;
	    ++line;
	}
	if (! eol_found)
	    error_stop ("line is too long -", cur_line);

    /*	    stop reading if field(s) found and line not continued	*/

	if (nfield > 0 && ! line_continued)
	    break;
    }

/*	set output arguments and return		*/

    *field = fld;
    return (nfield);
}