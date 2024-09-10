/*
 * This function is careful to do line breaks based on wchar_t's, not
 * bytes, so multi-byte characters are traced properly.
 * However, it doesn't know that DBCS characters are two columns wide, so it
 * will get those wrong and break too late.  To get that right, it needs some
 * sort of function to tell it that a wchar_t is double-width, which we lack at
 * the moment.
 *
 * If wchar_t's are Unicode, it could perhaps use some sort of heuristic based
 * on which plane the character is in.
 */
static void
trace_ds_s(char *s, Boolean can_break)
{
    	int len = strlen(s);
	int len0 = len + 1;
	int wlen;
	Boolean nl = False;
	wchar_t *w_buf;		/* wchar_t translation of s */
	wchar_t *w_cur;		/* current wchar_t pointer */
	wchar_t *w_chunk;	/* transient wchar_t buffer */
	char *mb_chunk;		/* transient multibyte buffer */

	if (!toggled(TRACING) || tracef == NULL || !len)
		return;

	/* Allocate buffers for chunks of output data. */
	mb_chunk = Malloc(len0);
	w_chunk = (wchar_t *)Malloc(len0 * sizeof(wchar_t));

	/* Convert the input string to wchar_t's. */
	w_buf = (wchar_t *)Malloc(len0 * sizeof(wchar_t));
	wlen = mbstowcs(w_buf, s, len);
	if (wlen < 0)
	    Error("trace_ds_s: mbstowcs failed");
	w_cur = w_buf;

	/* Check for a trailing newline. */
	if (len && s[len-1] == '\n') {
		wlen--;
		nl = True;
	}

	if (!can_break && dscnt + wlen >= 75) {
		wtrace("...\n... ");
		dscnt = 0;
	}

	while (dscnt + wlen >= 75) {
		int plen = 75-dscnt;
		int mblen;

		if (plen) {
		    memcpy(w_chunk, w_cur, plen * sizeof(wchar_t));
		    w_chunk[plen] = 0;
		    mblen = wcstombs(mb_chunk, w_chunk, len0);
		    if (mblen <= 0)
			Error("trace_ds_s: wcstombs 1 failed");
		} else {
		    mb_chunk[0] = '\0';
		    mblen = 0;
		}

		wtrace("%.*s ...\n... ", mblen, mb_chunk);
		dscnt = 4;
		w_cur += plen;
		wlen -= plen;
	}
	if (wlen) {
		int mblen;

		memcpy(w_chunk, w_cur, wlen * sizeof(wchar_t));
		w_chunk[wlen] = 0;
		mblen = wcstombs(mb_chunk, w_chunk, len0);
		if (mblen <= 0)
		    Error("trace_ds_s: wcstombs 2 failed");
		wtrace("%.*s", mblen, mb_chunk);
		dscnt += wlen;
	}
	if (nl) {
		wtrace("\n");
		dscnt = 0;
	}
	Free(mb_chunk);
	Free(w_buf);
	Free(w_chunk);
}