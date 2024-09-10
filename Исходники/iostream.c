Int StartChildProcess ( Char *dir, Char *prg, Char *args[] )
{
/*  Int             j;       / loop variables                  */
/*  char            c[8];    / buffer for communication        */
/*  int             n;       / return value of 'select'        */
    int             slave;   /* pipe to child                   */
    Int            stream;

#if HAVE_TERMIOS_H
    struct termios  tst;     /* old and new terminal state      */
#elif HAVE_TERMIO_H
    struct termio   tst;     /* old and new terminal state      */
#elif HAVE_SGTTY_H
    struct sgttyb   tst;     /* old and new terminal state      */
#elif !defined(USE_PRECOMPILED)
/* If no way to store and reset terminal states is known, and we are
   not currently re-making the dependency list (via cnf/Makefile),
   then trigger an error. */
    #error No supported way of (re)storing terminal state is available
#endif

    /* Get a stream record */
    stream = NewStream();
    if (stream == -1)
      return -1;
    
    /* open pseudo terminal for communication with gap */
    if ( OpenPty(&PtyIOStreams[stream].ptyFD, &slave) )
    {
        Pr( "open pseudo tty failed\n", 0L, 0L);
        FreeStream(stream);
        return -1;
    }

    /* Now fiddle with the terminal sessions on the pty */
#if HAVE_TERMIOS_H
    if ( tcgetattr( slave, &tst ) == -1 )
    {
        Pr( "tcgetattr on slave pty failed\n", 0L, 0L);
        goto cleanup;

    }
    tst.c_cc[VINTR] = 0377;
    tst.c_cc[VQUIT] = 0377;
    tst.c_iflag    &= ~(INLCR|ICRNL);
    tst.c_cc[VMIN]  = 1;
    tst.c_cc[VTIME] = 0;
    tst.c_lflag    &= ~(ECHO|ICANON);
    tst.c_oflag    &= ~(ONLCR);
    if ( tcsetattr( slave, TCSANOW, &tst ) == -1 )
    {
        Pr("tcsetattr on slave pty failed\n", 0, 0 );
        goto cleanup;
    }
#elif HAVE_TERMIO_H
    if ( ioctl( slave, TCGETA, &tst ) == -1 )
    {
        Pr( "ioctl TCGETA on slave pty failed\n");
        goto cleanup;
    }
    tst.c_cc[VINTR] = 0377;
    tst.c_cc[VQUIT] = 0377;
    tst.c_iflag    &= ~(INLCR|ICRNL);
    tst.c_cc[VMIN]  = 1;
    tst.c_cc[VTIME] = 0;   
    /* Note that this is at least on Linux dangerous! 
       Therefore, we now have the HAVE_TERMIOS_H section for POSIX
       Terminal control. */
    tst.c_lflag    &= ~(ECHO|ICANON);
    if ( ioctl( slave, TCSETAW, &tst ) == -1 )
    {
        Pr( "ioctl TCSETAW on slave pty failed\n");
        goto cleanup;
    }
#elif HAVE_SGTTY_H
    if ( ioctl( slave, TIOCGETP, (char*)&tst ) == -1 )
    {
        Pr( "ioctl TIOCGETP on slave pty failed\n");
        goto cleanup;
    }
    tst.sg_flags |= RAW;
    tst.sg_flags &= ~ECHO;
    if ( ioctl( slave, TIOCSETN, (char*)&tst ) == -1 )
    {
        Pr( "ioctl on TIOCSETN slave pty failed\n");
        goto cleanup;
    }
#endif

    /* set input to non blocking operation */
    /* Not any more */

    PtyIOStreams[stream].inuse = 1;
    PtyIOStreams[stream].alive = 1;
    PtyIOStreams[stream].blocked = 0;
    PtyIOStreams[stream].changed = 0;
    /* fork */
    PtyIOStreams[stream].childPID = fork();
    if ( PtyIOStreams[stream].childPID == 0 )
    {
        /* Set up the child */
        close(PtyIOStreams[stream].ptyFD);
        if ( dup2( slave, 0 ) == -1)
            _exit(-1);
        fcntl( 0, F_SETFD, 0 );
        
        if (dup2( slave, 1 ) == -1)
            _exit(-1);
        fcntl( 1, F_SETFD, 0 );
        
        if ( chdir(dir) == -1 ) {
            _exit(-1);
        }

#if HAVE_SETPGID
        setpgid(0,0);
#endif

        execv( prg, args );

        /* This should never happen */
        close(slave);
        _exit(1);
    }

    /* Now we're back in the master */
    /* check if the fork was successful */
    if ( PtyIOStreams[stream].childPID == -1 )
    {
        Pr( "Panic: cannot fork to subprocess.\n", 0, 0);
        goto cleanup;
    }
    close(slave);
    
    
    return stream;

 cleanup:
    close(slave);
    close(PtyIOStreams[stream].ptyFD);
    PtyIOStreams[stream].inuse = 0;
    FreeStream(stream);
    return -1;
}