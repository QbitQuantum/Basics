int
__m_wacs_cc(const cchar_t *acs, cchar_t *cc)
{
	int i;
	unsigned char *acsc, mb[MB_LEN_MAX];

	*cc = *acs;
	cc->_f = 1;

	/* Is it a single-byte character? */
	if (!(acs->_at & WA_ALTCHARSET)
	|| acs->_n != 1 || wctomb((char *) mb, acs->_wc[0]) != 1)
		/* No, just return the original character. */
		return 0;

	/* Pick the acs mapping string to use. */
	if (acs_chars == (char *) 0) {
		/* Use primary character set. */
		acsc = acs_defaults;
		cc->_at &= ~A_ALTCHARSET;
	} else {
		acsc = (unsigned char *) acs_chars;
	}

	/* Assume that acsc is even in length. */
	for (i = 0; acsc[i] != '\0'; i += 2) {
		if (acsc[i] == *mb) {
			(void) mbtowc(cc->_wc, (char *) &acsc[i+1], 1);
			cc->_at |= A_ALTCHARSET;
			break;
		}
	}

	return 0;
}