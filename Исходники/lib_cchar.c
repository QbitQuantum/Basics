getcchar(const cchar_t *wcval,
	 wchar_t *wch,
	 attr_t *attrs,
	 short *color_pair,
	 void *opts)
{
    wchar_t *wp;
    int len;
    int code = ERR;

    TR(TRACE_CCALLS, (T_CALLED("getcchar(%p,%p,%p,%p,%p)"),
		      (const void *) wcval,
		      (void *) wch,
		      (void *) attrs,
		      (void *) color_pair,
		      opts));

    if (opts == NULL) {
	len = ((wp = wmemchr(wcval->chars, L'\0', CCHARW_MAX))
	       ? (int) (wp - wcval->chars)
	       : CCHARW_MAX);

	if (wch == NULL) {
	    /*
	     * If the value is a null, set the length to 1.
	     * If the value is not a null, return the length plus 1 for null.
	     */
	    code = (len < CCHARW_MAX) ? (len + 1) : CCHARW_MAX;
	} else if (attrs == 0 || color_pair == 0) {
	    code = ERR;
	} else if (len >= 0) {
	    *attrs = AttrOf(*wcval) & A_ATTRIBUTES;
	    *color_pair = (short) GetPair(*wcval);
	    wmemcpy(wch, wcval->chars, (unsigned) len);
	    wch[len] = L'\0';
	    code = OK;
	}
    }

    TR(TRACE_CCALLS, (T_RETURN("%d"), code));
    return (code);
}