WINDOW *
__newwin(SCREEN *screen, int nlines, int ncols, int by, int bx, int ispad)
{
	WINDOW *win;
	__LINE *lp;
	int     i, j;
	int	maxy, maxx;
	__LDATA *sp;

	if (by < 0 || bx < 0)
		return (NULL);

	maxy = nlines > 0 ? nlines : LINES - by + nlines;
	maxx = ncols > 0 ? ncols : COLS - bx + ncols;

	if ((win = __makenew(screen, maxy, maxx, by, bx, 0, ispad)) == NULL)
		return (NULL);

	win->bch = ' ';
	if (__using_color)
		win->battr = __default_color;
	else
		win->battr = 0;
	win->nextp = win;
	win->ch_off = 0;
	win->orig = NULL;
	win->reqy = nlines;
	win->reqx = ncols;

#ifdef DEBUG
	__CTRACE(__CTRACE_WINDOW, "newwin: win->ch_off = %d\n", win->ch_off);
#endif

	for (i = 0; i < maxy; i++) {
		lp = win->alines[i];
		if (ispad)
			lp->flags = __ISDIRTY;
		else
			lp->flags = 0;
		for (sp = lp->line, j = 0; j < maxx; j++, sp++) {
			sp->attr = 0;
#ifndef HAVE_WCHAR
			sp->ch = win->bch;
#else
			sp->ch = ( wchar_t )btowc(( int ) win->bch );
			sp->nsp = NULL;
			SET_WCOL( *sp, 1 );
#endif /* HAVE_WCHAR */
		}
		lp->hash = __hash((char *)(void *)lp->line,
		    (size_t) (ncols * __LDATASIZE));
	}
	return (win);
}