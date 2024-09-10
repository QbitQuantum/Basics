int
__printf_render_chr(struct __printf_io *io, const struct printf_info *pi, const void *const *arg)
{
	int i;
	wint_t ii;
	unsigned char c;
	static const mbstate_t initial;		/* XXX: this is bogus! */
	mbstate_t mbs;
	size_t mbseqlen;
	char buf[MB_CUR_MAX];

	if (pi->is_long || pi->spec == 'C') {
		ii = *((wint_t *)arg[0]);

		mbs = initial;
		mbseqlen = wcrtomb(buf, (wchar_t)ii, &mbs);
		if (mbseqlen == (size_t) -1)
			return (-1);
		return (__printf_out(io, pi, buf, mbseqlen));
	}
	i = *((int *)arg[0]);
	c = i;
	i = __printf_out(io, pi, &c, 1);
	__printf_flush(io);
	return (i);
}