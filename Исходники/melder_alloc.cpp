wchar_t * Melder_wcstok (wchar_t *string, const wchar_t *delimiter, wchar_t **last) {
	#if defined (__MINGW32__)
		(void) last;
		return wcstok (string, delimiter);
	#else
		return wcstok (string, delimiter, last);
	#endif
}