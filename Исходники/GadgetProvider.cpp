static char* _StrClone(const BSTR bstr)
{
    UINT blen = SysStringLen(bstr);
    UINT alen = SysStringByteLen(bstr);
    char* astr = new char[alen + 1];

    if (!astr)
        return 0;

    memset(astr, 0, alen + 1);
    WideCharToMultiByte(CP_ACP, 0, bstr, blen, astr, alen, NULL, NULL);

    return astr;
}