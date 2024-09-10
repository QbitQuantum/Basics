_MRTIMP2 int __cdecl _Wcrtomb
        (
        char *s,
        wchar_t wchar,
        mbstate_t *pst,
        const _Cvtvec *ploc
        )
{
        LCID handle;
        UINT codepage;

        if (ploc == 0)
        {
            handle = ___lc_handle_func()[LC_CTYPE];
            codepage = ___lc_codepage_func();
        }
        else
        {
            handle = ploc->_Hand;
            codepage = ploc->_Page;
        }

        if ( handle == _CLOCALEHANDLE )
        {
            if ( wchar > 255 )  /* validate high byte */
            {
                errno = EILSEQ;
                return -1;
            }

            *s = (char) wchar;
            return sizeof(char);
        } else {
            int size;
            BOOL defused = 0;
            _locale_t locale = _GetLocaleForCP(codepage);

            if ( ((size = WideCharToMultiByte(codepage,
                                              0,
                                              &wchar,
                                              1,
                                              s,
                                              ___mb_cur_max_l_func(locale),
                                              NULL,
                                              &defused)) == 0) ||
                 (defused) )
            {
                errno = EILSEQ;
                return -1;
            }

            return size;
        }
}