extern "C" size_t __cdecl _mbslen_l(
        const unsigned char *s,
        _locale_t plocinfo
        )
{
        int n;
        _LocaleUpdate _loc_update(plocinfo);

        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return strlen((const char *)s);

        for (n = 0; *s; n++, s++) {
            if ( _ismbblead_l(*s, _loc_update.GetLocaleT()) ) {
                if (*++s == '\0')
                    break;
            }
        }

        return(n);
}