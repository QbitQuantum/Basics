bool make_invalid_wchar(wchar_t &w) {
    std::setlocale(LC_ALL,"C");
    w=(wchar_t)WEOF;

    std::mbstate_t ps=std::mbstate_t();
    char s[MB_LEN_MAX];
    size_t r=wcrtomb(s,w,&ps);
    return r==(size_t)-1;
}