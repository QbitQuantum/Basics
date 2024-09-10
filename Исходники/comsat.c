void
jkfprintf(FILE *tp, char name[], off_t offset)
{
	char *cp, ch;
	char visout[5], *s2;
	FILE *fi;
	int linecnt, charcnt, inheader;
	char line[BUFSIZ];

	if ((fi = fopen(name, "r")) == NULL)
		return;

	(void)fseeko(fi, offset, SEEK_SET);
	/*
	 * Print the first 7 lines or 560 characters of the new mail
	 * (whichever comes first).  Skip header crap other than
	 * From, Subject, To, and Date.
	 */
	linecnt = 7;
	charcnt = 560;
	inheader = 1;
	while (fgets(line, sizeof(line), fi) != NULL) {
		if (inheader) {
			if (line[0] == '\n') {
				inheader = 0;
				continue;
			}
			if (line[0] == ' ' || line[0] == '\t' ||
			    (strncmp(line, "From:", 5) &&
			    strncmp(line, "Subject:", 8)))
				continue;
		}
		if (linecnt <= 0 || charcnt <= 0) {
			(void)fprintf(tp, "...more...%s", cr);
			(void)fclose(fi);
			return;
		}
		/* strip weird stuff so can't trojan horse stupid terminals */
		for (cp = line; (ch = *cp) && ch != '\n'; ++cp, --charcnt) {
			ch = toascii(ch);
			vis(visout, ch, VIS_SAFE|VIS_NOSLASH, cp[1]);
			for (s2 = visout; *s2; s2++)
				(void)fputc(*s2, tp);
		}
		(void)fputs(cr, tp);
		--linecnt;
	}
	(void)fprintf(tp, "----%s\n", cr);
	(void)fclose(fi);
}