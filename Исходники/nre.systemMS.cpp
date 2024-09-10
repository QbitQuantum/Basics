int
doForkExec( char *prog, char *arg1 ) {
    int pid, i;

    i = checkFilePerms( prog );
    if ( i ) {
        return( i );
    }

    i = checkFilePerms( arg1 );
    if ( i ) {
        return( i );
    }

#ifndef windows_platform
    pid = fork();
    if ( pid == -1 ) {
        return -1;
    }

    if ( pid ) {
        /*  This is still the parent.  */
    }
    else {
        /* child */
        for ( i = 0; i < 100; i++ ) {
            close( i );
        }
        i = execl( prog, prog, arg1, ( char * ) 0 );
        printf( "execl failed %d\n", i );
        return( 0 );
    }
#else
    /* windows platform */
    if ( _spawnl( _P_NOWAIT, prog, prog, arg1 ) == -1 ) {
        return -1;
    }
#endif

    return( 0 );
}