static int
really_getch(WINDOW *win, int *fkey)
{
    int ch;
#ifdef USE_WIDE_CURSES
    int code;
    mbstate_t state;
    wchar_t my_wchar;
    wint_t my_wint;

    /*
     * We get a wide character, translate it to multibyte form to avoid
     * having to change the rest of the code to use wide-characters.
     */
    if (used_last_getc >= have_last_getc) {
	used_last_getc = 0;
	have_last_getc = 0;
	ch = ERR;
	*fkey = 0;
	code = wget_wch(win, &my_wint);
	my_wchar = (wchar_t) my_wint;
	switch (code) {
	case KEY_CODE_YES:
	    ch = *fkey = my_wchar;
	    last_getc = my_wchar;
	    break;
	case OK:
	    memset(&state, 0, sizeof(state));
	    have_last_getc = (int) wcrtomb(last_getc_bytes, my_wchar, &state);
	    if (have_last_getc < 0) {
		have_last_getc = used_last_getc = 0;
		last_getc_bytes[0] = (char) my_wchar;
	    }
	    ch = (int) CharOf(last_getc_bytes[used_last_getc++]);
	    last_getc = my_wchar;
	    break;
	case ERR:
	    ch = ERR;
	    last_getc = ERR;
	    break;
	default:
	    break;
	}
    } else {
	ch = (int) CharOf(last_getc_bytes[used_last_getc++]);
    }
#else
    ch = wgetch(win);
    last_getc = ch;
    *fkey = (ch > KEY_MIN && ch < KEY_MAX);
#endif
    return ch;
}