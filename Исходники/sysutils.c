static int Rwputenv(const wchar_t *nm, const wchar_t *val)
{
    wchar_t *buf;
    buf = (wchar_t *) malloc((wcslen(nm) + wcslen(val) + 2) * sizeof(wchar_t));
    if(!buf) return 1;
    /* previously wsprintfW, which had a limit of 1024 chars */
    wcscpy(buf, nm); wcscat(buf, L"="); wcscat(buf, val);
    if(_wputenv(buf)) return 1;
    /* no free here: storage remains in use */
    return 0;
}