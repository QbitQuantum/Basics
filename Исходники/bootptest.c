/*
 * Print out a filename (or other ascii string).
 * Return true if truncated.
 */
int
printfn(u_char *s, u_char *ep)
{
	u_char c;

	putchar('"');
	while ((c = *s++) != 0) {
		if (s > ep) {
			putchar('"');
			return (1);
		}
		if (!isascii(c)) {
			c = toascii(c);
			putchar('M');
			putchar('-');
		}
		if (!isprint(c)) {
			c ^= 0x40;			/* DEL to ?, others to alpha */
			putchar('^');
		}
		putchar(c);
	}
	putchar('"');
	return (0);
}