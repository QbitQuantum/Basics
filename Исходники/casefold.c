char   *casefoldx(int flags, VSTRING *dest, const char *src, ssize_t len)
{
    size_t  old_len;

#ifdef NO_EAI

    /*
     * ASCII mode only.
     */
    if (len < 0)
	len = strlen(src);
    if ((flags & CASEF_FLAG_APPEND) == 0)
	VSTRING_RESET(dest);
    old_len = VSTRING_LEN(dest);
    vstring_strncat(dest, src, len);
    lowercase(STR(dest) + old_len);
    return (STR(dest));
#else

    /*
     * Unicode mode.
     */
    const char myname[] = "casefold";
    static VSTRING *fold_buf = 0;
    static UCaseMap *csm = 0;
    UErrorCode error;
    ssize_t space_needed;
    int     n;

    /*
     * Handle special cases.
     */
    if (len < 0)
	len = strlen(src);
    if (dest == 0)
	dest = (fold_buf != 0 ? fold_buf : (fold_buf = vstring_alloc(100)));
    if ((flags & CASEF_FLAG_APPEND) == 0)
	VSTRING_RESET(dest);
    old_len = VSTRING_LEN(dest);

    /*
     * All-ASCII input, or ASCII mode only.
     */
    if ((flags & CASEF_FLAG_UTF8) == 0 || allascii(src)) {
	vstring_strncat(dest, src, len);
	lowercase(STR(dest) + old_len);
	return (STR(dest));
    }

    /*
     * ICU 4.8 ucasemap_utf8FoldCase() does not complain about UTF-8 syntax
     * errors. XXX Based on source-code review we conclude that non-UTF-8
     * bytes are copied verbatim, and experiments confirm this. Given that
     * this behavior is intentional, we assume that it will stay that way.
     */
#if 0
    if (valid_utf8_string(src, len) == 0) {
	if (err)
	    *err = "malformed UTF-8 or invalid codepoint";
	return (0);
    }
#endif

    /*
     * One-time initialization. With ICU 4.8 this works while chrooted.
     */
    if (csm == 0) {
	error = U_ZERO_ERROR;
	csm = ucasemap_open("en_US", U_FOLD_CASE_DEFAULT, &error);
	if (U_SUCCESS(error) == 0)
	    msg_fatal("ucasemap_open error: %s", u_errorName(error));
    }

    /*
     * Fold the input, adjusting the buffer size if needed. Safety: don't
     * loop forever.
     * 
     * Note: the requested amount of space for casemapped output (as reported
     * with space_needed below) does not include storage for the null
     * terminator. The terminator is written only when the output buffer is
     * large enough. This is why we overallocate space when the output does
     * not fit. But if the output fits exactly, then the ouput will be
     * unterminated, and we have to terminate the output ourselves.
     */
    for (n = 0; n < 3; n++) {
	error = U_ZERO_ERROR;
	space_needed = ucasemap_utf8FoldCase(csm, STR(dest) + old_len,
				     vstring_avail(dest), src, len, &error);
	if (U_SUCCESS(error)) {
	    VSTRING_AT_OFFSET(dest, old_len + space_needed);
	    if (vstring_avail(dest) == 0)	/* exact fit, no terminator */
		VSTRING_TERMINATE(dest);	/* add terminator */
	    break;
	} else if (error == U_BUFFER_OVERFLOW_ERROR) {
	    VSTRING_SPACE(dest, space_needed + 1);	/* for terminator */
	} else {
	    msg_fatal("%s: conversion error for \"%s\": %s",
		      myname, src, u_errorName(error));
	}
    }
    return (STR(dest));
#endif						/* NO_EAI */
}