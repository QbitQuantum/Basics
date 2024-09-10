VOID
cdecl
PlotDbgPrint(
    LPCSTR   pszFormat,
    ...
)

/*++

Routine Description:

    This fucntion output the debug informat to the debugger


Arguments:

    pszFormat   - format string

    ...         - variable data


Return Value:


    VOID

Author:

    15-Nov-1993 Mon 17:57:59 created


Revision History:


--*/

{
    va_list         vaList;

#if defined(UMODE) || defined(USERMODE_DRIVER)

    static WCHAR    wOutBuf[768];
    static WCHAR    wFormatBuf[256];
    size_t          cch;

    //
    // We assume that UNICODE flag is turn on for the compilation, bug the
    // format string passed to here is ASCII version, so we need to convert
    // it to LPWSTR before the wvsprintf()
    //

    if (!SUCCEEDED(StringCchLengthA(pszFormat, CCHOF(wFormatBuf), &cch)))
    {
        return;
    }

    va_start(vaList, pszFormat);
    MultiByteToWideChar(CP_ACP, 0, pszFormat, -1, wFormatBuf, CCHOF(wFormatBuf));
    if (!SUCCEEDED(StringCchVPrintfW(wOutBuf, CCHOF(wOutBuf), wFormatBuf, vaList)))
    {
        return;
    }
    va_end(vaList);

    OutputDebugString((LPCTSTR)wOutBuf);
    OutputDebugString(TEXT("\n"));

#else

    va_start(vaList, pszFormat);
    EngDebugPrint("PLOT",pszFormat,vaList);
    va_end(vaList);

#endif
}