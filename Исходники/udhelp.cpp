int dbg_help_client_t::init(char* path) {
    DWORD64 dwBaseAddr=0;

    int chars;
    char exe_path[MAX_PATH];
    chars = GetModuleFileName(NULL, exe_path, MAX_PATH);
    if (chars == 0) { 
        fprintf(stderr,"Could not find base path for XED executable\n");
        fflush(stderr);
        exit(1);
    }
    //fprintf(stderr,"EXE PATH %s\n", exe_path);
    char* dir = find_base_path(exe_path);
    //fprintf(stderr,"DIR      %s\n", dir);

    char* dbghelp = append3(dir,"\\","dbghelp.dll");
    //fprintf(stderr,"DBGHLP   %s\n", dbghelp);

    if (_access_s(dbghelp,4) != 0) {
        //fprintf(stderr,
        //    "WARNING: Could not find dbghelp.dll in xed.exe directory\n");
        //fflush(stderr);
        return 0;
    }    
    //fprintf(stderr,"FOUND DBGHELP\n");

    if (validate_version(dbghelp)) {
        fprintf(stderr,
            "WARNING: dbghelp.dll version is too old\n");
        fflush(stderr);
        return 0;
    }


    //FIXME: Add a version check for the dll ( ImagehlpApiVersion is NOT
    //the right thing)
        
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    hProcess = GetCurrentProcess();
    
    if (SymInitialize(hProcess, NULL, FALSE))     {
        // nothing
    }
    else    {
        error = GetLastError();
        fprintf(stderr,"SymInitialize returned error : %d 0x%x\n",
                error, error);
        fflush(stderr);
        return 0;
    }


    actual_base = SymLoadModuleEx(hProcess, NULL, path, NULL, 
                                  dwBaseAddr, 0, NULL, 0);
    if (actual_base) {
        // nothing
    }
    else    {
        error = GetLastError();
        fprintf(stderr,"SymLoadModuleEx returned error : %d 0x%x\n", 
                error, error);
        fflush(stderr);
        return 0;
    }


    if (SymEnumerateModules64(hProcess, 
                        (PSYM_ENUMMODULES_CALLBACK64)enum_modules, this)) {
        // nothing
    }
    else    {
        error = GetLastError();
        fprintf(stderr,"SymEnumerateModules64 returned error : %d 0x%x\n",
               error, error);
        fflush(stderr);
        return 0;
    }

    if (SymEnumSymbols(hProcess, actual_base, 0, enum_sym, this))    {
        // nothing
    }
    else    {
        error = GetLastError();
        fprintf(stderr,"SymEnumSymbols failed: %d 0x%x\n", error, error);
        fflush(stderr);
        return 0;
    }

    make_symbol_vector(&sym_tab);
    initialized = true;
    return 1;
}