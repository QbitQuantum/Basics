static int
scanner_error(mvc *lc, int cur)
{
	switch (cur) {
	case EOF:
		(void) sql_error(lc, 1, "unexpected end of input");
		return -1;	/* EOF needs -1 result */
	default:
		/* on Windows at least, iswcntrl returns TRUE for
		 * U+FEFF, but we just want consistent error
		 * messages */
		(void) sql_error(lc, 1, "unexpected%s character (U+%04X)", iswcntrl(cur) && cur != 0xFEFF ? " control" : "", cur);
	}
	return LEX_ERROR;
}