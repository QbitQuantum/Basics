void GUImain( void )
{
    char buff[256];

    // fix up env vars if necessary
    watcom_setup_env();

    SetErrorMode( SEM_FAILCRITICALERRORS );
    SetHandleCount( 60 );
    _8087 = 0;
    CmdData=buff;
    getcmd( CmdData );
    DebugMain();
    InitHookFunc();
}