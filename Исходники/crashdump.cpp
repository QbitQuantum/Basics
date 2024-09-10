int StackTrace::GetSymbolInfo(Address address, char* symbol, int maxSymbolLen)
{
    if (!InitSymbols())
        return 0;

    // Start with address.
    int charsAdded = 
        _snprintf_s(symbol, maxSymbolLen, _TRUNCATE, "%p ", address);
    symbol += charsAdded;
    maxSymbolLen -= charsAdded;
    if (maxSymbolLen < 0)
        return charsAdded;

    const DWORD64 address64 = (DWORD64)address;
    // Module name
    IMAGEHLP_MODULE64 moduleInfo;
    ZeroMemory(&moduleInfo, sizeof(moduleInfo));
    moduleInfo.SizeOfStruct = sizeof(moduleInfo);
    const HANDLE hCurrentProcess = GetCurrentProcess();
    if (SymGetModuleInfo64(hCurrentProcess, address64, &moduleInfo))
    {
        char moduleName[_MAX_PATH + 1];
        GetFileFromPath(moduleInfo.ImageName, moduleName, _MAX_PATH);
        const int moduleLen = (int)strlen(moduleName);
        strncpy_s(symbol, maxSymbolLen, moduleName, _TRUNCATE);
        symbol += moduleLen;
        charsAdded += moduleLen;
        maxSymbolLen -= moduleLen;
    }
    if (maxSymbolLen <= 0)
        return charsAdded;

    // Symbol name
    ULONG64 symbolBuffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME*sizeof(TCHAR) +
            sizeof(ULONG64) - 1) / sizeof(ULONG64)] = { 0 };
    IMAGEHLP_SYMBOL64* symbolInfo = reinterpret_cast<IMAGEHLP_SYMBOL64*>(symbolBuffer);
    symbolInfo->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
    symbolInfo->MaxNameLength = MAX_SYM_NAME;
    DWORD64 disp(0);
    if (SymGetSymFromAddr64(hCurrentProcess, address64, &disp, symbolInfo))
    {
        const int symbolChars =
            _snprintf_s(symbol, maxSymbolLen, _TRUNCATE, " %s + 0x%X", symbolInfo->Name, disp);
        symbol += symbolChars;
        maxSymbolLen -= symbolChars;
        charsAdded += symbolChars;
    }
    if (maxSymbolLen <= 0)
        return charsAdded;

    // File + line
    DWORD displacementLine;
    IMAGEHLP_LINE64 lineInfo;
    ZeroMemory(&lineInfo, sizeof(lineInfo));
    lineInfo.SizeOfStruct = sizeof(lineInfo);
    if (SymGetLineFromAddr64(hCurrentProcess, address64, &displacementLine, &lineInfo))
    {
        char fileName[_MAX_PATH + 1];
        GetFileFromPath(lineInfo.FileName, fileName, _MAX_PATH);
        int fileLineChars(0);
        if (displacementLine > 0)
        {
            fileLineChars = _snprintf_s(symbol, maxSymbolLen, _TRUNCATE, 
                " %s(%d+%04d byte(s))", fileName, lineInfo.LineNumber, displacementLine);
        }
        else
        {
            fileLineChars = _snprintf_s(symbol, maxSymbolLen, _TRUNCATE,
                " %s(%d)", fileName, lineInfo.LineNumber);
        }
        symbol += fileLineChars;
        maxSymbolLen -= fileLineChars;
        charsAdded += fileLineChars;
    }
    return charsAdded;
}