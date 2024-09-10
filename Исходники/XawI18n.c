int
_Xaw_iswalnum(wchar_t ch)
{
#ifdef HAVE_ISWALNUM
    return iswalnum(ch);
#else
    unsigned char mb[MB_LEN_MAX];

    wctomb((char*)mb, ch);

    return (isalnum(*mb));
#endif
}