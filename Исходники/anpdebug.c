void tcscat_s(tchar_t *Out, size_t OutLen, const tchar_t *In)
{
    if (OutLen > 0)
    {
        size_t n = tcslen(Out);
        tcscpy_s(Out + n, OutLen - n, In);
    }
}