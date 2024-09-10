void
outc(wint_t c, int width) {
	int i;

	putwchar(c);
	if (must_use_uc && (curmode&UNDERL)) {
		for (i=0; i<width; i++)
			PRINT(CURS_LEFT);
		for (i=0; i<width; i++)
			PRINT(UNDER_CHAR);
	}
}