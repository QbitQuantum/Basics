// list all symbols of the module passed in
void enumModulesDlg::GetModuleSymbols( PCSTR imageName, EnumModuleInfo *userContext )
{
    HANDLE hProcess = GetCurrentProcess(); // NOT safe to hookhop
    DWORD64 BaseOfDll;
    char *Mask = "*";
    BOOL status;

    status = (BOOL)HookHop::FunctionHop(SymInitialize, hProcess, NULL, FALSE);
    if (status == FALSE)
    {
        return;
    }

    BaseOfDll = SymLoadModuleEx(hProcess, // NOT safe to hookhop
        NULL,
        imageName,
        NULL,
        0,
        0,
        NULL,
        0);

    if (BaseOfDll == 0)
    {
        SymCleanup(hProcess);
        return;
    }

    if (::SymEnumSymbols( // One of the parameters is 64-bit, and so we can't use our hook hop
        hProcess,                // Process handle from SymInitialize.
        BaseOfDll,               // Base address of module.
        Mask,                    // Name of symbols to match.
        EnumSymProc,             // Symbol handler procedure.
        userContext))            // User context.
    {
        // SymEnumSymbols succeeded
    }
    else
    {
        // SymEnumSymbols failed
    }

    SymCleanup( hProcess ); // NOT safe to hookhop
}