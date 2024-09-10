/*
 * werase --
 *	Erases everything on the window.
 */
int
werase(WINDOW *win)
{

	int     y;
	__LDATA *sp, *end, *start;
	attr_t	attr;

#ifdef DEBUG
	__CTRACE(__CTRACE_ERASE, "werase: (%p)\n", win);
#endif
	if (win != curscr)
		attr = win->battr & __ATTRIBUTES;
	else
		attr = 0;
	for (y = 0; y < win->maxy; y++) {
		start = win->alines[y]->line;
		end = &start[win->maxx];
		for (sp = start; sp < end; sp++)
#ifndef HAVE_WCHAR
			if (sp->ch != win->bch || sp->attr != 0) {
#else
			if (sp->ch != ( wchar_t )btowc(( int ) win->bch ) ||
			    (sp->attr & WA_ATTRIBUTES) != 0 || sp->nsp) {
#endif /* HAVE_WCHAR */
				if (sp->attr & __ALTCHARSET)
					sp->attr = attr | __ALTCHARSET;
				else
					sp->attr = attr;
#ifdef HAVE_WCHAR
				sp->ch = ( wchar_t )btowc(( int ) win->bch);
				if (_cursesi_copy_nsp(win->bnsp, sp) == ERR)
					return ERR;
				SET_WCOL( *sp, 1 );
#else
				sp->ch = win->bch;
#endif /* HAVE_WCHAR */
			}
	}
	/*
	 * Mark the whole window as changed in case we have overlapping
	 * windows - this will result in the (intended) clearing of the
	 * screen over the area covered by the window. */
	__touchwin(win);
	wmove(win, 0, 0);
	return (OK);
}