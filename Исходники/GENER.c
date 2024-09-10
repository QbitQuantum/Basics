static void exec( char *program, char *param ) {
    static char *args[3];
    int retcode;

    assert( program != NULL );
    assert( param != NULL );
#if DEBUG
    printf("*** Search '%s'\n", program );
#endif
    fn_split( program );

    args[0] = xfind( fn_make(".exe"), getrundir() );
    args[1] = param;
    args[2] = NULL;

#if DEBUG
    printf("*** Run '%s' '%s'\n", args[0], args[1] );
#endif
    retcode = spawnvp( P_WAIT, args[0], (void *)args );

    if ( retcode > 0 ) {
        fprintf( stderr, "\n'%s' exitcode = %d\n", program, retcode );
        if (! get_option(OPT_KEEPRSP) )
            unlink( RESPONSE );
        exit( retcode );
    } else if ( retcode < 0 ) {
        perror( program );
        if (! get_option(OPT_KEEPRSP) )
            unlink( RESPONSE );
      exit(1);
    }
}