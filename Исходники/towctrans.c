static wchar_t __towcase(wchar_t wc, int lower)
{
	int i;
	int lmul = 2*lower-1;
	int lmask = lower-1;
	/* no letters with case in these large ranges */
	if (!iswalpha(wc)
	 || (unsigned)wc - 0x0600 <= 0x0fff-0x0600
	 || (unsigned)wc - 0x2e00 <= 0xa63f-0x2e00
	 || (unsigned)wc - 0xa800 <= 0xfeff-0xa800)
		return wc;
	/* special case because the diff between upper/lower is too big */
	if (lower && (unsigned)wc - 0x10a0 < 0x2e)
		if (wc>0x10c5 && wc != 0x10c7 && wc != 0x10cd) return wc;
		else return wc + 0x2d00 - 0x10a0;
	if (!lower && (unsigned)wc - 0x2d00 < 0x26)
		if (wc>0x2d25 && wc != 0x2d27 && wc != 0x2d2d) return wc;
		else return wc + 0x10a0 - 0x2d00;
	for (i=0; casemaps[i].len; i++) {
		int base = casemaps[i].upper + (lmask & casemaps[i].lower);
		if ((unsigned)wc-base < casemaps[i].len) {
			if (casemaps[i].lower == 1)
				return wc + lower - ((wc-casemaps[i].upper)&1);
			return wc + lmul*casemaps[i].lower;
		}
	}
	for (i=0; pairs[i][1-lower]; i++) {
		if (pairs[i][1-lower] == wc)
			return pairs[i][lower];
	}
	if ((unsigned)wc - (0x10428 - 0x28*lower) < 0x28)
		return wc - 0x28 + 0x50*lower;
	return wc;
}