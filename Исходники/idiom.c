int is_number(wchar_t *s) {
    /* return TRUE if the string s is a sequence of digits. */
    while(*s != L'\0') {
	if (!iswdigit((wint_t)*s)) return FALSE;
	s++;
    }
    return TRUE;
}