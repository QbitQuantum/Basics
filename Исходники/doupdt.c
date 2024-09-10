static void clrupdate(WINDOW *scr)
{
  register int *src;
  register int *dst;
  register int i;
  register int j;
  WINDOW *w;

  w = curscr;

  if (scr != w) {		/* copy scr to curscr */
	for (i = 0; i < LINES; i++) {
		src = scr->_line[i];
		dst = w->_line[i];
		for (j = 0; j < COLS; j++) *dst++ = *src++;
	}			/* for */
  }				/* if */
  newattr(scr->_attrs);
  clrscr();
  scr->_clear = FALSE;
  for (i = 0; i < LINES; i++) {	/* update physical screen */
	src = w->_line[i];
	j = 0;
	while (j < COLS) {
		if (*src != (' ' | ATR_NRM)) {
			gotoxy(i, j);
			while (j < COLS && (*src != (' ' | ATR_NRM))) {
				Putchar(*src++);
				j++;
			}
		} else {
			src++;
			j++;
		}
	}			/* for */
  }				/* for */
  fflush(stdout);
}				/* clrupdate */