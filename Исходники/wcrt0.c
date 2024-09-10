void __cdecl wmainCRTStartup()
{
    wchar_t *cl;
    char *clbuffer;
    int argc;
    int res;

    // check and init fpu if required,
    // exit if required, but not available
    if (_FPinit && (_FPinit() == 0)) ExitProcess(-2);

    // call c initialisers
    if (_initterm(__xi_a, __xi_z, 1)) ExitProcess(-3);

    // call c++ initialisers
    _initterm(__xc_a, __xc_z, 0);

    // get command line
    cl = GetCommandLine();
    if (cl == NULL) cl = L"";

    // parse command line into argv array
    {
        int clsize;

        clsize = wcrt_parse_argvw(cl, &argc, NULL, NULL);

        clbuffer = (char *) malloc(clsize);

        if (clbuffer)
        {
            wcrt_parse_argvw(
                cl,
                &argc,
                (wchar_t **) clbuffer,
                (wchar_t *) (clbuffer + (argc + 1)*sizeof(wchar_t *))
            );
        } else {
            argc = 0;
        }
    }

    // -WCRT- tag
    __asm {
        test  eax, 0x0a0d0a0d
        sub   eax, 0x54524357
        sub   eax, 0x0a0d0a0d
    }

    // call main
    if (clbuffer)
    {
        res = wmain(argc, (wchar_t **) clbuffer, 0);
        free(clbuffer);

    } else {

        res = wmain(0, 0, 0);
    }

    exit(res);
}