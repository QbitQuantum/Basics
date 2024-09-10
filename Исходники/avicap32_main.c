/***********************************************************************
 *             capCreateCaptureWindowA   (AVICAP32.@)
 */
HWND VFWAPI capCreateCaptureWindowA(LPCSTR lpszWindowName, DWORD dwStyle, INT x,
                                    INT y, INT nWidth, INT nHeight, HWND hWnd,
                                    INT nID)
{   UNICODE_STRING nameW;
    HWND retW;

    if (lpszWindowName) RtlCreateUnicodeStringFromAsciiz(&nameW, lpszWindowName);
    else nameW.Buffer = NULL;

    retW = capCreateCaptureWindowW(nameW.Buffer, dwStyle, x, y, nWidth, nHeight,
                                   hWnd, nID);
    RtlFreeUnicodeString(&nameW);

    return retW;
}