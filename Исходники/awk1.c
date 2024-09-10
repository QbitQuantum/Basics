/*
 * Return a character for lexical analyser.
 * Only one returned character is (not enforced) legitimite.
 */
static void
lexungetc(wint_t c)
{
	if (c == '\n')
		--lineno;
	if (c != WEOF) {
		if (conptr == &context[0])
			conptr = &context[NCONTEXT];
		*--conptr = '\0';
	}
	if (progfp != FNULL) {
		(void) ungetwc(c, progfp);
		return;
	}
	if (c == WEOF)
		return;
	*--progptr = c;
	proglen++;
}