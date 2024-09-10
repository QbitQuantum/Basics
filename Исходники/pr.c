static	void
putspace(void)
{
	int nc = 0;

	for (; Nspace > 0; Outpos += nc, Nspace -= nc) {
#ifdef XPG4
		/* XPG4:  -i:  replace multiple SPACE chars with tab chars */
		if ((Nspace >= 2 && Itabn > 0 &&
			Nspace >= (nc = Itabn - Outpos % Itabn)) && !fold) {
#else
		/* Solaris:  -i:  replace white space with tab chars */
		if ((Itabn > 0 && Nspace >= (nc = Itabn - Outpos % Itabn)) &&
			!fold) {
#endif
			(void) fputwc(Itabc, stdout);
		} else {
			nc = 1;
			(void) putchar(' ');
		}
	}
}


static	void
unget(int colno)
{
	if (Buffer) {
		if (*(Colpts[colno].c_ptr-1) != '\t')
			--(Colpts[colno].c_ptr);
		if (Colpts[colno].c_lno)
			Colpts[colno].c_lno--;
	} else {
		if ((Multi == 'm' && colno == 0) || Multi != 'm')
			if (Lnumb && !foldcol)
				Lnumb--;
		colno = (Multi == 'a') ? 0 : colno;
		(void) ungetwc(Files[colno].f_nextc, Files[colno].f_f);
		Files[colno].f_nextc = C;
	}
}


/*
 * Defer message about failure to open file to prevent messing up
 * alignment of page with tear perforations or form markers.
 * Treat empty file as special case and report as diagnostic.
 */

static	FILE *
mustopen(char *s, FILS *f)
{
	char	*empty_file_msg = gettext("%s -- empty file");
	int	c;

	if (*s == '\0') {
		f->f_name = STDINNAME();
		f->f_f = stdin;
	} else if ((f->f_f = fopen(f->f_name = s, "r")) == NULL) {
		s = ffiler(f->f_name);
		s = strcpy((char *)getspace((UNS) strlen(s) + 1), s);
	}
	if (f->f_f != NULL) {
		errno = 0;
		f->f_nextc = _fgetwc_pr(f->f_f, &c);
		if (f->f_nextc != WEOF) {
			return (f->f_f);
		} else {	/* WEOF */
			if (errno == EILSEQ) {
				f->f_nextc = (wchar_t)c;
				return (f->f_f);
			}
			if (Multi == 'm')
				return (f->f_f);
		}
		(void) sprintf(s = (char *)getspace((UNS) strlen(f->f_name)
		    + 1 + (UNS) strlen(empty_file_msg)),
		    empty_file_msg, f->f_name);
		(void) fclose(f->f_f);
	}
	Error = 1;
	if (Report)
		if (Ttyout) {	/* accumulate error reports */
			Lasterr = Lasterr->e_nextp =
			    (ERR *) getspace((UNS) sizeof (ERR));
			Lasterr->e_nextp = NULL;
			Lasterr->e_mess = s;
		} else {	/* ok to print error report now */
			cerror(s);
			(void) putc('\n', stderr);
		}
	return ((FILE *)NULL);
}