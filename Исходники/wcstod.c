double
_wcstod_l (struct _reent *ptr, const wchar_t *nptr, wchar_t **endptr,
	   locale_t loc)
{
        static const mbstate_t initial;
        mbstate_t mbs;
        double val;
        char *buf, *end;
        const wchar_t *wcp;
        size_t len;

        while (iswspace_l(*nptr, loc))
                nptr++;

        /*
         * Convert the supplied numeric wide char. string to multibyte.
         *
         * We could attempt to find the end of the numeric portion of the
         * wide char. string to avoid converting unneeded characters but
         * choose not to bother; optimising the uncommon case where
         * the input string contains a lot of text after the number
         * duplicates a lot of strtod()'s functionality and slows down the
         * most common cases.
         */
        wcp = nptr;
        mbs = initial;
        if ((len = _wcsnrtombs_l(ptr, NULL, &wcp, (size_t) -1, 0, &mbs, loc))
	    == (size_t) -1) {
                if (endptr != NULL)
                        *endptr = (wchar_t *)nptr;
                return (0.0);
        }
        if ((buf = _malloc_r(ptr, len + 1)) == NULL)
                return (0.0);
        mbs = initial;
        _wcsnrtombs_l(ptr, buf, &wcp, (size_t) -1, len + 1, &mbs, loc);

        /* Let strtod() do most of the work for us. */
        val = _strtod_l(ptr, buf, &end, loc);

        /*
         * We only know where the number ended in the _multibyte_
         * representation of the string. If the caller wants to know
         * where it ended, count multibyte characters to find the
         * corresponding position in the wide char string.
         */
        if (endptr != NULL) {
		/* The only valid multibyte char in a float converted by
		   strtod/wcstod is the radix char.  What we do here is,
		   figure out if the radix char was in the valid leading
		   float sequence in the incoming string.  If so, the
		   multibyte float string is strlen(radix char) - 1 bytes
		   longer than the incoming wide char string has characters.
		   To fix endptr, reposition end as if the radix char was
		   just one byte long.  The resulting difference (end - buf)
		   is then equivalent to the number of valid wide characters
		   in the input string. */
		len = strlen (__localeconv_l (loc)->decimal_point);
		if (len > 1) {
			char *d = strstr (buf,
					  __localeconv_l (loc)->decimal_point);
			if (d && d < end)
				end -= len - 1;
		}
                *endptr = (wchar_t *)nptr + (end - buf);
	}

        _free_r(ptr, buf);

        return (val);
}