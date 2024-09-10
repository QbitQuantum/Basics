VOID StrToNameOrd(
    LPTSTR pszNameOrd,
    BOOL fDecOnly)
{
    register INT i;
    INT nOrd;
    INT nLen;

    /*
     * Empty string?
     */
    if (!(*pszNameOrd))
        return;

    nLen = lstrlen(pszNameOrd);

    /*
     * Is a hex value ok and does this appear to be a hex value?
     */
    if (!fDecOnly && pszNameOrd[0] == CHAR_0 &&
            (pszNameOrd[1] == CHAR_X || pszNameOrd[1] == CHAR_CAP_X)) {
        for (i = 2; i < nLen; i++) {
            if (!iswxdigit(pszNameOrd[i]))
                return;
        }

        nOrd =  axtoi(&pszNameOrd[2]);
    }
    else {
        /*
         * All characters must be numeric.  Negative numbers may
         * or may not be allowed, based on the fDecOnly flag.
         */
        for (i = 0; i < nLen; i++) {
            if (!iswdigit(pszNameOrd[i]) &&
                    (fDecOnly || i != 0 || pszNameOrd[0] != CHAR_MINUS))
                return;
        }

        nOrd = awtoi(pszNameOrd);
    }

    /*
     * Return the ordinal in the original buffer.
     */
    WriteOrd((PORDINAL)pszNameOrd, nOrd);
}