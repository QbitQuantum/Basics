/*
 * sscr_insert --
 *	Take a line from the shell and insert it into the file.
 */
static int
sscr_insert(SCR *sp)
{
	struct timeval tv;
	CHAR_T *endp, *p, *t;
	SCRIPT *sc;
	fd_set rdfd;
	db_recno_t lno;
	size_t blen, len = 0, tlen;
	e_key_t value;
	int nr, rval;
	CHAR_T *bp;

	/* Find out where the end of the file is. */
	if (db_last(sp, &lno))
		return (1);

#define	MINREAD	1024
	GET_SPACE_RETW(sp, bp, blen, MINREAD);
	endp = bp;

	/* Read the characters. */
	rval = 1;
	sc = sp->script;
more:	switch (nr = read(sc->sh_master, endp, MINREAD)) {
	case  0:			/* EOF; shell just exited. */
		sscr_end(sp);
		rval = 0;
		goto ret;
	case -1:			/* Error or interrupt. */
		msgq(sp, M_SYSERR, "shell");
		goto ret;
	default:
		endp += nr;
		break;
	}

	/* Append the lines into the file. */
	for (p = t = bp; p < endp; ++p) {
		value = KEY_VAL(sp, *p);
		if (value == K_CR || value == K_NL) {
			len = p - t;
			if (db_append(sp, 1, lno++, t, len))
				goto ret;
			t = p + 1;
		}
	}
	if (p > t) {
		len = p - t;
		/*
		 * If the last thing from the shell isn't another prompt, wait
		 * up to 1/10 of a second for more stuff to show up, so that
		 * we don't break the output into two separate lines.  Don't
		 * want to hang indefinitely because some program is hanging,
		 * confused the shell, or whatever.
		 */
		if (!sscr_matchprompt(sp, t, len, &tlen) || tlen != 0) {
			tv.tv_sec = 0;
			tv.tv_usec = 100000;
			FD_ZERO(&rdfd);
			FD_SET(sc->sh_master, &rdfd);
			if (select(sc->sh_master + 1,
			    &rdfd, NULL, NULL, &tv) == 1) {
				MEMMOVE(bp, t, len);
				endp = bp + len;
				goto more;
			}
		}
		if (sscr_setprompt(sp, t, len))
			return (1);
		if (db_append(sp, 1, lno++, t, len))
			goto ret;
	}

	/* The cursor moves to EOF. */
	sp->lno = lno;
	sp->cno = len ? len - 1 : 0;
	rval = vs_refresh(sp, 1);

ret:	FREE_SPACEW(sp, bp, blen);
	return (rval);
}