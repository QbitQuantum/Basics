static void
	plan_b (char const *filename)
{
	register FILE *ifp;
	register int c;
	register size_t len;
	register size_t maxlen;
	register bool found_revision;
	register size_t i;
	register char const *rev;
	register size_t revlen;
	register LINENUM line = 1;
	int exclusive;

	if (instat.st_size == 0)
		filename = NULL_DEVICE;
	if (! (ifp = fopen (filename, binary_transput ? "rb" : "rt")))
		pfatal ("Can't open file %s", quotearg (filename));
	exclusive = TMPINNAME_needs_removal ? 0 : O_EXCL;
	TMPINNAME_needs_removal = 1;
	tifd = create_file (TMPINNAME, O_RDWR | O_BINARY | exclusive, (mode_t) 0);
	i = 0;
	len = 0;
	maxlen = 1;
	rev = revision;
	found_revision = !rev;
	revlen = rev ? strlen (rev) : 0;

	while ((c = getc (ifp)) != EOF)
	{
		len++;

		if (c == '\n')
		{
			if (++line < 0)
				too_many_lines (filename);
			if (maxlen < len)
				maxlen = len;
			len = 0;
		}

		if (!found_revision)
		{
			if (i == revlen)
			{
				found_revision = ISSPACE ((unsigned char) c);
				i = (size_t) -1;
			}
			else if (i != (size_t) -1)
				i = rev[i]==c ? i + 1 : (size_t) -1;

			if (i == (size_t) -1  &&  ISSPACE ((unsigned char) c))
				i = 0;
		}
	}

	if (revision)
		report_revision (found_revision);
	Fseek (ifp, (off_t) 0, SEEK_SET);		/* rewind file */
	for (tibufsize = TIBUFSIZE_MINIMUM;  tibufsize < maxlen;  tibufsize <<= 1)
		continue;
	lines_per_buf = tibufsize / maxlen;
	tireclen = maxlen;
	tibuf[0] = (char *)malloc (2 * tibufsize);
	tibuf[1] = tibuf[0] + tibufsize;

	for (line = 1; ; line++)
	{
		char *p = tibuf[0] + maxlen * (line % lines_per_buf);
		char const *p0 = p;
		if (! (line % lines_per_buf))	/* new block */
			if (write (tifd, tibuf[0], tibufsize) != tibufsize)
				write_fatal ();
		if ((c = getc (ifp)) == EOF)
			break;

		for (;;)
		{
			*p++ = c;
			if (c == '\n')
			{
				last_line_size = p - p0;
				break;
			}

			if ((c = getc (ifp)) == EOF)
			{
				last_line_size = p - p0;
				line++;
				goto EOF_reached;
			}
		}
	}
EOF_reached:
	if (ferror (ifp)  ||  fclose (ifp) != 0)
		read_fatal ();

	if (line % lines_per_buf  !=  0)
		if (write (tifd, tibuf[0], tibufsize) != tibufsize)
			write_fatal ();
	input_lines = line - 1;
}