static void
num_arg(char *arg, int md)
{
	offset_t repeat, toline;
	char rep[21];
	char *ptr;
	int		len;

	ptr = rep;
	for (++arg; *arg != '}'; arg += len) {
		if (*arg == NULL)
			fatal("%s: missing '}'\n", targ);
		if ((len = mblen(arg, MB_LEN_MAX)) <= 0)
			len = 1;
		if ((ptr + len) >= &rep[20])
			fatal("%s: Repeat count too large\n", targ);
		(void) memcpy(ptr, arg, len);
		ptr += len;
	}
	*ptr = NULL;
	if ((asc_to_ll(rep, &repeat) == ERR) || repeat < 0L)
		fatal("Illegal repeat count: %s\n", targ);
	if (md == LINMODE) {
		toline = offset = curline;
		for (; repeat > 0LL; repeat--) {
			toline += offset;
			to_line(toline);
		}
	} else	if (md == EXPMODE)
			for (; repeat > 0LL; repeat--)
				to_line(findline(expbuf, offset));
		else
			fatal("No operation for %s\n", targ);
}