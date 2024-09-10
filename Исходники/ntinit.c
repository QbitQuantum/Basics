void GUImain( void )
{
    char        *buff;
    int         len;

    // fix up env vars if necessary
    watcom_setup_env();

    SetErrorMode( ERR_MODE );
#if defined( _M_IX86 )
    _8087 = 0;
#endif
    len = _bgetcmd( NULL, 0 );
    _AllocA( buff, len + 1 );
    getcmd( buff );
    CmdData = buff;

    DebugMain();
}