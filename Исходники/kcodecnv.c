LRESULT TransConvertList( HIMC hImc, LPIMESTRUCT lpIme)
{
    LPSTR           lpSrc;
    LPSTR           lpDst;
    HGLOBAL         hCandList;
    LPCANDIDATELIST lpCandList;
    LPSTR           lpCandStr;
    UINT            i, uBufLen;
    LRESULT         lRet = 0;

    lpSrc = lpSource(lpIme);
    lpDst = lpDest(lpIme);
    uBufLen = ImmGetConversionListA(GetKeyboardLayout(0), hImc, (LPCSTR)lpSrc,
            NULL, 0, GCL_CONVERSION);
    if (uBufLen)
    {
        hCandList = GlobalAlloc(GHND, uBufLen);
        lpCandList = (LPCANDIDATELIST)GlobalLock(hCandList);
        lRet = ImmGetConversionListA(GetKeyboardLayout(0), hImc, (LPCSTR)lpSrc,
                lpCandList, uBufLen, GCL_CONVERSION);
        for (i = 0; i < lpCandList->dwCount; i++)
        {
            lpCandStr = (LPSTR)lpCandList + lpCandList->dwOffset[i];
            *lpDst++ = *lpCandStr++;
            *lpDst++ = *lpCandStr++;
        }
        *lpDst = '\0';
        lpIme->wCount = (WORD)lpCandList->dwCount * 2;
        GlobalUnlock(hCandList);
        GlobalFree(hCandList);
    }
    return (lRet);
}