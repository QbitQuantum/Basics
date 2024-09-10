mod_export ZLE_INT_T
getrestchar(int inchar)
{
    char c = inchar;
    wchar_t outchar;
    int timeout;
    static mbstate_t mbs;

    /*
     * We are guaranteed to set a valid wide last character,
     * although it may be WEOF (which is technically not
     * a wide character at all...)
     */
    lastchar_wide_valid = 1;

    if (inchar == EOF) {
	/* End of input, so reset the shift state. */
	memset(&mbs, 0, sizeof mbs);
	return lastchar_wide = WEOF;
    }

    /*
     * Return may be zero if we have a NULL; handle this like
     * any other character.
     */
    while (1) {
	size_t cnt = mbrtowc(&outchar, &c, 1, &mbs);
	if (cnt == MB_INVALID) {
	    /*
	     * Invalid input.  Hmm, what's the right thing to do here?
	     */
	    memset(&mbs, 0, sizeof mbs);
	    return lastchar_wide = WEOF;
	}
	if (cnt != MB_INCOMPLETE)
	    break;

	/*
	 * Always apply KEYTIMEOUT to the remains of the input
	 * character.  The parts of a multibyte character should
	 * arrive together.  If we don't do this the input can
	 * get stuck if an invalid byte sequence arrives.
	 */
	inchar = getbyte(1L, &timeout);
	/* getbyte deliberately resets lastchar_wide_valid */
	lastchar_wide_valid = 1;
	if (inchar == EOF) {
	    memset(&mbs, 0, sizeof mbs);
	    if (timeout)
	    {
		/*
		 * This case means that we got a valid initial byte
		 * (since we tested for EOF above), but the followup
		 * timed out.  This probably indicates a duff character.
		 * Return a '?'.
		 */
		lastchar = '?';
		return lastchar_wide = L'?';
	    }
	    else
		return lastchar_wide = WEOF;
	}
	c = inchar;
    }
    return lastchar_wide = (ZLE_INT_T)outchar;
}