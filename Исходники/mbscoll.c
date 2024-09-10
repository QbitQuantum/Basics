extern "C" int __cdecl _mbscoll_l(
        const unsigned char *s1,
        const unsigned char *s2,
        _locale_t plocinfo
        )
{
        int ret;
        _LocaleUpdate _loc_update(plocinfo);

        /* validation section */
        _VALIDATE_RETURN(s1 != NULL, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(s2 != NULL, EINVAL, _NLSCMPERROR);

        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return _strcoll_l((const char *)s1, (const char *)s2, plocinfo);

        if (0 == (ret = __crtCompareStringA(
                        _loc_update.GetLocaleT(),
                        _loc_update.GetLocaleT()->mbcinfo->mblcid,
                        SORT_STRINGSORT,
                        (LPCSTR)s1,
                        -1,
                        (LPSTR)s2,
                        -1,
                        _loc_update.GetLocaleT()->mbcinfo->mbcodepage )))
        {
            errno = EINVAL;

            return _NLSCMPERROR;
        }

        return ret - 2;

}