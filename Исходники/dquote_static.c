STATIC char
S_grok_bslash_c(pTHX_ const char source, const bool utf8, const bool output_warning)
{

    U8 result;

    if (utf8) {
	/* Trying to deprecate non-ASCII usages.  This construct has never
	 * worked for a utf8 variant.  So, even though are accepting non-ASCII
	 * Latin1 in 5.14, no need to make them work under utf8 */
	if (! isASCII(source)) {
	    Perl_croak(aTHX_ "Character following \"\\c\" must be ASCII");
	}
    }

    result = toCTRL(source);
    if (! isASCII(source)) {
	    Perl_ck_warner_d(aTHX_ packWARN2(WARN_DEPRECATED, WARN_SYNTAX),
			    "Character following \"\\c\" must be ASCII");
    }
    else if (! isCNTRL(result) && output_warning) {
	if (source == '{') {
	    Perl_ck_warner_d(aTHX_ packWARN2(WARN_DEPRECATED, WARN_SYNTAX),
			    "\"\\c{\" is deprecated and is more clearly written as \";\"");
	}
	else {
	    U8 clearer[3];
	    U8 i = 0;
	    if (! isALNUM(result)) {
		clearer[i++] = '\\';
	    }
	    clearer[i++] = result;
	    clearer[i++] = '\0';

	    Perl_ck_warner(aTHX_ packWARN(WARN_SYNTAX),
			    "\"\\c%c\" is more clearly written simply as \"%s\"",
			    source,
			    clearer);
	}
    }

    return result;
}