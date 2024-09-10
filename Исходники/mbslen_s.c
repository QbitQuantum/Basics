size_t __cdecl _mbsnlen_l(
        const unsigned char *s,
        size_t sizeInBytes,
        _locale_t plocinfo
        )
{
        size_t n, size;
        _LocaleUpdate _loc_update(plocinfo);

        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return strnlen((const char *)s, sizeInBytes);

        /* Note that we do not check if s == NULL, because we do not
         * return errno_t...
         */

        /* Note that sizeInBytes here is the number of bytes, not mb characters! */
        for (n = 0, size = 0; size < sizeInBytes && *s; n++, s++, size++)
        {
            if ( _ismbblead_l(*s, _loc_update.GetLocaleT()) )
                        {
                                size++;
                                if (size >= sizeInBytes)
                                {
                                        break;
                                }
                if (*++s == '\0')
                                {
                    break;
                                }
            }
        }

                return (size >= sizeInBytes ? sizeInBytes : n);
}