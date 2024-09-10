const u_char *
c_print(register const u_char *s, register const u_char *ep)
{
	register u_char c;
	register int flag;

	flag = 1;
	while (ep == NULL || s < ep) {
		c = *s++;
		if (c == '\0') {
			flag = 0;
			break;
		}
		if (!isascii(c)) {
			c = toascii(c);
			putchar('M');
			putchar('-');
		}
		if (!isprint(c)) {
			c ^= 0x40;	/* DEL to ?, others to alpha */
			putchar('^');
		}
		putchar(c);
	}
	if (flag)
		return NULL;
	return (s);
}