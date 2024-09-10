int DrawTextExA(
    HDC hdc,
    LPSTR lpchText,
    int cchText,
    LPRECT lprc,
    UINT format,
    LPDRAWTEXTPARAMS lpdtp)
{
    LPWSTR lpwstr;
    int iRet;
    int iUniString;
    WORD wCodePage = (WORD)GdiGetCodePage(hdc);

    if (cchText == -1) {
        // USER_AWCONV_COUNTSTRINGSZ does not count/convert trailing \0.
        cchText = USER_AWCONV_COUNTSTRINGSZ;
    } else if (cchText < -1) {
        return 0;
    }

    if ((iUniString = MBToWCSEx(wCodePage, lpchText, cchText, &lpwstr, -1, TRUE)) == 0) {
        if (cchText == USER_AWCONV_COUNTSTRINGSZ) {
            lpwstr = (LPWSTR)gwszNullStr;
            format &= ~DT_MODIFYSTRING;
        } else {
            return 0;
        }
    }

    /*
     * Grow the buffer to accomodate the ellipsis (see AddEllipsisAndDrawLine)
     */
    if (format & DT_MODIFYSTRING) {
        int iNewLen = (iUniString + CCHELLIPSIS + 1) * sizeof(*lpwstr);
        LPWSTR lpwstrNew = UserLocalReAlloc(lpwstr, iNewLen, HEAP_ZERO_MEMORY);
        if (lpwstrNew == NULL) {
            UserLocalFree((HANDLE)lpwstr);
            return FALSE;
        }
        lpwstr = lpwstrNew;
    }

    iRet = DrawTextExWorker(hdc, lpwstr, iUniString, lprc, format, lpdtp, GetTextCharset(hdc));

    if (format & DT_MODIFYSTRING) {
        /*
         * Note that if the buffer grew and the caller provided the string size,
         *  then we won't return the additional characters... fixing this
         *  might break some apps so let's leave it alone until some one complains
         */
        if (cchText < 0) {
            UserAssert(cchText == USER_AWCONV_COUNTSTRINGSZ);
            // Guess how many bytes we can put in the buffer...
            // We can safely assume the maximum bytes available.
            // At worst, even for DBCS, the buffer size required
            // will be smaller than or equal to the orignal size,
            // because some DBCS characters would be substituted
            // to SBC ".", which is one byte each.
            // On the other hand, the number of characters converted
            // is limited by both iUniString and cchText.
            //
            if (IS_DBCS_ENABLED()) {
                cchText = iUniString * DBCS_CHARSIZE;
            } else {
                cchText = iUniString * sizeof(CHAR);
            }
        }
        WCSToMBEx(wCodePage, lpwstr, iUniString, &lpchText, cchText, FALSE);
    }

    if (lpwstr != gwszNullStr) {
        UserLocalFree((HANDLE)lpwstr);
    }

    return iRet;
}