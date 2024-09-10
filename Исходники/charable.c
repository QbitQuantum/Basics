NCURSES_EXPORT(int) _nc_to_char(wint_t ch)
{
    int result;
#if HAVE_WCTOB
    result = wctob(ch);
#elif HAVE_WCTOMB
    char temp[MB_LEN_MAX];
    result = wctomb(temp, ch);
    if (strlen(temp) == 1)
	result = UChar(temp[0]);
    else
	result = -1;
#endif
    return result;
}