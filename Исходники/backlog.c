static inline int xmbswidth(const char *s, size_t n) {
#ifdef USE_UNICODE
	size_t i;
	int res = 0;

	mbtowc(NULL, NULL, 0);
	for (i = 0; i < n; ) {
		wchar_t ch;
		int ch_len;

		ch_len = mbtowc(&ch, &s[i], n - i);
		if (ch_len != -1) {
			int wc_width = wcwidth(ch);

			if (wc_width == -1)
				wc_width = 1;

			res += wc_width;
			i += ch_len;
		} else {
			i++;
			res++;
		}
	}
	return res;
#else
	return n;
#endif
}