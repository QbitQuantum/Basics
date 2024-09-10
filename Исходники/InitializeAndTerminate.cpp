extern "C" void mainCRTStartup()
{
    _init_atexit();
    _initterm(__xc_a, __xc_z);
    main();
    _doexit();
    ExitProcess(0);
}