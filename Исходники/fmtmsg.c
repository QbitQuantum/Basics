static int
wrap(wchar_t *prefix, wchar_t *suffix, int indent_len, wchar_t *str)
{
	int	len, n, col;
	int	maxlen, tmpcol;
	wchar_t	*p, *pw, *ppw;
	static const wchar_t	eol[] = {L'\r', L'\n', L'\0'};

	/*
	 * Display the initial stuff followed by a colon.
	 */
	if ((len = wscol(suffix)))
		n = fprintf(stderr, gettext("%*ws: %ws: "),
			indent_len - len - 2, prefix, suffix);
	else
		n = fprintf(stderr, gettext("%*ws: "), indent_len, prefix);
	if (n <= 0)
		return (-1);

	maxlen = LINE_LEN - indent_len - 1;

	/* Check for bogus indent_len */
	if (maxlen < 1) {
		return (-1);
	}

	/*
	 * Loop once for each line of the string to display.
	 */
	for (p = str; *p; ) {

		/*
		 * Display the next "len" bytes of the string, where
		 * "len" is the smallest of:
		 *
		 *	- LINE_LEN
		 *	- # bytes before control character
		 *	- # bytes left in string
		 *
		 */

		len = wcscspn(p, eol);
		/* calc how many columns the string will take */
		col = wcswidth(p, len);
		if (col > maxlen) {
			/*
			 * How many characters fit into our desired line length
			 */
			pw = p;
			tmpcol = 0;
			while (*pw) {
				if (iswprint(*pw))
					tmpcol += wcwidth(*pw);
				if (tmpcol > maxlen)
					break;
				else
					pw++;
			}
			/*
			 * At this point, pw may point to:
			 * A null character:  EOL found (should never happen, though)
			 * The character that just overruns the maxlen.
			 */
			if (!*pw) {
				/*
				 * Found a EOL.
				 * This should never happen.
				 */
				len = pw - p;
				goto printline;
			}
			ppw = pw;
			/*
			 * Don't split words
			 *
			 * Bugid 4202307 - liblpoam in lp internal library doesn't
			 * handle multibyte character.
			 */
			while (pw > p) {
				if (iswspace(*pw) ||
				    (wdbindf(*(pw - 1), *pw, 1) < 5)) {
					break;
				} else {
					pw--;
				}
			}
			if (pw != p) {
				len = pw - p;
			} else {
				/*
				 * Failed to find the best place to fold.
				 * So, prints as much characters as maxlen allows
				 */
				len = ppw - p;
			}
		}

printline:
		for (n = 0; n < len; n++, p++) {
			if (iswprint(*p)) {
				if (fputwc(*p, stderr) == WEOF) {
					return (-1);
				}
			}
		}

		/*
		 * If we displayed up to a control character,
		 * put out the control character now; otherwise,
		 * put out a newline unless we've put out all
		 * the text.
		 */

		if (*p == L'\r' || *p == L'\n') {
			while (*p == L'\r' || *p == L'\n') {
				if (fputwc(*p, stderr) == WEOF)
					return (-1);
				p++;
			}
		} else if (*p) {
			if (fputwc(L'\n', stderr) == WEOF)
				return (-1);
		}

		while (iswspace(*p))
			p++;

		/*
		 * If the loop won't end this time (because we
		 * have more stuff to display) put out leading
		 * blanks to align the next line with the previous
		 * lines.
		 */
		if (*p) {
			for (n = 0; n < indent_len + 2; n++)
				(void) fputwc(L' ', stderr);
		}
	}

	return (1);
}