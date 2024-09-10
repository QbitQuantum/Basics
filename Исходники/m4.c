static void
error3()
{
	if (Cp) {
		struct call	*mptr;

		/* fix limit */
		*op = EOS;
		(Cp+1)->argp = Ap+1;

		for (mptr = callst; mptr <= Cp; ++mptr) {
			wchar_t	**aptr, **lim;

			aptr = mptr->argp;
			lim = (mptr+1)->argp-1;
			if (mptr == callst)
				(void) fputws(*aptr, stderr);
			++aptr;
			(void) fputs("(", stderr);
			if (aptr < lim)
				for (;;) {
					(void) fputws(*aptr++, stderr);
					if (aptr >= lim)
						break;
					(void) fputs(",", stderr);
				}
		}
		while (--mptr >= callst)
			(void) fputs(")", stderr);

		(void) fputs("\n", stderr);
	}
	delexit(NOT_OK, 1);
}