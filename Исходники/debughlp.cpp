/* static */
BOOL
wxDbgHelpDLL::CallSymEnumSymbols(HANDLE hProcess,
                                 ULONG64 baseOfDll,
                                 wxPSYM_ENUMERATESYMBOLS_CALLBACK callback,
                                 const PVOID callbackParam)
{
#ifdef UNICODE
    if ( SymEnumSymbolsW )
    {
        if ( SymEnumSymbolsW(hProcess, baseOfDll, NULL, callback, callbackParam) )
            return TRUE;
    }

    if ( SymEnumSymbols )
    {
        wxEnumSymbolsCallbackBridge br(callback, callbackParam);

        if ( SymEnumSymbols(hProcess, baseOfDll, NULL, wxEnumSymbolsCallback, &br) )
            return TRUE;
    }
#else // !UNICODE
    if ( SymEnumSymbols )
    {
        if ( SymEnumSymbols(hProcess, baseOfDll, NULL, callback, callbackParam) )
            return TRUE;
    }
#endif // UNICODE/!UNICODE

    return FALSE;
}