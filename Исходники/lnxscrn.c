static bool TryXWindows( void )
{
    int         slavefd;
    int         masterfd;
    char        buff[64];
    char        **argv;
    char        *p;
    char        *end;
    unsigned    argc;
    char        slavename[] = "/dev/pts/xxxxxx";
    int         unlock = 0;
    char        buf;
    int         res;
    struct termios termio;

    /* we're in the X (or helper)environment */
    if ( getenv( "DISPLAY" ) == NULL )
        return( false );
    masterfd = open( "/dev/ptmx", O_RDWR );
    if( masterfd < 0 )
        return( false );
    fcntl( masterfd, F_SETFD, 0 );
    ioctl( masterfd, TIOCGPTN, &slavefd ); /* slavefd = ptsname(masterfd); */
    ioctl( masterfd, TIOCSPTLCK, &unlock ); /* unlockpt(masterfd); */
    sprintf( slavename + 9, "%d", slavefd );
    slavefd = open( slavename, O_RDWR );
    DbgConHandle = slavefd;
    if( DbgConHandle == -1 ) {
        StartupErr( "unable to open debugger console" );
        return( false );
    }
    tcgetattr( slavefd, &termio );
    termio.c_lflag &= ~ECHO;
    tcsetattr( slavefd, TCSANOW, &termio );
    argc = 0;
    p = XConfig;
    for( ;; ) {
        while( isspace( *p ) )
            ++p;
        while( !isspace( *p ) && *p != '\0' )
            ++p;
        if( *p == '\0' )
            break;
        ++argc;
        *p++ = '\0';
    }
    end = p;
    _AllocA( argv, ( argc + 16 ) * sizeof( *argv ) );

    argv[0] = "xterm";
    argv[1] = "-title";
    argv[2] = "Open Watcom Debugger";
    argv[3] = "-ut";

    argc = 4;

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
    Format( p, "-SXX%u", masterfd );
    argv[argc++] = p;
    argv[argc] = NULL;

    fcntl( slavefd, F_SETFD, FD_CLOEXEC );
    XTermPid = fork();
    if( XTermPid == 0 ) { /* child */
        setpgid( 0, 0 );
#if defined( __UNIX__ ) && !defined( __WATCOMC__ )
        execvp( argv[0], (char * const *)argv );
#else
        execvp( argv[0], (const char **)argv );
#endif
        exit( 1 );
    }
    if( XTermPid == (pid_t)-1 ) {
        StartupErr( "unable to create console helper process" );
    }
    do { /* xterm transmits a window ID -- ignore */
        res = read( slavefd, &buf, 1 );
    } while( res != -1 && buf != '\n' );
    termio.c_lflag |= ECHO;
    tcsetattr( slavefd, TCSANOW, &termio );

    /* make slavefd a controlling tty */
    setpgid( 0, XTermPid );
    setsid();
    ioctl( slavefd, TIOCSCTTY, 1 );

    signal( SIGHUP, &HupHandler );
    return( true );
}