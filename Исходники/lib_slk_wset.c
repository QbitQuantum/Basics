slk_wset(int i, const wchar_t *astr, int format)
{
    int result = ERR;
    size_t arglen;
    const wchar_t *str;
    char *mystr;
    mbstate_t state;

    T((T_CALLED("slk_wset(%d, %s, %d)"), i, _nc_viswbuf(astr), format));

    init_mb(state);
    str = astr;
    if ((arglen = wcsrtombs(NULL, &str, 0, &state)) != (size_t) -1) {
	if ((mystr = (char *) _nc_doalloc(0, arglen + 1)) != 0) {
	    str = astr;
	    if (wcsrtombs(mystr, &str, arglen, &state) != (size_t) -1) {
		/* glibc documentation claims that the terminating L'\0'
		 * is written, but it is not...
		 */
		mystr[arglen] = 0;
		result = slk_set(i, mystr, format);
	    }
	    free(mystr);
	}
    }
    returnCode(result);
}