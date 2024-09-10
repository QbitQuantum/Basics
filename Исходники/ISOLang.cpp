bool ISOLang::IsISO639Language(LPCSTR code)
{
    size_t nLen = strlen(code) + 1;
    LPSTR tmp = DEBUG_NEW CHAR[nLen];
    strncpy_s(tmp, nLen, code, nLen);
    _strlwr_s(tmp, nLen);
    tmp[0] = (CHAR)toupper(tmp[0]);

    bool bFound = false;
    for (size_t i = 0, cnt = _countof(s_isolangs); i < cnt; i++) {
        if (!strcmp(s_isolangs[i].name, tmp)) {
            bFound = true;
            break;
        }
    }

    delete[] tmp;

    return bFound;
}