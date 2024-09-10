void __cdecl WinMainCRTStartup()
{
    STARTUPINFO si;
    unsigned char *cl;
    int res;

    // check and init fpu if required,
    // exit if required, but not available
    if (_FPinit && (_FPinit() == 0)) ExitProcess(-2);

    // call c initialisers
    if (_initterm(__xi_a, __xi_z, 1)) ExitProcess(-3);

    // call c++ initialisers
    _initterm(__xc_a, __xc_z, 0);

    cl = GetCommandLine();

    if (cl == NULL) cl = "";

    // parse command line
    {
        unsigned char delim = ' ';

        // skip any leading whitespaces (just in case)
        while (*cl && *cl <= delim) ++cl;

        // skip one parameter, which should be the application filename
        for ( ; *cl > delim; ++cl)
        {
            if (*cl == '"') delim ^= ' ';
        }

        // skip any whitespaces before first command line argument
        while (*cl && *cl <= delim) ++cl;
    }

    // get startup info on how to show
    si.dwFlags = 0;
    GetStartupInfo(&si);

    // -WCRT- tag
    __asm {
        test  eax, 0x0a0d0a0d
        sub   eax, 0x54524357
        sub   eax, 0x0a0d0a0d
    }

    // call WinMain
    res =
	WinMain(
	    (HINSTANCE)GetModuleHandle(NULL),
	    NULL,
	    (LPSTR)cl,
	    (si.dwFlags & STARTF_USESHOWWINDOW) ? si.wShowWindow : SW_SHOWDEFAULT
	    );

    exit(res);
}