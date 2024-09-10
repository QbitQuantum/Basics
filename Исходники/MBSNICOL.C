int __cdecl _mbsnicoll(
    const unsigned char *s1,
    const unsigned char *s2,
    size_t n
    )
{
#if !defined (_WIN32)
        return _mbsnicmp(s1, s2, n);
#else  /* !defined (_WIN32) */
        int ret;
        size_t bcnt1, bcnt2;

        if (n == 0)
            return 0;

        bcnt1 = _mbsnbcnt(s1, n);
        bcnt2 = _mbsnbcnt(s2, n);

        if (0 == (ret = __crtCompareStringA(__mblcid, NORM_IGNORECASE,
                s1, bcnt1, s2, bcnt2, __mbcodepage)))
            return _NLSCMPERROR;

        return ret - 2;

#endif  /* !defined (_WIN32) */
}