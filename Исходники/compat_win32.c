FILE *aa_fopen(const char *name, const char *mode)
{
    wchar_t *wname, *wmode;
    FILE *fp;

    if (strcmp(name, "-") == 0) {
        fp = (mode[0] == 'r') ? stdin : stdout;
        _setmode(_fileno(fp), _O_BINARY);
    } else {
        int share = _SH_DENYRW;
        if (strchr(mode, 'r') && !strchr(mode, '+'))
            share = _SH_DENYWR;
        codepage_decode_wchar(CP_UTF8, name, &wname);
        codepage_decode_wchar(CP_UTF8, mode, &wmode);
        fp = _wfsopen(wname, wmode, share);
        free(wname);
        free(wmode);
    }
    return fp;
}