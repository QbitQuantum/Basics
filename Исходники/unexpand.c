static int
tabify(const char *curfile)
{
	int dcol, doneline, limit, n, ocol, width;
	wint_t ch;

	limit = nstops == 1 ? INT_MAX : tabstops[nstops - 1] - 1;

	doneline = ocol = dcol = 0;
	while ((ch = getwchar()) != WEOF) {
		if (ch == ' ' && !doneline) {
			if (++dcol >= limit)
				doneline = 1;
			continue;
		} else if (ch == '\t') {
			if (nstops == 1) {
				dcol = (1 + dcol / tabstops[0]) *
				    tabstops[0];
				continue;
			} else {
				for (n = 0; tabstops[n] - 1 < dcol &&
				    n < nstops; n++)
					;
				if (n < nstops - 1 && tabstops[n] - 1 < limit) {
					dcol = tabstops[n];
					continue;
				}
				doneline = 1;
			}
		}

		/* Output maximal number of tabs. */
		if (nstops == 1) {
			while (((ocol + tabstops[0]) / tabstops[0])
			    <= (dcol / tabstops[0])) {
				if (dcol - ocol < 2)
					break;
				putwchar('\t');
				ocol = (1 + ocol / tabstops[0]) *
				    tabstops[0];
			}
		} else {
			for (n = 0; tabstops[n] - 1 < ocol && n < nstops; n++)
				;
			while (ocol < dcol && n < nstops && ocol < limit) {
				putwchar('\t');
				ocol = tabstops[n++];
			}
		}

		/* Then spaces. */
		while (ocol < dcol && ocol < limit) {
			putwchar(' ');
			ocol++;
		}

		if (ch == '\b') {
			putwchar('\b');
			if (ocol > 0)
				ocol--, dcol--;
		} else if (ch == '\n') {
			putwchar('\n');
			doneline = ocol = dcol = 0;
			continue;
		} else if (ch != ' ' || dcol > limit) {
			putwchar(ch);
			if ((width = wcwidth(ch)) > 0)
				ocol += width, dcol += width;
		}

		/*
		 * Only processing leading blanks or we've gone past the
		 * last tab stop. Emit remainder of this line unchanged.
		 */
		if (!all || dcol >= limit) {
			while ((ch = getwchar()) != '\n' && ch != WEOF)
				putwchar(ch);
			if (ch == '\n')
				putwchar('\n');
			doneline = ocol = dcol = 0;
		}
	}
	if (ferror(stdin)) {
		warn("%s", curfile);
		return (1);
	}
	return (0);
}