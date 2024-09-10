/*
 * _cursesi_addwchar -
 *	Internal function to add a wide character and update the row
 * and column positions.
 */
int
_cursesi_addwchar(WINDOW *win, __LINE **lnp, int *y, int *x,
		  const cchar_t *wch)
{
#ifndef HAVE_WCHAR
	return (ERR);
#else
	int sx = 0, ex = 0, cw = 0, i = 0, newx = 0;
	__LDATA *lp = &win->alines[*y]->line[*x], *tp = NULL;
	nschar_t *np = NULL;
	cchar_t cc;
	attr_t attributes;

	/* special characters handling */
	switch (wch->vals[0]) {
	case L'\b':
		if (--*x < 0)
			*x = 0;
		win->curx = *x;
		return OK;
	case L'\r':
		*x = 0;
		return OK;
	case L'\n':
		wclrtoeol(win);
		PSYNCH_IN;
		*x = 0;
		(*lnp)->flags &= ~__ISPASTEOL;
		if (*y == win->scr_b) {
			if (!(win->flags & __SCROLLOK))
				return ERR;
			PSYNCH_OUT;
			scroll(win);
			PSYNCH_IN;
		} else {
			(*y)++;
		}
		PSYNCH_OUT;
		return OK;
	case L'\t':
		cc.vals[0] = L' ';
		cc.elements = 1;
		cc.attributes = win->wattr;
		for (i = 0; i < 8 - (*x % 8); i++) {
			if (wadd_wch(win, &cc) == ERR)
				return ERR;
		}
		return OK;
	}

	/* check for non-spacing character */
	if (!wcwidth(wch->vals[0])) {
#ifdef DEBUG
		__CTRACE(__CTRACE_INPUT,
			 "_cursesi_addwchar: char '%c' is non-spacing\n",
			 wch->vals[0]);
#endif /* DEBUG */
		cw = WCOL(*lp);
		if (cw < 0) {
			lp += cw;
			*x += cw;
		}
		for (i = 0; i < wch->elements; i++) {
			if (!(np = (nschar_t *) malloc(sizeof(nschar_t))))
				return ERR;;
			np->ch = wch->vals[i];
			np->next = lp->nsp;
			lp->nsp = np;
		}
		(*lnp)->flags |= __ISDIRTY;
		newx = *x + win->ch_off;
		if (newx < *(*lnp)->firstchp)
			*(*lnp)->firstchp = newx;
		if (newx > *(*lnp)->lastchp)
			*(*lnp)->lastchp = newx;
		__touchline(win, *y, *x, *x);
		return OK;
	}
	/* check for new line first */
	if ((*lnp)->flags & __ISPASTEOL) {
		*x = 0;
		(*lnp)->flags &= ~__ISPASTEOL;
		if (*y == win->scr_b) {
			if (!(win->flags & __SCROLLOK))
				return ERR;
			PSYNCH_OUT;
			scroll(win);
			PSYNCH_IN;
		} else {
			(*y)++;
		}
		(*lnp) = win->alines[*y];
		lp = &win->alines[*y]->line[*x];
	}
	/* clear out the current character */
	cw = WCOL(*lp);
	if (cw >= 0) {
		sx = *x;
	} else {
		for (sx = *x - 1; sx >= max(*x + cw, 0); sx--) {
#ifdef DEBUG
			__CTRACE(__CTRACE_INPUT,
				 "_cursesi_addwchar: clear current char (%d,%d)\n",
				 *y, sx);
#endif /* DEBUG */
			tp = &win->alines[*y]->line[sx];
			tp->ch = (wchar_t) btowc((int) win->bch);
			if (_cursesi_copy_nsp(win->bnsp, tp) == ERR)
				return ERR;

			tp->attr = win->battr;
			SET_WCOL(*tp, 1);
		}
		sx = *x + cw;
		(*lnp)->flags |= __ISDIRTY;
		newx = sx + win->ch_off;
		if (newx < *(*lnp)->firstchp)
			*(*lnp)->firstchp = newx;
	}

	/* check for enough space before the end of line */
	cw = wcwidth(wch->vals[0]);
	if (cw < 0)
		cw = 1;
	if (cw > win->maxx - *x) {
#ifdef DEBUG
		__CTRACE(__CTRACE_INPUT,
			 "_cursesi_addwchar: clear EOL (%d,%d)\n",
			 *y, *x);
#endif /* DEBUG */
		(*lnp)->flags |= __ISDIRTY;
		newx = *x + win->ch_off;
		if (newx < *(*lnp)->firstchp)
			*(*lnp)->firstchp = newx;
		for (tp = lp; *x < win->maxx; tp++, (*x)++) {
			tp->ch = (wchar_t) btowc((int) win->bch);
			if (_cursesi_copy_nsp(win->bnsp, tp) == ERR)
				return ERR;
			tp->attr = win->battr;
			SET_WCOL(*tp, 1);
		}
		newx = win->maxx - 1 + win->ch_off;
		if (newx > *(*lnp)->lastchp)
			*(*lnp)->lastchp = newx;
		__touchline(win, *y, sx, (int) win->maxx - 1);
		sx = *x = 0;
		if (*y == win->scr_b) {
			if (!(win->flags & __SCROLLOK))
				return ERR;
			PSYNCH_OUT;
			scroll(win);
			PSYNCH_IN;
		} else {
			(*y)++;
		}
		lp = &win->alines[*y]->line[0];
		(*lnp) = win->alines[*y];
	}
	win->cury = *y;

	/* add spacing character */
#ifdef DEBUG
	__CTRACE(__CTRACE_INPUT,
		 "_cursesi_addwchar: add character (%d,%d) 0x%x\n",
		 *y, *x, wch->vals[0]);
#endif /* DEBUG */
	(*lnp)->flags |= __ISDIRTY;
	newx = *x + win->ch_off;
	if (newx < *(*lnp)->firstchp)
		*(*lnp)->firstchp = newx;
	if (lp->nsp) {
		__cursesi_free_nsp(lp->nsp);
		lp->nsp = NULL;
	}

	lp->ch = wch->vals[0];

	attributes = (win->wattr | wch->attributes)
		& (WA_ATTRIBUTES & ~__COLOR);
	if (wch->attributes & __COLOR)
		attributes |= wch->attributes & __COLOR;
	else if (win->wattr & __COLOR)
		attributes |= win->wattr & __COLOR;
	if (attributes & __COLOR)
		lp->attr = attributes | (win->battr & ~__COLOR);
	else
		lp->attr = attributes | win->battr;

	SET_WCOL(*lp, cw);

#ifdef DEBUG
	__CTRACE(__CTRACE_INPUT,
		 "_cursesi_addwchar: add spacing char 0x%x, attr 0x%x\n",
		 lp->ch, lp->attr);
#endif /* DEBUG */

	if (wch->elements > 1) {
		for (i = 1; i < wch->elements; i++) {
			np = (nschar_t *)malloc(sizeof(nschar_t));
			if (!np)
				return ERR;;
			np->ch = wch->vals[i];
			np->next = lp->nsp;
#ifdef DEBUG
			__CTRACE(__CTRACE_INPUT,
			    "_cursesi_addwchar: add non-spacing char 0x%x\n", np->ch);
#endif /* DEBUG */
			lp->nsp = np;
		}
	}
#ifdef DEBUG
	__CTRACE(__CTRACE_INPUT, "_cursesi_addwchar: non-spacing list header: %p\n",
	    lp->nsp);
	__CTRACE(__CTRACE_INPUT, "_cursesi_addwchar: add rest columns (%d:%d)\n",
		sx + 1, sx + cw - 1);
#endif /* DEBUG */
	for (tp = lp + 1, *x = sx + 1; *x - sx <= cw - 1; tp++, (*x)++) {
		if (tp->nsp) {
			__cursesi_free_nsp(tp->nsp);
			tp->nsp = NULL;
		}
		tp->ch = wch->vals[0];
		tp->attr = lp->attr & WA_ATTRIBUTES;
		/* Mark as "continuation" cell */
		tp->attr |= __WCWIDTH;
	}
	if (*x == win->maxx) {
		(*lnp)->flags |= __ISPASTEOL;
		newx = win->maxx - 1 + win->ch_off;
		if (newx > *(*lnp)->lastchp)
			*(*lnp)->lastchp = newx;
		__touchline(win, *y, sx, (int) win->maxx - 1);
		win->curx = sx;
	} else {
		win->curx = *x;

		/* clear the remining of the current characer */
		if (*x && *x < win->maxx) {
			ex = sx + cw;
			tp = &win->alines[*y]->line[ex];
			while (ex < win->maxx && WCOL(*tp) < 0) {
#ifdef DEBUG
				__CTRACE(__CTRACE_INPUT,
					 "_cursesi_addwchar: clear "
					 "remaining of current char (%d,%d)nn",
					 *y, ex);
#endif /* DEBUG */
				tp->ch = (wchar_t) btowc((int) win->bch);
				if (_cursesi_copy_nsp(win->bnsp, tp) == ERR)
					return ERR;
				tp->attr = win->battr;
				SET_WCOL(*tp, 1);
				tp++, ex++;
			}
			newx = ex - 1 + win->ch_off;
			if (newx > *(*lnp)->lastchp)
				*(*lnp)->lastchp = newx;
			__touchline(win, *y, sx, ex - 1);
		}
	}

#ifdef DEBUG
	__CTRACE(__CTRACE_INPUT, "add_wch: %d : 0x%x\n", lp->ch, lp->attr);
#endif /* DEBUG */
	return OK;
#endif
}