int
iswblank (wint_t wc)
{
    return iswctype(wc, wctype("blank"));
}