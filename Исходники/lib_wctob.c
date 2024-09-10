int wctob(wint_t wc)
{
	unsigned char pmb[MB_LEN_MAX];

	if (wc == WEOF) {
		return EOF;
	}

	return wctomb((char *)pmb, wc) == 1 ? (int)pmb[0] : EOF;
}