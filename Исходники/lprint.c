static void
vputc(unsigned char ch)
{
	int meta;

	if (!isprint(ch) && !isascii(ch)) {
		(void)putchar('M');
		(void)putchar('-');
		ch = toascii(ch);
		meta = 1;
	} else
		meta = 0;
	if (isprint(ch) || (!meta && (ch == ' ' || ch == '\t' || ch == '\n')))
		(void)putchar(ch);
	else {
		(void)putchar('^');
		(void)putchar(ch == '\177' ? '?' : ch | 0100);
	}
}