void _start(void)
{
    __TRY__
    int argc;
    char **argv;
    char **env;
    _startupinfo start_info;

    // Sets the current application type
    __set_app_type(_CONSOLE_APP);

    // Set default FP precision to 53 bits (8-byte double)
    // _MCW_PC (Precision control) is not supported on
    // the ARM and x64 architectures
#if defined(_X86_) && !defined(__x86_64)
    _controlfp(_PC_53, _MCW_PC);
#endif

    start_info.newmode = 0;
    if ( __getmainargs( &argc, &argv, &env, 0, &start_info ) < 0 )
    {
        ExitProcess(-1);
    }
    else
    {
        exit( main(argc, argv, env) );
    }

}