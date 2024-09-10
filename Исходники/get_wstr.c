/*
 * __wgetn_wstr --
 *	The actual implementation.
 *	Note that we include a trailing L'\0' for safety, so str will contain
 *	at most n - 1 other characters.
 */
int
__wgetn_wstr(WINDOW *win, wchar_t *wstr, int n)
{
	wchar_t *ostr, ec, kc, sc[ 2 ];
	int oldx, remain;
	wint_t wc;
	cchar_t cc;

	ostr = wstr;
	if ( erasewchar( &ec ) == ERR )
		return ERR;
	if ( killwchar( &kc ) == ERR )
		return ERR;
	sc[ 0 ] = ( wchar_t )btowc( ' ' );
	sc[ 1 ] = L'\0';
	setcchar( &cc, sc, win->wattr, 0, NULL );
	oldx = win->curx;
	remain = n - 1;

	while (wget_wch(win, &wc) != ERR
	       && wc != L'\n' && wc != L'\r') {
#ifdef DEBUG
		__CTRACE(__CTRACE_INPUT,
		    "__wgetn_wstr: win %p, char 0x%x, remain %d\n",
		    win, wc, remain);
#endif
		*wstr = wc;
		touchline(win, win->cury, 1);
		if (wc == ec || wc == KEY_BACKSPACE || wc == KEY_LEFT) {
			*wstr = L'\0';
			if (wstr != ostr) {
				if ((wchar_t)wc == ec) {
					mvwadd_wch(win, win->cury,
						win->curx, &cc);
					wmove(win, win->cury, win->curx - 1);
				}
				if (wc == KEY_BACKSPACE || wc == KEY_LEFT) {
					/* getch() displays the key sequence */
					mvwadd_wch(win, win->cury,
						win->curx - 1, &cc);
					mvwadd_wch(win, win->cury,
						win->curx - 2, &cc);
					wmove(win, win->cury, win->curx - 1);
				}
				wstr--;
				if (n != -1) {
					/* We're counting chars */
					remain++;
				}
			} else { /* str == ostr */
				if (wc == KEY_BACKSPACE || wc == KEY_LEFT)
					/* getch() displays the other keys */
					mvwadd_wch(win, win->cury,
						win->curx - 1, &cc);
				wmove(win, win->cury, oldx);
			}
		} else if (wc == kc) {
			*wstr = L'\0';
			if (wstr != ostr) {
				/* getch() displays the kill character */
				mvwadd_wch(win, win->cury, win->curx - 1, &cc);
				/* Clear the characters from screen and str */
				while (wstr != ostr) {
					mvwadd_wch(win, win->cury,
						win->curx - 1, &cc);
					wmove(win, win->cury, win->curx - 1);
					wstr--;
					if (n != -1)
						/* We're counting chars */
						remain++;
				}
				mvwadd_wch(win, win->cury, win->curx - 1, &cc);
				wmove(win, win->cury, win->curx - 1);
			} else
				/* getch() displays the kill character */
				mvwadd_wch( win, win->cury, oldx, &cc );
			wmove(win, win->cury, oldx);
		} else if (wc >= KEY_MIN && wc <= KEY_MAX) {
			/* get_wch() displays these characters */
			mvwadd_wch( win, win->cury, win->curx - 1, &cc );
			wmove(win, win->cury, win->curx - 1);
		} else {
			if (remain) {
				wstr++;
				remain--;
			} else {
				mvwadd_wch(win, win->cury, win->curx - 1, &cc);
				wmove(win, win->cury, win->curx - 1);
			}
		}
	}

	if (wc == ERR) {
		*wstr = L'\0';
		return ERR;
	}
	*wstr = L'\0';
	return OK;
}