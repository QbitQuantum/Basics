int __stdcall ___lscrtl_startup(HINSTANCE hInst, DWORD fdwReason, LPVOID lpvReserved)
{
    int flags;
    int rv;
    unsigned exceptBlock[2];
    char quote;
    char *cmd;
    asm mov [flags],edx;
    quote = 0;
    ___lsdllinit(flags, _dorundown, exceptBlock);
    if (!(flags & DLL) || fdwReason == DLL_PROCESS_ATTACH)
    {   
        if (flags & DLL)
        {
            if (!dllexists)
                dllexists++;
            else
            {
                MessageBox(0,"NonShared data segment required","Error",0);
                return 1;
            }
        }
    }
    __srproc(INITSTART, INITEND);
    if (flags & DLL)
    {
        rv = DllEntryPoint(hInst, fdwReason, lpvReserved) + 1;
    }
    else if (flags & GUI)
    {
        cmd = _oscmd;
        while ((!quote || *cmd != ' ') && *cmd)
        {
            if (*cmd == '"')
                quote ^= *cmd;
            cmd++;
        }
        while (*cmd && *cmd == ' ') cmd++;
        rv = WinMain(hInst, 0, cmd, 10) + 1;
    }
    else
    {
        rv = main(_argc, _argv, _environ) + 1;
    }
    if ((flags & DLL) && fdwReason == DLL_PROCESS_DETACH)
    {
        __srproc(EXITSTART, EXITEND);
    }
    rv--;
    if (!(flags & DLL))
    {
        _exit(rv);
        ExitProcess(rv); // needed to satisfy the debugger
    }
    return rv;
}