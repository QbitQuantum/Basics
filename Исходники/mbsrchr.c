extern "C" _CONST_RETURN unsigned char * __cdecl _mbsrchr_l(
        const unsigned char *str,
        unsigned int c,
        _locale_t plocinfo
        )
{
        char *r = NULL;
        unsigned int cc;
        _LocaleUpdate _loc_update(plocinfo);

        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return (_CONST_RETURN unsigned char *)strrchr((const char *)str, c);

        /* validation section */
        _VALIDATE_RETURN(str != NULL, EINVAL, 0);

        do {
            cc = *str;
            if ( _ismbblead_l(cc, _loc_update.GetLocaleT()) ) {
                if(*++str) {
                    if (c == ((cc<<8)|*str))
                        r = (char *)str - 1;
                }
                else if(!r)
                    /* return pointer to '\0' */
                    r = (char *)str;
            }
            else if (c == cc)
                r = (char *)str;
        }
        while (*str++);

        return((_CONST_RETURN unsigned char *)r);
}