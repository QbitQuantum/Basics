unsigned int __cdecl _mbctoupper(
    unsigned int c
    )
{
	unsigned char val[2];
#if defined(_WIN32) && !defined(_POSIX_)
        unsigned char ret[4];
#endif /* _WIN32 */

	if (c > 0x00FF)
        {
            val[0] = (c >> 8) & 0xFF;
            val[1] = c & 0xFF;

            if (!_ismbblead(val[0]))
                return c;

#if defined( _WIN32 ) && !defined(_POSIX_)

            if (__crtLCMapStringA(  __mblcid,
                                    LCMAP_UPPERCASE,
                                    val,
                                    2,
                                    ret,
                                    2,
                                    __mbcodepage) == 0)
                return c;

            c = ret[1];
            c += ret[0] << 8;

            return c;

#else /* _WIN32 */

            if      (c >= _MBLOWERLOW1 && c <= _MBLOWERHIGH1)
                c -= _MBCASEDIFF1;

            else if (c >= _MBLOWERLOW2 && c <= _MBLOWERHIGH2)
                c -= _MBCASEDIFF2;

            return c;

#endif /* _WIN32 */

	} else