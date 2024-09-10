int exceptionHandler(unsigned int code, struct _EXCEPTION_POINTERS *e)
{
    char strCode[128];
    bool canContinue;
    int numException = 0;
    char szTemp[1024];
    PEXCEPTION_POINTERS eNext = e;
    PEXCEPTION_RECORD excRec;
    static DWORD numCall = 0;

    if (numCall++ >= 4)
        ExitProcess(0);

    _snprintf(szTemp, sizeof(szTemp), "!!! exceptionHandler(0x%08p)->0x%08p  [ %03d ] *************************** !!!",
        e, e->ExceptionRecord, numCall);
    // OutputDebugString(szTemp);
    deb(szTemp);

    _snprintf(szTemp, sizeof(szTemp),
        "eax=0x%08X ebx=0x%08X ecx=0x%08X edx=0x%08X\r\nesi=0x%08X edi=0x%08X esp=0x%08X ebp=0x%08X",
        eNext->ContextRecord->Eax, eNext->ContextRecord->Ebx, eNext->ContextRecord->Ecx, eNext->ContextRecord->Edx,
        eNext->ContextRecord->Esi, eNext->ContextRecord->Edi, eNext->ContextRecord->Esp, eNext->ContextRecord->Ebp);
    // OutputDebugString(szTemp);
    deb(szTemp);

    do
    {
        excRec = eNext->ExceptionRecord;

        numException++;

        // deb(" -> # %-4d 0x%08p", numException, excRec);
        // deb("code: %x", excRec->ExceptionCode);

        canContinue = excRec->ExceptionFlags == EXCEPTION_NONCONTINUABLE ? true:false;
        // deb("canContinue: %d", canContinue);

        if (excRec->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
        {
            _snprintf(strCode, sizeof(strCode), "Access violation (%s @ 0x%08p)",
                excRec->ExceptionInformation[0] ? "WRITE":"READ", excRec->ExceptionInformation[1]);
        }
        else
            if (excRec->ExceptionCode == EXCEPTION_IN_PAGE_ERROR)
            {
                _snprintf(strCode, sizeof(strCode), "Access in-page violation (%s @ 0x%08p) ntcode: %d",
                    excRec->ExceptionInformation[0] ? "READ":"WRITE", excRec->ExceptionInformation[1],
                    excRec->ExceptionInformation[2]);
            }
            else
            {
                _snprintf(strCode, sizeof(strCode), "<unkcode=%X> d0: 0x%08x d1: 0x%08x d2: 0x%08x",
                    excRec->ExceptionCode, excRec->ExceptionInformation[0], excRec->ExceptionInformation[1],
                    excRec->ExceptionInformation[2]);
            }

        _snprintf(szTemp, sizeof(szTemp), "Exception 0x%08X %s Address=0x%08X canContinue=%s", excRec->ExceptionCode,
            strCode, excRec->ExceptionAddress, canContinue ? "yes":"no");
        deb(szTemp);

        if (!eNext->ExceptionRecord->ExceptionRecord)
            break;

        excRec = eNext->ExceptionRecord->ExceptionRecord;
        eNext->ExceptionRecord = eNext->ExceptionRecord->ExceptionRecord;

    }
    while (excRec->ExceptionRecord);

    // find symbols
    LPAPI_VERSION av = ImagehlpApiVersion();
    // deb("dbghelp.dll: %d.%d rev:%d", av->MajorVersion, av->MinorVersion, av->Revision);

    int ret = SymInitialize(GetCurrentProcess(), "c:\\symbols", TRUE);
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS | SYMOPT_DEFERRED_LOADS | 0x01000000 |
        SYMOPT_CASE_INSENSITIVE | SYMOPT_LOAD_ANYTHING | SYMOPT_LOAD_LINES);
    if (!ret)
        deb("syminit failed: code=%d, %s", ret, fmterr());

    PSYMBOL_INFO si;
    unsigned long stackPtr = e->ContextRecord->Esp;
    DWORD dwDisp = false;
    unsigned __int64 dwDisp64 = false;
    LPVOID addr;

    si = (PSYMBOL_INFO)malloc(4096);

    for (int i = 0;i<100;i++)
    {
        memset(si, 0, 4096);
        // si.Name = (char*) a(128);
        si->MaxNameLen = 3000;
        si->SizeOfStruct = sizeof(SYMBOL_INFO) + 3000;

        memcpy((void*) &addr, (void*)stackPtr, 4);

        char szTemp[128];

        memset(szTemp, 0, sizeof(szTemp));
        si->Address = (unsigned __int64)addr;
        // get sym module name
        ret = SymFromAddr(GetCurrentProcess(), (unsigned __int64)addr, &dwDisp64, si);
        // if(ret)
        snprintf(szTemp, sizeof(szTemp), "  %03d 0x%08X :%-25s", i, addr, si->Name);

        // get sym module line number
        IMAGEHLP_LINE64 il;

        memset(&il, 0, sizeof(il));
        il.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
        il.Address = (unsigned __int64)addr;
        ret = SymGetLineFromAddr64(GetCurrentProcess(), (unsigned __int64)addr, &dwDisp, &il);

        char szTemp2[128];

        memset(szTemp2, 0, sizeof(szTemp2));

        if (il.LineNumber)
            snprintf(szTemp2, sizeof(szTemp2), "  %s:%d (0x%08X)", il.FileName, il.LineNumber, il.Address);

        // show line info

        if (addr && (strlen(szTemp) || strlen(szTemp2)))
            deb("  %s %s", szTemp, szTemp2[0] ? szTemp2:"");

        stackPtr -= 4;
    }
    // ret=SymEnumSymbols(GetCurrentProcess(), 0, "!", EnumSymProc, NULL);
    // if(!ret)
    // deb("enum err: %s", fmterr());

    deb("!!! exceptionHandler out\r\n");

    // EXCEPTION_CONTINUE_EXECUTION
    // EXCEPTION_EXECUTE_HANDLER

    return EXCEPTION_EXECUTE_HANDLER;
}