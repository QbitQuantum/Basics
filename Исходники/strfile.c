/*
 * main:
 *	Drive the sucker.  There are two main modes -- either we store
 *	the seek pointers, if the table is to be sorted or randomized,
 *	or we write the pointer directly to the file, if we are to stay
 *	in file order.  If the former, we allocate and re-allocate in
 *	CHUNKSIZE blocks; if the latter, we just write each pointer,
 *	and then seek back to the beginning to write in the table.
 */
int
main(int ac, char *av[])
{
	bool		first;
	char		*sp, dc;
	FILE		*inf, *outf;
	int32_t		last_off, length, pos;
	int32_t		*p;
	int		cnt;
	char		*nsp;
	STR		*fp;
	static char	string[257];

	if (pledge("stdio rpath wpath cpath", NULL) == -1)
		err(1, "pledge");

	getargs(ac, av);		/* evalute arguments */
	dc = Delimch;
	if ((inf = fopen(Infile, "r")) == NULL)
		err(1, "%s", Infile);

	if ((outf = fopen(Outfile, "w")) == NULL)
		err(1, "%s", Outfile);

	if (pledge("stdio", NULL) == -1)
		err(1, "pledge");

	if (!STORING_PTRS)
		(void) fseek(outf, sizeof Tbl, SEEK_SET);

	/*
	 * Write the strings onto the file
	 */

	Tbl.str_longlen = 0;
	Tbl.str_shortlen = (unsigned int) 0xffffffff;
	Tbl.str_delim = dc;
	Tbl.str_version = VERSION;
	first = Oflag;
	add_offset(outf, ftell(inf));
	last_off = 0;
	do {
		sp = fgets(string, sizeof(string), inf);
		if (sp == NULL || (sp[0] == dc && sp[1] == '\n')) {
			pos = ftell(inf);
			length = pos - last_off - (sp ? strlen(sp) : 0);
			last_off = pos;
			if (!length)
				continue;
			add_offset(outf, pos);
			if (Tbl.str_longlen < (u_int32_t)length)
				Tbl.str_longlen = length;
			if (Tbl.str_shortlen > (u_int32_t)length)
				Tbl.str_shortlen = length;
			first = Oflag;
		} else if (first) {
			for (nsp = sp; !isalnum((unsigned char)*nsp); nsp++)
				continue;
			ALLOC(Firstch, Num_pts);
			fp = &Firstch[Num_pts - 1];
			if (Iflag && isupper((unsigned char)*nsp))
				fp->first = tolower((unsigned char)*nsp);
			else
				fp->first = *nsp;
			fp->pos = Seekpts[Num_pts - 1];
			first = false;
		}
	} while (sp != NULL);

	/*
	 * write the tables in
	 */

	(void) fclose(inf);
	Tbl.str_numstr = Num_pts - 1;
	if (Tbl.str_numstr == 0)
		Tbl.str_shortlen = 0;

	if (Oflag)
		do_order();
	else if (Rflag)
		randomize();

	if (Xflag)
		Tbl.str_flags |= STR_ROTATED;

	if (!Sflag) {
		printf("\"%s\" created\n", Outfile);
		if (Tbl.str_numstr == 1)
			puts("There was 1 string");
		else
			printf("There were %u strings\n", Tbl.str_numstr);
		printf("Longest string: %lu byte%s\n",
			  (unsigned long) Tbl.str_longlen,
		       Tbl.str_longlen == 1 ? "" : "s");
		printf("Shortest string: %lu byte%s\n",
			  (unsigned long) Tbl.str_shortlen,
		       Tbl.str_shortlen == 1 ? "" : "s");
	}

	(void) fseek(outf, 0, SEEK_SET);
	Tbl.str_version = htonl(Tbl.str_version);
	Tbl.str_numstr = htonl(Tbl.str_numstr);
	Tbl.str_longlen = htonl(Tbl.str_longlen);
	Tbl.str_shortlen = htonl(Tbl.str_shortlen);
	Tbl.str_flags = htonl(Tbl.str_flags);
	(void) fwrite(&Tbl.str_version,  sizeof(Tbl.str_version),  1, outf);
	(void) fwrite(&Tbl.str_numstr,   sizeof(Tbl.str_numstr),   1, outf);
	(void) fwrite(&Tbl.str_longlen,  sizeof(Tbl.str_longlen),  1, outf);
	(void) fwrite(&Tbl.str_shortlen, sizeof(Tbl.str_shortlen), 1, outf);
	(void) fwrite(&Tbl.str_flags,    sizeof(Tbl.str_flags),    1, outf);
	(void) fwrite( Tbl.stuff,	 sizeof(Tbl.stuff),	   1, outf);
	if (STORING_PTRS) {
		for (p = Seekpts, cnt = Num_pts; cnt--; ++p) {
			*p = htonl(*p);
			(void) fwrite(p, sizeof(*p), 1, outf);
		}
	}
	if (fclose(outf))
		err(1, "fclose `%s'", Outfile);
	return 0;
}