LPVOID getCtrlRoutine() {
    LPVOID ctrlRoutine;
    
    // CtrlRoutine --> MyHandle --> getCtrlRoutine
    // set the CaptureStackBackTrace's first param to 2 to ingore the MyHandler and getCtrlRoutine calls.
    // should disable complier optimization on Release version.
    USHORT count = CaptureStackBackTrace((ULONG) 2, (ULONG) 1, &ctrlRoutine, NULL);
    if (count != 1) {
        _tprintf(__T("CaptureStackBackTrace error\n"));
        goto error;
    }
    
    HANDLE hProcess = GetCurrentProcess();
    if (!SymInitialize(hProcess, NULL, TRUE)) {
        RETVAL rv; _HandleLastError(rv, __T("SymInitialize"));
    }
    
    ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME*sizeof(TCHAR) + sizeof(ULONG64)-1)/sizeof(ULONG64)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO) buffer;
    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    pSymbol->MaxNameLen = MAX_SYM_NAME;
    
    LPVOID funcCtrlRoutine = NULL;
    DWORD64 dwDisplacement = 0;
    if(!SymFromAddr(hProcess, (DWORD64) ctrlRoutine, &dwDisplacement, pSymbol)) {
        RETVAL rv; _HandleLastError(rv, __T("SymFromAddr"));
    }
    funcCtrlRoutine = reinterpret_cast<LPVOID>(pSymbol->Address);
    
    SymCleanup(hProcess);
    
    return funcCtrlRoutine;
    
error:
    return NULL;
}