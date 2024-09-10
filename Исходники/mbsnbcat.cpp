extern "C" unsigned char * __cdecl _mbsnbcat_l(
        unsigned char *dst,
        const unsigned char *src,
        size_t cnt,
        _locale_t plocinfo
        )
{
        unsigned char *start;

        if (!cnt)
                return(dst);

        /* validation section */
        _VALIDATE_RETURN(dst != nullptr, EINVAL, nullptr);
        _VALIDATE_RETURN(src != nullptr, EINVAL, nullptr);

        _LocaleUpdate _loc_update(plocinfo);

        _BEGIN_SECURE_CRT_DEPRECATION_DISABLE
        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return (unsigned char *)strncat((char *)dst, (const char *)src, cnt);
        _END_SECURE_CRT_DEPRECATION_DISABLE

        start = dst;
        while (*dst++)
                ;
        --dst;          // dst now points to end of dst string

        /* if last char in string is a lead byte, back up pointer */
        if ( dst!=start && _mbsbtype_l(start, (int) ((dst - start) - 1), _loc_update.GetLocaleT()) == _MBC_LEAD )
        {
            --dst;
        }

        /* copy over the characters */

        while (cnt--) {

            if ( _ismbblead_l(*src, _loc_update.GetLocaleT()) ) {
                *dst++ = *src++;
                if (cnt == 0) {   /* write null if cnt exhausted */
                    dst[-1] = '\0';
                    break;
                }
                cnt--;
                if ((*dst++ = *src++)=='\0') { /* or if no trail byte */
                    dst[-2] = '\0';
                    break;
                }
            }
            else if ((*dst++ = *src++) == '\0')
                break;

        }

        if ( dst!=start && _mbsbtype_l(start, (int) ((dst - start) - 1), _loc_update.GetLocaleT()) == _MBC_LEAD )
        {
            dst[-1] = '\0';
        }
        else
        {
            *dst = '\0';
        }

        return(start);
}