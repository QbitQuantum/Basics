STATIC char *
S_scan_word(pTHX_ register char *s, char *dest, STRLEN destlen, int allow_package, STRLEN *slp)
{
    register char *d = dest;
    register char * const e = d + destlen - 3;  /* two-character token, ending NUL */
    for (;;) {
	if (d >= e)
	    Perl_croak(aTHX_ ident_too_long);
	if (isALNUM(*s))	/* UTF handled below */
	    *d++ = *s++;
	else if (*s == '\'' && allow_package && isIDFIRST_lazy_if(s+1,UTF)) {
	    *d++ = ':';
	    *d++ = ':';
	    s++;
	}
	else if (*s == ':' && s[1] == ':' && allow_package && s[2] != '$') {
	    *d++ = *s++;
	    *d++ = *s++;
	}
	else if (UTF && UTF8_IS_START(*s) && isALNUM_utf8((U8*)s)) {
	    char *t = s + UTF8SKIP(s);
	    while (UTF8_IS_CONTINUED(*t) && _is_utf8_mark((U8*)t))
		t += UTF8SKIP(t);
	    if (d + (t - s) > e)
		Perl_croak(aTHX_ ident_too_long);
	    Copy(s, d, t - s, char);
	    d += t - s;
	    s = t;
	}
	else {