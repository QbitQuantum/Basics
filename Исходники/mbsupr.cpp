extern "C" errno_t __cdecl _mbsupr_s_l(
        unsigned char *string,
        size_t sizeInBytes,
        _locale_t plocinfo
        )
{
        size_t stringlen;

        /* validation section */
        _VALIDATE_RETURN_ERRCODE((string != nullptr && sizeInBytes > 0) || (string == nullptr && sizeInBytes == 0), EINVAL);

        if (string == nullptr)
        {
            /* nothing to do */
            return 0;
        }

        stringlen = strnlen((char *)string, sizeInBytes);
        if (stringlen >= sizeInBytes)
        {
            _RESET_STRING(string, sizeInBytes);
            _RETURN_DEST_NOT_NULL_TERMINATED(string, sizeInBytes);
        }
        _FILL_STRING(string, sizeInBytes, stringlen + 1);

        unsigned char *cp, *dst;
        _LocaleUpdate _loc_update(plocinfo);

        for (cp = string, dst = string; *cp; ++cp)
        {
            if ( _ismbblead_l(*cp, _loc_update.GetLocaleT()) )
            {


                int retval;
                unsigned char ret[4];

                if ( (retval = __acrt_LCMapStringA(
                                _loc_update.GetLocaleT(),
                                _loc_update.GetLocaleT()->mbcinfo->mblocalename,
                                LCMAP_UPPERCASE,
                                (const char *)cp,
                                2,
                                (char *)ret,
                                2,
                                _loc_update.GetLocaleT()->mbcinfo->mbcodepage,
                                TRUE )) == 0 )
                {
                    errno = EILSEQ;
                    _RESET_STRING(string, sizeInBytes);
                    return errno;
                }

                *(dst++) = ret[0];
                ++cp;
                if (retval > 1)
                {
                    *(dst++) = ret[1];
                }


            }
            else
                /* single byte, macro version */
                *(dst++) = (unsigned char) _mbbtoupper_l(*cp, _loc_update.GetLocaleT());
        }
        /* null terminate the string */
        *dst = '\0';

        return 0;
}