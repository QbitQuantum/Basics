HINSTANCE R_loadLibrary(const char *path, int asLocal, int now,
			const char *search)
{
    HINSTANCE tdlh;
    unsigned int dllcw, rcw;
    int useSearch = search && search[0];

    rcw = _controlfp(0,0) & ~_MCW_IC;  /* Infinity control is ignored */
    _clearfp();
    if(useSearch) setDLLSearchPath(search);
    tdlh = LoadLibrary(path);
    if(useSearch) setDLLSearchPath(NULL);
    dllcw = _controlfp(0,0) & ~_MCW_IC;
    if (dllcw != rcw) {
	_controlfp(rcw, _MCW_EM | _MCW_IC | _MCW_RC | _MCW_PC);
	if (LOGICAL(GetOption1(install("warn.FPU")))[0])
	    warning(_("DLL attempted to change FPU control word from %x to %x"),
		    rcw,dllcw);
    }
    return(tdlh);
}