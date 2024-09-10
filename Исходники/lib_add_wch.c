wecho_wchar(WINDOW *win, const cchar_t * wch)
{
    PUTC_DATA;
    int n;
    int code = ERR;

    TR(TRACE_VIRTPUT | TRACE_CCALLS, (T_CALLED("wecho_wchar(%p, %s)"), win,
				      _tracech_t(wch)));

    if (win != 0) {
	PUTC_INIT;
	while (PUTC_i < CCHARW_MAX) {
	    if ((PUTC_ch = wch->chars[PUTC_i++]) == L'\0')
		break;
	    if ((PUTC_n = wcrtomb(PUTC_buf, PUTC_ch, &PUT_st)) <= 0) {
		code = ERR;
		if (is8bits(PUTC_ch))
		    code = waddch(win, UChar(PUTC_ch) | wch->attr);
		break;
	    }
	    for (n = 0; n < PUTC_n; n++) {
		if ((code = waddch(win, UChar(PUTC_buf[n]) | wch->attr)) == ERR) {
		    break;
		}
	    }
	    if (code == ERR)
		break;
	}
	wrefresh(win);
    }

    TR(TRACE_VIRTPUT | TRACE_CCALLS, (T_RETURN("%d"), code));
    return (code);
}