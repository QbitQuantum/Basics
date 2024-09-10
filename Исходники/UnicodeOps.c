int unicodeGetXRanges(char *utf8, int utf8Length, int *resultPtr, int resultLength) {
	SCRIPT_STRING_ANALYSIS ssa;
	HDC				hdc;
	int				i, pX;
	HRESULT			r;

	if (utf8Length == 0) return 0;

	g_wLength = 0;
	hdc = CreateCompatibleDC(0);
	ssa = analyze(hdc, utf8, utf8Length);
	if (ssa != NULL) {
		for (i = 0; i < g_wLength; i++) {
			r = ScriptStringCPtoX(ssa, i, FALSE, &pX);
			if (FAILED(r)) pX = -1;
			resultPtr[2 * i] = pX;
			r = ScriptStringCPtoX(ssa, i, TRUE, &pX);
			if (FAILED(r)) pX = -1;
			resultPtr[(2 * i) + 1] = pX;
		}
		ScriptStringFree(&ssa);
	}
	DeleteDC(hdc);
	return g_wLength;
}