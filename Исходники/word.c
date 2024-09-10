/* ARGSUSED */
int
capword(int f, int n)
{
	int	c, s;
	RSIZE	size;

	if ((s = checkdirty(curbp)) != TRUE)
		return (s);
	if (curbp->b_flag & BFREADONLY) {
		dobeep();
		ewprintf("Buffer is read-only");
		return (FALSE);
	}

	if (n < 0)
		return (FALSE);
	while (n--) {
		while (inword() == FALSE) {
			if (forwchar(FFRAND, 1) == FALSE)
				return (TRUE);
		}
		size = countfword();
		undo_add_change(curwp->w_dotp, curwp->w_doto, size);

		if (inword() != FALSE) {
			c = lgetc(curwp->w_dotp, curwp->w_doto);
			if (ISLOWER(c) != FALSE) {
				c = TOUPPER(c);
				lputc(curwp->w_dotp, curwp->w_doto, c);
				lchange(WFFULL);
			}
			if (forwchar(FFRAND, 1) == FALSE)
				return (TRUE);
			while (inword() != FALSE) {
				c = lgetc(curwp->w_dotp, curwp->w_doto);
				if (ISUPPER(c) != FALSE) {
					c = TOLOWER(c);
					lputc(curwp->w_dotp, curwp->w_doto, c);
					lchange(WFFULL);
				}
				if (forwchar(FFRAND, 1) == FALSE)
					return (TRUE);
			}
		}
	}
	return (TRUE);
}