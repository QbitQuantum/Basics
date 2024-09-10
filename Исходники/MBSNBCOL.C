int __cdecl _mbsnbcoll(
    const unsigned char *s1,
    const unsigned char *s2,
    size_t n
    )
{
#if !defined (_WIN32)
        return _mbsnbcmp(s1, s2, n);
#else  /* !defined (_WIN32) */
        int ret;

        if (n == 0)
            return 0;

        if (0 == (ret = __crtCompareStringA(__mblcid, 0,
                s1, n, s2, n, __mbcodepage)))
            return _NLSCMPERROR;

        return ret - 2;

#endif  /* !defined (_WIN32) */
}