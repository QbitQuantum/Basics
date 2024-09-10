unsigned char * __cdecl _mbsnbcpy_l(
        unsigned char *dst,
        const unsigned char *src,
        size_t cnt,
        _locale_t plocinfo
        )
{

        unsigned char *start = dst;
        _LocaleUpdate _loc_update(plocinfo);

        /* validation section */
        _VALIDATE_RETURN(dst != NULL || cnt == 0, EINVAL, NULL);
        _VALIDATE_RETURN(src != NULL || cnt == 0, EINVAL, NULL);

        _BEGIN_SECURE_CRT_DEPRECATION_DISABLE
        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return (unsigned char *)strncpy((char *)dst, (const char *)src, cnt);
        _END_SECURE_CRT_DEPRECATION_DISABLE

        while (cnt) {

            cnt--;
            if ( _ismbblead_l(*src, _loc_update.GetLocaleT()) ) {
                *dst++ = *src++;
                if (!cnt) {
                    dst[-1] = '\0';
                    break;
                }
                cnt--;
                if ((*dst++ = *src++) == '\0') {
                    dst[-2] = '\0';
                    break;
                }
            }

            else
                if ((*dst++ = *src++) == '\0')
                    break;

        }

        /* pad with nulls as needed */

        while (cnt--)
            *dst++ = '\0';

        return start;
}