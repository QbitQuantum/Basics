void _WLdtob(_WPft *px, wchar_t code)
	{	/* convert long double to wide text */
	wchar_t ac[MAXDIG];
	wchar_t *p = ac;
	long double ldval = px->v.ld;
	short errx, nsig, xexp;

	static const wchar_t inf[] =
		{L'i', L'n', L'f', L'\0'};
	static const wchar_t Inf[] =
		{L'I', L'N', L'F', L'\0'};
	static const wchar_t nan_str[] =
		{L'n', L'a', L'n', L'\0'};
	static const wchar_t Nan[] =
		{L'N', L'A', L'N', L'\0'};
	static const wchar_t xdigs[] =
		{L'0', L'1', L'2', L'3',
		L'4', L'5', L'6', L'7',
		L'8', L'9', L'a', L'b',
		L'c', L'd', L'e', L'f'};
	static const wchar_t Xdigs[] =
		{L'0', L'1', L'2', L'3',
		L'4', L'5', L'6', L'7',
		L'8', L'9', L'A', L'B',
		L'C', L'D', L'E', L'F'};

	if (code == L'a' || code == L'A')
		;
	else if (px->prec < 0)
		px->prec = 6;
	else if (px->prec == 0
		&& (code == L'g' || code == L'G'))
		px->prec = 1;
	if ((errx = _LDunscale(&xexp, &px->v.ld)) == _NANCODE)
		{	/* x == NaN */
		wmemcpy(px->s, code == L'a' || code == L'e'
			|| code == L'f' || code == L'g'
				? nan_str : Nan, px->n1 = 3);
		return;
		}
	else if (0 < errx)
		{	/* x == INF */
		wmemcpy(px->s, code == L'a' || code == L'e'
			|| code == L'f' || code == L'g'
				? inf : Inf, px->n1 = 3);
		return;
		}

	if (code == L'a' || code == L'A')
		{	/* put "0x" */
		*px->s++ = L'0';
		*px->s++ = code == L'a' ? L'x' : L'X';
		px->n0 +=2;
		}

	if (0 == errx)	/* x == 0 */
		nsig = 0, xexp = 0;
	else if (code == L'a' || code == L'A')
		{	/* 0 < |x|, generate hex fraction, binary exponent */
		const wchar_t *digits = code == L'a' ? xdigs : Xdigs;
		int gen;

		nsig = px->prec < 0 ? MAXDIG - NXDIG : px->prec + 1;
		gen = nsig + 1;
		ldval = ldval < 0 ? -px->v.ld : px->v.ld;
		xexp -= 4;	/* one leading nonzero hex digit */

		for (*p++ = 0x0; 0 < gen && 0 < ldval; p += NXDIG)
			{	/* convert NXDIG at a time */
			int j;
			long lo;

			_LDscale(&ldval, 4 * NXDIG);
			lo = (long)ldval;
			if (0 < (gen -= NXDIG))
				ldval -= (long double)lo;
			for (p += NXDIG, j = NXDIG; 0 < lo && 0 <= --j; )
				*--p = (int)(lo & 0xf), lo >>= 4;
			while (0 <= --j)
				*--p = 0;
			}
		gen = p - &ac[1];
		p = &ac[1];
		if (gen < nsig)
			nsig = gen;
		if (0 <= nsig)
			{	/* round and strip trailing zeros */
			const char drop = nsig < gen && 0x8 <= p[nsig] ? 0xf : 0x0;
			int n;

			for (n = nsig; p[--n] == drop; )
				--nsig;
			if (drop == 0xf)
				++p[n];
			if (n < 0)
				--p, ++nsig, xexp += 4;
			for (n = nsig; 0 <= --n; )
				p[n] = digits[p[n]];
			}
		if (px->prec < 0)
			px->prec = nsig - 1;
		}
	else
		{	/* 0 < |x|, generate decimal fraction and exponent */
		 {	/* scale ldval to ~~10^(NDIG/2) */