extern "C" unsigned char* __cdecl _mbsrev_l(
    unsigned char* string,
    _locale_t plocinfo
) {
    unsigned char* start = string;
    unsigned char* left  = string;
    unsigned char c;
    _LocaleUpdate _loc_update(plocinfo);
    /* validation section */
    _VALIDATE_RETURN(string != NULL, EINVAL, NULL);

    if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0) {
        return (unsigned char*)_strrev((char*)string);
    }

    /* first go through and reverse the bytes in MBCS chars */
    while (*string) {
        if (_ismbblead_l(*string++, _loc_update.GetLocaleT())) {
            if (*string) {
                c = *string;
                *string = *(string - 1);
                *(string - 1) = c;
                string++;
            } else {
                /*  second byte is EOS
                    There is nothing really satisfying to do here. We have a string
                    that ends in leadbyte,'\0'. Reversing this would lead to the leadbyte
                    becoming falsely attached to the character before it:
                    (XL0 -> LX0, X has suddenly become a trailbyte)

                    So what we choose to do is assert and purge the dud byte from within the
                    string.
                */
                errno = EINVAL;
                _ASSERTE(("Bad MBCS string passed into _mbsrev", 0));
                /* String has at least moved once already, so this is safe */
                _ASSERTE(string > start);
                /* move back one to point at the dud leadbyte */
                --string;
                /* now truncate the string one byte earlier */
                *string = '\0';
                break;
            }
        }
    }

    /* now reverse the whole string */
    string--;

    while (left < string) {
        c = *left;
        *left++ = *string;
        *string-- = c;
    }

    return (start);
}