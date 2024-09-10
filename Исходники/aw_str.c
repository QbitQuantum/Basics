BOOL __cdecl __crtGetStringTypeA(
    DWORD    dwInfoType,
    LPCSTR   lpSrcStr,
    int      cchSrc,
    LPWORD   lpCharType,
    int      code_page,
    int      lcid
    )
{
    static int f_use = 0;

    /* 
     * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
     * Must actually call the function to ensure it's not a stub.
     */
    
    if (0 == f_use)
    {
        unsigned short dummy;

    	if (0 != GetStringTypeA(0, CT_CTYPE1, "\0", 1, &dummy))
            f_use = USE_A;

    	else if (0 != GetStringTypeW(CT_CTYPE1, L"\0", 1, &dummy))
            f_use = USE_W;

        else
            return FALSE;
    }

    /* Use "A" version */

    if (USE_A == f_use)
    {
        if (0 == lcid)
            lcid = __lc_handle[LC_CTYPE];

        return GetStringTypeA(lcid, dwInfoType, lpSrcStr, cchSrc, lpCharType);
    }

    /* Use "W" version */

    if (USE_W == f_use)
    {
        int retval;
        int buff_size;
        BOOL retbool = FALSE;
        wchar_t *wbuffer = NULL;

        /*
         * Convert string and return the requested information. Note that 
         * we are converting to a wide character string so there is not a 
         * one-to-one correspondence between number of multibyte chars in the 
         * input string and the number of wide chars in the buffer. However, 
         * there had *better be* a one-to-one correspondence between the 
         * number of multibyte characters and the number of WORDs in the
         * return buffer.
         */
         
        /*
         * Use __lc_codepage for conversion if code_page not specified
         */

        if (0 == code_page)
            code_page = __lc_codepage;

        /* find out how big a buffer we need */
        if (0 == (buff_size = MultiByteToWideChar(code_page, 
            MB_PRECOMPOSED|MB_ERR_INVALID_CHARS, lpSrcStr, cchSrc, NULL, 0)))
            goto done;

        /* allocate enough space for wide chars */
        if (NULL == (wbuffer = (wchar_t *)_calloc_crt(sizeof(wchar_t), buff_size)))
            goto done;

        /* do the conversion */
        if (0 == (retval = MultiByteToWideChar(code_page, 
            MB_PRECOMPOSED, lpSrcStr, cchSrc, wbuffer, buff_size)))
            goto done;

        /* obtain result */
        retbool = GetStringTypeW(dwInfoType, wbuffer, retval, lpCharType);

done:
        _free_crt(wbuffer);
        return retbool;
    }
}