/**
 * Loads the elements of the call stack in a list
 * @param exceptionInfos are useful information on the exception
 */
void LoadCallStack(EXCEPTION_POINTERS* exceptionInfos, HANDLE &hProcess, std::list<std::string> &callStack,
                   std::list<std::string> &fileStack)
{
    STACKFRAME64 tempStackFrame;
    CONTEXT context = *(exceptionInfos->ContextRecord);
    memset( &tempStackFrame, 0, sizeof(STACKFRAME64) );
    DWORD machineType;

#ifdef _M_IX86
    machineType                     = IMAGE_FILE_MACHINE_I386;
    tempStackFrame.AddrPC.Offset    = context.Eip;
    tempStackFrame.AddrPC.Mode      = AddrModeFlat;
    tempStackFrame.AddrStack.Offset = context.Esp;
    tempStackFrame.AddrStack.Mode   = AddrModeFlat;
    tempStackFrame.AddrFrame.Offset = context.Ebp;
    tempStackFrame.AddrFrame.Mode   = AddrModeFlat;
#elif _M_X64
    machineType                     = IMAGE_FILE_MACHINE_AMD64;
    tempStackFrame.AddrPC.Offset    = context.Rip;
    tempStackFrame.AddrPC.Mode      = AddrModeFlat;
    tempStackFrame.AddrFrame.Offset = context.Rsp;
    tempStackFrame.AddrFrame.Mode   = AddrModeFlat;
    tempStackFrame.AddrStack.Offset = context.Rsp;
    tempStackFrame.AddrStack.Mode   = AddrModeFlat;
#elif _M_IA64
    machineType                      = IMAGE_FILE_MACHINE_IA64;
    tempStackFrame.AddrPC.Offset     = context.StIIP;
    tempStackFrame.AddrPC.Mode       = AddrModeFlat;
    tempStackFrame.AddrFrame.Offset  = context.IntSp;
    tempStackFrame.AddrFrame.Mode    = AddrModeFlat;
    tempStackFrame.AddrBStore.Offset = context.RsBSP;
    tempStackFrame.AddrBStore.Mode   = AddrModeFlat;
    tempStackFrame.AddrStack.Offset  = context.IntSp;
    tempStackFrame.AddrStack.Mode    = AddrModeFlat;
#else
#error "Platform not supported!"
#endif

    ULONG64 buffer[(sizeof(SYMBOL_INFO) + nbChar*sizeof(TCHAR) + sizeof(ULONG64) + 1) / sizeof(ULONG64)];
    PSYMBOL_INFO pSymbol = reinterpret_cast<PSYMBOL_INFO>(buffer);
    PSTR undecoratedName = (PSTR)malloc(sizeof(TCHAR) * nbChar);

    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    pSymbol->MaxNameLen   = nbChar;
    DWORD lineDisplacement;
    IMAGEHLP_LINE64 lineInfo = { sizeof(IMAGEHLP_LINE64) };

    while(StackWalk64(machineType, hProcess, GetCurrentThread(), &tempStackFrame, &context, NULL,
                      SymFunctionTableAccess64, SymGetModuleBase64, NULL))
    {
        // Sanity stack check
        if(tempStackFrame.AddrPC.Offset == 0)
        {
            break;
        }

        DWORD64 symDisplacement = 0;
        // Try to get the symbol name
        if(SymFromAddr(hProcess, tempStackFrame.AddrPC.Offset, &symDisplacement, pSymbol))
        {
            UnDecorateSymbolName(pSymbol->Name, undecoratedName, MAX_SYM_NAME, UNDNAME_COMPLETE);
            callStack.push_back(std::string((char*)undecoratedName) + "+" +
                                ::boost::lexical_cast<std::string>(symDisplacement));

            if(SymGetLineFromAddr64(hProcess, tempStackFrame.AddrPC.Offset, &lineDisplacement, &lineInfo))
            {
                fileStack.push_back(std::string(lineInfo.FileName) + "\tl:" +
                                    ::boost::lexical_cast<std::string>(lineInfo.LineNumber));
            }
            else
            {
                fileStack.push_back("No info");
            }
        }
        else
        {
        }
    }
    free(undecoratedName);
}