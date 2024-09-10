static bool TryXWindows( void )
{
    char        xqsh_name[CMD_LEN];
    int         pip[2];
    char        buff[64];
    char        **argv;
    int         len;
    char        *p;
    char        *end;
    unsigned    argc;

    /* we're in the X Windows (or helper)environment */
    if( pipe( pip ) != 0 ) {
        StartupErr( "unable to create console control channel" );
    }
    fcntl( pip[0], F_SETFD, (int)FD_CLOEXEC );
    searchenv( "qnxterm", "PATH", xqsh_name );
    if( xqsh_name[0] == NULLCHAR ) {
        StartupErr( "qnxterm executable not in PATH" );
    }
    argc = 0;
    p = XConfig;
    for( ;; ) {
        while( isspace( *p ) )
            ++p;
        while( !isspace( *p ) && *p != NULLCHAR )
            ++p;
        if( *p == NULLCHAR )
            break;
        ++argc;
        *p++ = NULLCHAR;
    }
    end = p;
    _AllocA( argv, (argc + 10) * sizeof( *argv ) );

    argv[0] = xqsh_name;
    argv[1] = "-T";
    argv[2] = "WATCOM Debugger";

    argc = 3;

    if( DbgLines != 0 || DbgColumns != 0 ) {
        argv[argc++] = "-geometry";
        if( DbgLines == 0 )
            DbgLines = 25;
        if( DbgColumns == 0 )
            DbgColumns = 80;
        p = Format( buff, "%ux%u+0+0", DbgColumns, DbgLines ) + 1;
        argv[argc++] = buff;
    }

    for( p = XConfig; p < end; p += strlen( p ) + 1 ) {
        while( isspace( *p ) )
            ++p;
        argv[argc++] = p;
    }
    argv[argc++] = "-tty";
    Format( p, "%u", pip[1] );
    argv[argc++] = p;
    argv[argc] = NULL;

    XQshPid = qnx_spawn( 0, 0, 0, -1, -1, _SPAWN_NEWPGRP,
                argv[0], argv, environ, NULL, 0 );
    if( XQshPid == (pid_t)-1 ) {
        StartupErr( "unable to create console helper process" );
    }
    /* close the write pipe here so that the read fails if xqsh aborts */
    close( pip[1] );
    len = read( pip[0], buff, sizeof( buff ) );
    if( len == -1 ) {
        StartupErr( "console helper process unable to initialize" );
    }
    close( pip[0] );
    buff[len] = NULLCHAR;
    DbgConHandle = open( buff, O_RDWR );
    if( DbgConHandle == -1 ) {
        StartupErr( "unable to open debugger console" );
    }
    SetTermType( "qnx" );
    tcsetct( DbgConHandle, getpid() );
    signal( SIGHUP, &HupHandler );
    return( true );
}