static
FRESULT create_name (
	DIR *dj,			/* Pointer to the directory object */
	const char **path	/* Pointer to pointer to the segment in the path string */
)
{
	BYTE c, d, ni, si, i, *sfn;
	const char *p;

	/* Create file name in directory form */
	sfn = dj->fn;
	mem_set(sfn, ' ', 11);
	si = i = 0; ni = 8;
	p = *path;
	for (;;) {
		c = p[si++];
		if (c <= ' ' || c == '/') break;	/* Break on end of segment */
		if (c == '.' || i >= ni) {
			if (ni != 8 || c != '.') break;
			i = 8; ni = 11;
			continue;
		}
#ifdef _EXCVT
		if (c >= 0x80)					/* To upper extended char (SBCS) */
			c = cvt[c - 0x80];
#endif
		if (IsDBCS1(c) && i < ni - 1) {	/* DBC 1st byte? */
			d = p[si++];				/* Get 2nd byte */
			sfn[i++] = c;
			sfn[i++] = d;
		} else {						/* Single byte code */
			if (IsLower(c)) c -= 0x20;	/* toupper */
			sfn[i++] = c;
		}
	}
	*path = &p[si];						/* Rerurn pointer to the next segment */

	sfn[11] = (c <= ' ') ? 1 : 0;		/* Set last segment flag if end of path */

	return FR_OK;
}