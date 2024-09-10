static wchar_t *itow (unsigned long int val) {
    static wchar_t buf[30];
    wchar_t *wcp = &buf[29];
    *wcp = L'\0';
    while (val != 0) {
        *--wcp = btowc ('0' + val % 10);
        val /= 10;
    }
    if (wcp == &buf[29])
        *--wcp = L'0';
    return wcp;
}