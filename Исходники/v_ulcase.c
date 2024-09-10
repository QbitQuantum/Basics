/*
 * ulcase --
 *	Change part of a line's case.
 */
static int
ulcase(SCR *sp, db_recno_t lno, CHAR_T *lp, size_t len, size_t scno, size_t ecno)
{
	size_t blen;
	int change, rval;
	ARG_CHAR_T ch;
	CHAR_T *p, *t, *bp;

	GET_SPACE_RETW(sp, bp, blen, len);
	MEMMOVEW(bp, lp, len);

	change = rval = 0;
	for (p = bp + scno, t = bp + ecno + 1; p < t; ++p) {
		ch = (UCHAR_T)*p;
		if (ISLOWER(ch)) {
			*p = TOUPPER(ch);
			change = 1;
		} else if (ISUPPER(ch)) {
			*p = TOLOWER(ch);
			change = 1;
		}
	}

	if (change && db_set(sp, lno, bp, len))
		rval = 1;

	FREE_SPACEW(sp, bp, blen);
	return (rval);
}