static HANDLE GetSymHandle(void)
{
    static HANDLE symHandle = NULL;
    if (!symHandle) {
        BOOL bRet = SymInitialize(symHandle = GetCurrentProcess(), NULL, FALSE);
        if (bRet) {
            DWORD dwOptions = SymGetOptions();
            dwOptions &= ~SYMOPT_UNDNAME;
            dwOptions |= SYMOPT_LOAD_LINES;
            SymSetOptions(dwOptions);
        }
    }
    return symHandle;
}