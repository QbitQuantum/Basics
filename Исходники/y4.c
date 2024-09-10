static int
gtnm(void)
{
	register int s, val, c;

	/* read and convert an integer from the standard input */
	/* return the terminating character */
	/* blanks, tabs, and newlines are ignored */

	s = 1;
	val = 0;

	while ((c = getwc(finput)) != EOF) {
		if (iswdigit(c))
			val = val * 10 + c - L'0';
		else if (c == L'-')
			s = -1;
		else
			break;
	}
	*optimmem++ = s*val;
	if (optimmem >= &tracemem[new_memsize])
		exp_mem(0);
	return (c);
}