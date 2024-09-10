void Add ( void )
{
	char tag[MaxLine]= "<!--BOOK=";
	char stout[255] = "";
	BOOL Updates = FALSE;

	/* Set the book header */
	for (; (strlen(BookName)>0) && (BookName[strlen(BookName)-1]!='.');
		 BookName[strlen(BookName)-1]=0);
	BookName[strlen(BookName)-1]=0;

	/* Get the tag name */
	strcat (tag,BookName);
	strcat (tag,"-->");
	strupr (tag);

	/* Pass all earlier */
	while (TRUE) {
		fgets  (line, MaxLine, fin);

		if (feof(fin)) CriticalError (SC_BooksCorrupted, "");
		strcpy (stout, line);
		NoSpaces();

		if (!strcmp(line,"<!--/BOOKSHELF-->")) break;
		if (strcmp(line,tag)>=0) break;

		strcat (line,"\n");
		fputs (line, fout);
		do {
			fgets (line, MaxLine,fin);
			fputs (line, fout);
			NoSpaces();
		} while (strcmp(line,"<!--/BOOK-->"));

	}
	   /* In all exits of this loop through here, stout is pending to be put */

	/* if present, update, that is, ignore previous book */
	if (!strcmp(line,tag))  {
		Updates = TRUE;		/* flag to say that we don't have to */
						/* append the saved line */
		do {
			fgets (line, MaxLine,fin);
			NoSpaces();
		} while (strcmp(line,"<!--/BOOK-->"));
	}

	/* Insert the book */
	fprintf (fout, "%s\n", tag);

	/* Transfer contents */
	while (TRUE) {
		fgets (line, MaxLine, fbook);
		if feof(fbook) break;
		fputs (line, fout);
	}

	/* Set the book end */
	fputs ("<!--/BOOK-->\n", fout);

	if (!Updates) fputs (stout, fout);
}