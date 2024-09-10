EESTATUS
GetExpr (
    uint radix,
    PEEHSTR phStr,
    ulong  *pEnd
    )
{
    EESTATUS    retval = EENOMEMORY;
    char *pStr;
    char *pExprStr;
    HDEP        hExprStr;
    int         len;
    ulong       strIndex;
    UINT nLen;

    Unreferenced( radix );

    //M00KLUDGE - this routine will eventuall have to walk the bound tree
    //            and format the expression because of ambiguous expressions

    // use the saved original string if there is one
    // (in case the expression has been modified)

    if (pExState->hExStrSav) {
        hExprStr = pExState->hExStrSav;
        len = pExState->ExLenSav;
        strIndex = pExState->strIndexSav;
    } else {
        hExprStr = pExState->hExStr;
        len = pExState->ExLen;
        strIndex = pExState->strIndex;
    }

    pExprStr = (char *) MemLock (hExprStr);

    nLen = len+1;
    if (((*phStr = MemAllocate (nLen)) != 0)) {
        // the expression has been bound and memory allocated
        char        tempBuf[TYPESTRMAX];
        UINT        nb;
        UINT        nIndex = 0;
        BOOL        fHSYM;
        char *psz;
        ulong       nAdj = 0;

        pStr = (char *) MemLock (*phStr);
        for (psz = pExprStr; (psz < pExprStr + len) && *psz; psz = _tcsinc (psz)) {
            fHSYM = FALSE;
            if (*psz == HSYM_MARKER) {
                HSYM hSym = GetHSYMFromHSYMCode(psz + 1);
                psz += HSYM_CODE_LEN;  // skip embedded HSYM code
                fHSYM = TRUE;
                DASSERT (hSym);
                if (GetNameFromHSYM(tempBuf, hSym) == FALSE) {
                    pExState->err_num = ERR_INTERNAL;
                    MemUnLock(*phStr);
                    MemUnLock(hExprStr);
                    return EEGENERAL;
                }
                nb = _tcslen(tempBuf);
                // compute adjustment for strIndex:
                // if an HSYM is to the left of strIndex,
                // strIndex needs to be adjusted
                if (psz <= pExprStr + strIndex)
                    nAdj += (nb - sizeof (char) - HSYM_CODE_LEN);
            } else {
                nb = 1;
            }

            // check if there is space in the buffer and
            // copy nb characters to the destination string

            if (nIndex + nb > nLen-1) {
                // there is not enough space, grow buffer
                MemUnLock(*phStr);
                nLen += NAMESTRMAX;
                if ((*phStr = MemReAlloc(*phStr, nLen)) == 0){
                    MemUnLock(hExprStr);
                    return EENOMEMORY;
                }
                pStr = (char *) MemLock (*phStr);
            }
            if (fHSYM) {
                // copy name from tembBuf
                memcpy(pStr+nIndex, tempBuf, nb);
                nIndex += nb;
            } else {
                // copy a single character from pExprStr
                _tccpy (pStr + nIndex, psz);
                nIndex += _tclen (psz);
            }
        }
        pStr[nIndex++] = 0;
        MemUnLock (*phStr);

        // Reallocate the buffer in case it is too large
        DASSERT (nIndex <= nLen);
        if (nIndex < nLen &&
            (*phStr = MemReAlloc(*phStr, nIndex)) == 0){
            MemUnLock(hExprStr);
            return EENOMEMORY;
        }
        retval = EENOERROR;
        *pEnd = strIndex + nAdj;
    }
    MemUnLock (hExprStr);

    return retval;
}