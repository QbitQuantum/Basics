/*
 * wdelch --
 *	Do a delete-char on the line, leaving (cury, curx) unchanged.
 */
int
wdelch(WINDOW *win)
{
	__LDATA *end, *temp1, *temp2;

	int cw, sx;
	nschar_t *np, *tnp;

	end = &win->alines[win->cury]->line[win->maxx - 1];
	sx = win->curx;
	temp1 = &win->alines[win->cury]->line[win->curx];
	cw = WCOL( *temp1 );
	if ( cw < 0 ) {
		temp1 += cw;
		sx += cw;
		cw = WCOL( *temp1 );
	}
	np = temp1->nsp;
	if (np) {
		while ( np ) {
			tnp = np->next;
			free( np );
			np = tnp;
		}
		temp1->nsp = NULL;
	}
	if ( sx + cw < win->maxx ) {
		temp2 = temp1 + cw;
		while ( temp1 < end - ( cw - 1 )) {
			( void )memcpy( temp1, temp2, sizeof( __LDATA ));
			temp1++, temp2++;
		}
	}
	while ( temp1 <= end ) {
		temp1->ch = ( wchar_t )btowc(( int ) win->bch );
		temp1->attr = 0;
		if (_cursesi_copy_nsp(win->bnsp, temp1) == ERR)
			return ERR;
		SET_WCOL(*temp1, 1);
		temp1++;
	}
	__touchline(win, (int) win->cury, sx, (int) win->maxx - 1);
	return (OK);
}