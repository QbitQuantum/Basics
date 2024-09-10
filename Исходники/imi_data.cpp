void
print_wide(const TWCHAR* wstr)
{
    char buf[512];

#ifdef HAVE_ICONV_H
    iconv_t icv = iconv_open("UTF-8", TWCHAR_ICONV_NAME);
    TIConvSrcPtr src = (TIConvSrcPtr)wstr;
    size_t srclen = (WCSLEN(wstr)+1)*sizeof(TWCHAR);
    char *dst = buf;
    size_t dstlen = 1024;
    iconv(icv, &src, &srclen, &dst, &dstlen);
    iconv_close(icv);
#else // !HAVE_ICONV_H
    memset(&buf[0], 0, sizeof(buf));
    WCSTOMBS(&buf[0], wstr, sizeof(buf) - 1);
#endif // HAVE_ICONV_H

    printf("%s", buf);
}