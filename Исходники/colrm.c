int process_input(unsigned long first, unsigned long last)
{
	unsigned long ct = 0;
	wint_t c;
	unsigned long i;
	int w;
	int padding;

	for (;;) {
		c = getwc(stdin);
		if (c == WEOF)
			return 0;
		if (c == '\t')
			w = ((ct + 8) & ~7) - ct;
		else if (c == '\b')
			w = (ct ? ct - 1 : 0) - ct;
		else {
			w = wcwidth(c);
			if (w < 0)
				w = 0;
		}
		ct += w;
		if (c == '\n') {
			putwc(c, stdout);
			ct = 0;
			continue;

		}
		if (!first || ct < first) {
			putwc(c, stdout);
			continue;
		}
		break;
	}

	for (i = ct - w + 1; i < first; i++)
		putwc(' ', stdout);

	/* Loop getting rid of characters */
	while (!last || ct < last) {
		c = getwc(stdin);
		if (c == WEOF)
			return 0;
		if (c == '\n') {
			putwc(c, stdout);
			return 1;
		}
		if (c == '\t')
			ct = (ct + 8) & ~7;
		else if (c == '\b')
			ct = ct ? ct - 1 : 0;
		else {
			w = wcwidth(c);
			if (w < 0)
				w = 0;
			ct += w;
		}
	}

	padding = 0;

	/* Output last of the line */
	for (;;) {
		c = getwc(stdin);
		if (c == WEOF)
			break;
		if (c == '\n') {
			putwc(c, stdout);
			return 1;
		}
		if (padding == 0 && last < ct) {
			for (i = last; i < ct; i++)
				putwc(' ', stdout);
			padding = 1;
		}
		putwc(c, stdout);
	}
	return 0;
}