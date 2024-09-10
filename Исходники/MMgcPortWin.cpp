    bool AVMPI_getFunctionNameFromPC(uintptr_t pc, char *buffer, size_t bufferSize)
    {
#ifdef UNDER_CE
        (void)pc;
        (void)buffer;
        (void)bufferSize;
        return false;
#else

        if(!InitDbgHelp())
            return false;

        // gleaned from IMAGEHLP_SYMBOL64 docs
        IMAGEHLP_SYMBOL64 *pSym = (IMAGEHLP_SYMBOL64 *) alloca(sizeof(IMAGEHLP_SYMBOL64) + MaxNameLength);
        pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
        pSym->MaxNameLength = MaxNameLength;

        DWORD64 offsetFromSymbol;
        if(!g_DbgHelpDll.m_SymGetSymFromAddr64 ||
            !(*g_DbgHelpDll.m_SymGetSymFromAddr64)(GetCurrentProcess(), pc, &offsetFromSymbol, pSym)) {
                return false;
        }

        StringCchPrintfA(buffer, bufferSize, "%s", pSym->Name);
        //printf("%s\n", pSym->Name);
        return true;

#endif //UNDER_CE
    }