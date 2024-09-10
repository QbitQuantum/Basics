/*
 * Reads the lines from the fiven \"input\" file and creates the reads and prefixes
 * for the read filter.  The \"read_filter\" given is allocated.
 *
 * Returns 0 on success.  Errors cause the usage message and exit. 
 */
int read_filter_from_file(FILE *input, read_filter_t *read_filter)
{
    int   isNewline;              /* Boolean indicating we've read a CR or LF */
    long  lFileLen;               /* Length of file */
    long  lIndex;                 /* Index into cThisLine array */
    long  lLineCount;             /* Current line number */
    long  lLineLen;               /* Current line length */
    long  lStartPos;              /* Offset of start of current line */
    long  lTotalChars;            /* Total characters read */
    char  cThisLine[MAX_REC_LEN]; /* Contents of current line */
    char *cFile;                  /* Dynamically allocated buffer (entire file) */
    char *cThisPtr;               /* Pointer to current position in cFile */

    char *filter_type = NULL;
    char *prefix;
    char *read;

    fseek(input, 0L, SEEK_END);  /* Position to end of file */
    lFileLen = ftell(input);     /* Get file length */
    rewind(input);               /* Back to start of file */

    cFile = calloc(lFileLen + 1, sizeof(char));

    if(cFile == NULL )
	{
	    fprintf(stderr, "\nInsufficient memory to read file.\n");
	    return -1;
	}

    /* Read the entire file into cFile */
    if (1 != fread(cFile, lFileLen, 1, input))
	return -1;

    lLineCount  = 0L;
    lTotalChars = 0L;

    cThisPtr    = cFile;              /* Point to beginning of array */

    while (*cThisPtr)                 /* Read until reaching null char */
	{
	    lIndex    = 0L;                 /* Reset counters and flags */
	    isNewline = 0;
	    lStartPos = lTotalChars;

	    while (*cThisPtr)               /* Read until reaching null char */
		{
		    if (!isNewline)               /* Haven't read a CR or LF yet */
			{
			    if (*cThisPtr == CR || *cThisPtr == LF) /* This char IS a CR or LF */
				isNewline = 1;                        /* Set flag */
			}

		    else if (*cThisPtr != CR && *cThisPtr != LF) /* Already found CR or LF */
			break;                                     /* Done with line */

		    /* Don't copy LS or CR */
		    if (*cThisPtr != CR && *cThisPtr != LF) {
			cThisLine[lIndex++] = *cThisPtr++; /* Add char to output and increment */
			++lTotalChars;
		    } else {
			cThisPtr++;
		    }

		} /* end while (*cThisPtr) */

	    cThisLine[lIndex] = '\0';     /* Terminate the string */
	    ++lLineCount;                 /* Increment the line counter */
	    lLineLen = strlen(cThisLine); /* Get length of line */

	    /* Find the one and only = in the string. */
	    if(strchr(cThisLine,'=') != NULL && (strchr(cThisLine,'=') == strrchr(cThisLine,'='))) {
		filter_type = strtok (cThisLine, "=");
	    } else {
		fprintf(stderr, "Baddly formatted read filter \"%s\".  Expected an \"=\" character in middle of filter.\n", cThisLine);
		usage(1);
	    }

	    if (!strcmp(filter_type, "prefix")) {
		prefix = strtok (NULL, "=");
		if(prefix == NULL) {
		    fprintf(stderr, "Bad prefix \"%s\" in read filter \"%s\".\n", prefix, cThisLine);
		    usage(1);
		} else {
		    ++(read_filter->prefixes_size);
		    read_filter->prefixes = (char**) realloc (read_filter->prefixes, read_filter->prefixes_size * sizeof(char *));
		    read_filter->prefixes[read_filter->prefixes_size - 1] =  (char*) calloc (strlen(prefix) + 1,sizeof(char));
		    strcpy(read_filter->prefixes[read_filter->prefixes_size - 1], prefix);
		}
	    } else if (!strcmp(filter_type, "read")) {
		read = strtok (NULL, "=");
		if(read == NULL) {
		    fprintf(stderr, "Bad read \"%s\" in read filter \"%s\".\n", read, cThisLine);
		    usage(1);
		} else {
		    ++(read_filter->reads_size);
		    read_filter->reads = (char**) realloc (read_filter->reads, read_filter->reads_size * sizeof(char *));
		    read_filter->reads[read_filter->reads_size - 1] =  (char*) calloc (strlen(read) + 1,sizeof(char));
		    strcpy(read_filter->reads[read_filter->reads_size - 1], read);
		}
	    } else {
		fprintf(stderr, "Unrecognized filter type \"%s\" given as part of read filter \"%s\".  The valid filter types are \"%s\".\n", filter_type, cThisLine, "prefix or read");
		usage(1);
	    }

	}

    free(cFile);
    return 0;
}