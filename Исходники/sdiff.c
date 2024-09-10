static void
putline(FILE *file, char *start, int num)
{
	char	*cp, *end;
	int	i, len, d_col;
	wchar_t	wc;

	cp = start;
	end = cp + num;
	while (cp < end) {
		if (isascii(*cp)) {
			(void) putc(*cp++, file);
			continue;
		}

		if ((len = end - cp) > MB_LEN_MAX)
			len = MB_LEN_MAX;

		if ((len = mbtowc(&wc, cp, len)) <= 0) {
			(void) putc(*cp++, file);
			continue;
		}

		if ((d_col = wcwidth(wc)) <= 0)
			d_col = len;

		if ((cp + d_col) > end)
			return;

		for (i = 0; i < len; i++)
			(void) putc(*cp++, file);
	}
}