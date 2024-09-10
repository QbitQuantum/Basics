int __cdecl _mbsnbicmp_l(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n,
        _locale_t plocinfo
        )
{
        unsigned short c1, c2;
        _LocaleUpdate _loc_update(plocinfo);

        if (n==0)
            return(0);

        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return _strnicmp((const char *)s1, (const char *)s2, n);

        /* validation section */
        _VALIDATE_RETURN(s1 != nullptr, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(s2 != nullptr, EINVAL, _NLSCMPERROR);

        while (n--) {

            c1 = *s1++;
            if ( _ismbblead_l(c1, _loc_update.GetLocaleT()) )
            {
                if (n==0)
                {
                    c1 = 0; /* 'naked' lead - end of string */
                    c2 = _ismbblead_l(*s2, _loc_update.GetLocaleT()) ? 0 : *s2;
                    goto test;
                }
                if (*s1 == '\0')
                    c1 = 0;
                else {
                    c1 = ((c1<<8) | *s1++);

                    if ( ((c1 >= _MBUPPERLOW1_MT(_loc_update.GetLocaleT())) &&
                          (c1 <= _MBUPPERHIGH1_MT(_loc_update.GetLocaleT()))) )
                        c1 += _MBCASEDIFF1_MT(_loc_update.GetLocaleT());
                    else if ( ((c1 >= _MBUPPERLOW2_MT(_loc_update.GetLocaleT())) &&
                               (c1 <= _MBUPPERHIGH2_MT(_loc_update.GetLocaleT()))) )
                        c1 += _MBCASEDIFF2_MT(_loc_update.GetLocaleT());
                }
            }
            else
                c1 = _mbbtolower_l(c1, _loc_update.GetLocaleT());

                c2 = *s2++;
                if ( _ismbblead_l(c2, _loc_update.GetLocaleT()) )
                {
                    if (n==0)
                    {
                        c2 = 0; /* 'naked' lead - end of string */
                        goto test;
                    }
                    n--;
                    if (*s2 == '\0')
                        c2 = 0;
                    else {
                        c2 = ((c2<<8) | *s2++);

                        if ( ((c2 >= _MBUPPERLOW1_MT(_loc_update.GetLocaleT())) &&
                              (c2 <= _MBUPPERHIGH1_MT(_loc_update.GetLocaleT()))) )
                            c2 += _MBCASEDIFF1_MT(_loc_update.GetLocaleT());
                        else if ( ((c2 >= _MBUPPERLOW2_MT(_loc_update.GetLocaleT())) &&
                                   (c2 <= _MBUPPERHIGH2_MT(_loc_update.GetLocaleT()))) )
                            c2 += _MBCASEDIFF2_MT(_loc_update.GetLocaleT());
                    }
                }
                else
                    c2 = _mbbtolower_l(c2, _loc_update.GetLocaleT());

test:
            if (c1 != c2)
                return( (c1 > c2) ? 1 : -1);

            if (c1 == 0)
                return(0);
        }

        return(0);
}