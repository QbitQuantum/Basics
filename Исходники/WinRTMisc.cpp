void FWinRTMisc::PlatformPreInit()
{
    FGenericPlatformMisc::PlatformPreInit();

    // Use our own handler for pure virtuals being called.
    DefaultPureCallHandler = _set_purecall_handler(PureCallHandler);

    // initialize the file SHA hash mapping
    InitSHAHashes();
}