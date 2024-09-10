// The wctype table is 144 KB, too much for poor freeldr
int iswctype(wint_t wc, wctype_t wctypeFlags)
{
    return _isctype((char)wc, wctypeFlags);
}