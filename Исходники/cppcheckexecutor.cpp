static void PrintCallstack(FILE* f, PEXCEPTION_POINTERS ex)
{
    if (!loadDbgHelp())
        return;
    const HANDLE hProcess   = GetCurrentProcess();
    const HANDLE hThread    = GetCurrentThread();
    BOOL result = pSymInitialize(
                      hProcess,
                      0,
                      TRUE
                  );
    CONTEXT             context = *(ex->ContextRecord);
    STACKFRAME64        stack= {0};
#ifdef _M_IX86
    stack.AddrPC.Offset    = context.Eip;
    stack.AddrPC.Mode      = AddrModeFlat;
    stack.AddrStack.Offset = context.Esp;
    stack.AddrStack.Mode   = AddrModeFlat;
    stack.AddrFrame.Offset = context.Ebp;
    stack.AddrFrame.Mode   = AddrModeFlat;
#else
    stack.AddrPC.Offset    = context.Rip;
    stack.AddrPC.Mode      = AddrModeFlat;
    stack.AddrStack.Offset = context.Rsp;
    stack.AddrStack.Mode   = AddrModeFlat;
    stack.AddrFrame.Offset = context.Rsp;
    stack.AddrFrame.Mode   = AddrModeFlat;
#endif
    IMAGEHLP_SYMBOL64_EXT symbol;
    symbol.SizeOfStruct  = sizeof(IMAGEHLP_SYMBOL64);
    symbol.MaxNameLength = maxnamelength;
    DWORD64 displacement   = 0;
    int beyond_main=-1; // emergency exit, see below
    for (ULONG frame = 0; ; frame++) {
        result = pStackWalk64
                 (
#ifdef _M_IX86
                     IMAGE_FILE_MACHINE_I386,
#else
                     IMAGE_FILE_MACHINE_AMD64,
#endif
                     hProcess,
                     hThread,
                     &stack,
                     &context,
                     NULL,
                     pSymFunctionTableAccess64,
                     pSymGetModuleBase64,
                     NULL
                 );
        if (!result)  // official end...
            break;
        pSymGetSymFromAddr64(hProcess, (ULONG64)stack.AddrPC.Offset, &displacement, &symbol);
        TCHAR undname[maxnamelength]= {0};
        pUnDecorateSymbolName((const TCHAR*)symbol.Name, (PTSTR)undname, (DWORD)GetArrayLength(undname), UNDNAME_COMPLETE);
        if (beyond_main>=0)
            ++beyond_main;
        if (_tcscmp(undname, _T("main"))==0)
            beyond_main=0;
        fprintf(f,
                "%lu. 0x%08I64X in ",
                frame, (ULONG64)stack.AddrPC.Offset);
        fputs((const char *)undname, f);
        fputs("\n", f);
        if (0==stack.AddrReturn.Offset || beyond_main>2) // StackWalk64() sometimes doesn't reach any end...
            break;
    }

    FreeLibrary(hLibDbgHelp);
    hLibDbgHelp=0;
}