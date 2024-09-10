//--------------------------------------------------------------------------
//      Local helper functions
//--------------------------------------------------------------------------
BOOL __stdcall
DebugPrint(
    LPCWSTR     pszMessage,
        // Format string for the error message
    ...
        // args specified in the format string.
    )
{
    va_list arglist;
        // varargs list for processing the '...' parameter.

    WCHAR szMsgBuf[MAX_PATH] = {0};
        // Use a stack error buffer so that we don't need to
        // allocate in the failure path.

    HRESULT     hResult;
        // Result from formatting the string.

    if (NULL == pszMessage)
    {
        return FALSE;
    }

    // Pass the variable parameters to wvsprintf to be formated.
    va_start(arglist, pszMessage);
    hResult = StringCbVPrintfW(szMsgBuf, MAX_PATH*sizeof(szMsgBuf[0]), pszMessage, arglist);
    va_end(arglist);

    // Dump string to debug output.
    OutputDebugStringW(szMsgBuf);

    return SUCCEEDED(hResult);
}