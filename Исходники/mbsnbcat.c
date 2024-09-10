unsigned char * __cdecl _mbsnbcat(
    unsigned char *dst,
    const unsigned char *src,
    size_t cnt
    )
{
	unsigned char *start;

	if (!cnt)
		return(dst);

        if (0 == __mbcodepage)
            return strncat(dst, src, cnt);

        _mlock(_MB_CP_LOCK);

	start = dst;
	while (*dst++)
                ;
	--dst;		// dst now points to end of dst string


	/* if last char in string is a lead byte, back up pointer */

        if (_MBSBTYPE(start, (int) ((dst - start) - 1)) == _MBC_LEAD)
		--dst;

	/* copy over the characters */

	while (cnt--) {

		if (_ISLEADBYTE(*src)) {
			*dst++ = *src++;
			if (!cnt--) {	/* write nul if cnt exhausted */
				dst[-1] = '\0';
				break;
			}
			if ((*dst++ = *src++)=='\0') { /* or if no trail byte */
				dst[-2] = '\0';
                                break;
                        }
                }

		else if ((*dst++ = *src++) == '\0')
                        break;

        }

	/* enter final nul, if necessary */

	if (_MBSBTYPE(start, (int) ((dst - start) - 1)) == _MBC_LEAD)
	    dst[-1] = '\0';
	else
	    *dst = '\0';


        _munlock(_MB_CP_LOCK);
	return(start);
}