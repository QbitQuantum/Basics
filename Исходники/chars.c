/* c is a multibyte control character.  It displays as ^@, ^?, or ^[ch],
 * where ch is (c + 64).  We return that multibyte character.  If crep
 * is an invalid multibyte sequence, it will be replaced with Unicode
 * 0xFFFD (Replacement Character). */
char *control_mbrep(const char *c, char *crep, int *crep_len)
{
    assert(c != NULL && crep != NULL && crep_len != NULL);

#ifdef ENABLE_UTF8
    if (use_utf8) {
	wchar_t wc;

	if (mbtowc(&wc, c, MB_CUR_MAX) < 0) {
	    mbtowc_reset();
	    *crep_len = bad_mbchar_len;
	    strncpy(crep, bad_mbchar, *crep_len);
	} else {
	    *crep_len = wctomb(crep, control_wrep(wc));

	    if (*crep_len < 0) {
		wctomb_reset();
		*crep_len = 0;
	    }
	}
    } else {
#endif
	*crep_len = 1;
	*crep = control_rep(*c);
#ifdef ENABLE_UTF8
    }
#endif

    return crep;
}