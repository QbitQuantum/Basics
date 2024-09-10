_tracecchar_t2(int bufnum, const cchar_t *ch)
{
    char *result = _nc_trace_buf(bufnum, BUFSIZ);
    attr_t attr;
    const char *found;

    if (result != 0) {
	strcpy(result, l_brace);
	if (ch != 0) {
	    attr = AttrOfD(ch);
	    if ((found = _nc_altcharset_name(attr, (chtype) CharOfD(ch))) != 0) {
		(void) _nc_trace_bufcat(bufnum, found);
		attr &= ~A_ALTCHARSET;
	    } else if (isWidecExt(CHDEREF(ch))) {
		(void) _nc_trace_bufcat(bufnum, "{NAC}");
		attr &= ~A_CHARTEXT;
	    } else {
		PUTC_DATA;
		int n;

		PUTC_INIT;
		(void) _nc_trace_bufcat(bufnum, "{ ");
		for (PUTC_i = 0; PUTC_i < CCHARW_MAX; ++PUTC_i) {
		    PUTC_ch = ch->chars[PUTC_i];
		    if (PUTC_ch == L'\0') {
			if (PUTC_i == 0)
			    result = _nc_trace_bufcat(bufnum, "\\000");
			break;
		    }
		    PUTC_n = wcrtomb(PUTC_buf, ch->chars[PUTC_i], &PUT_st);
		    if (PUTC_n <= 0) {
			if (PUTC_ch != L'\0') {
			    /* it could not be a multibyte sequence */
			    (void) _nc_trace_bufcat(bufnum,
						    _nc_tracechar(CURRENT_SCREEN,
								  UChar(ch->chars[PUTC_i])));
			}
			break;
		    }
		    for (n = 0; n < PUTC_n; n++) {
			if (n)
			    (void) _nc_trace_bufcat(bufnum, ", ");
			(void) _nc_trace_bufcat(bufnum,
						_nc_tracechar(CURRENT_SCREEN,
							      UChar(PUTC_buf[n])));
		    }
		}
		(void) _nc_trace_bufcat(bufnum, " }");
	    }
	    if (attr != A_NORMAL) {
		(void) _nc_trace_bufcat(bufnum, " | ");
		(void) _nc_trace_bufcat(bufnum, _traceattr2(bufnum + 20, attr));
	    }
	}

	result = _nc_trace_bufcat(bufnum, r_brace);
    }
    return result;
}