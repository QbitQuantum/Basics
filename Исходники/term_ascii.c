/* ARGSUSED */
static void
locale_advance(struct termp *p, size_t len)
{
	size_t	 	i;

	for (i = 0; i < len; i++)
		putwchar(L' ');
}