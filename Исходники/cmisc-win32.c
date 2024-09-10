char *
c_win32_getlocale(void)
{
    LCID lcid = GetThreadLocale();
    char buf[19];
    int ccBuf = GetLocaleInfo(lcid, LOCALE_SISO639LANGNAME, buf, 9);
    buf[ccBuf - 1] = '-';
    ccBuf += GetLocaleInfo(lcid, LOCALE_SISO3166CTRYNAME, buf + ccBuf, 9);
    return strdup(buf);
}