int main( int argc, char * const argv[] )
{
    char                myfile[ sizeof __FILE__ ];
    int                 child = argc > 1;
    int                 handle;
    int                 status;
    int                 handle_out;
    long                size;


    /*** Initialize ***/
    strcpy( ProgramName, argv[0] );     /* store filename */
    strlwr( ProgramName );              /* and lower case it */
    strcpy( myfile, __FILE__ );
    strlwr( myfile );

    if( child ) {
        char    *env_var;

        if( argc == 4 ) {        
        /* Verify expected command line contents */
            VERIFY( !strcmp( argv[1], ARG1 ) );
            VERIFY( !strcmp( argv[2], ARG2 ) );
            VERIFY( !strcmp( argv[3], ARG3 ) );

        /* Verify expected environment contents */
            env_var = getenv( VAR_NAME );
            VERIFY( env_var );
            VERIFY( !strcmp( env_var, VAR_TEXT ) );

            if( NumErrors != 0 ) {
                return( EXIT_FAILURE );
            } else {
                return( CHILD_RC );
            }
        } else {
            if( argc == 2 ) {
            /* Verify expected command line contents */
                VERIFY( !strcmp( argv[1], ARG_REDIR ) );

            /* Write text to stdout */
                printf( REDIR_TEXT );

                if( NumErrors != 0 ) {
                    return( EXIT_FAILURE );
                } else {
                    return( CHILD_RC );
                }
            }
            else
                return( EXIT_FAILURE );
        }                   
    } else {
        int         rc;
        char        **env;
        const char  *path = "PATH=.";   /* Default PATH if none is found */
        const char  *child_args[] = { ProgramName, ARG1, ARG2, ARG3, NULL };
        const char  *child_envp[] = { NULL, VAR_NAME "=" VAR_TEXT, "DOS4G=QUIET", NULL };

        /* We need to pass PATH down to the child because DOS/4GW style stub
         * programs rely on it to function properly.
         */
        for( env = environ; *env; ++env )
            if( !strncmp( *env, "PATH=", 5 ) ) {
                path = *env;
                break;
            }

        child_envp[0] = path;

        /* Test spawn functions */
        rc = spawnle( P_WAIT, ProgramName, ProgramName, ARG1, ARG2, ARG3, NULL, child_envp );
        VERIFY( rc == CHILD_RC );

        rc = spawnlpe( P_WAIT, ProgramName, ProgramName, ARG1, ARG2, ARG3, NULL, child_envp );
        VERIFY( rc == CHILD_RC );

        rc = spawnve( P_WAIT, ProgramName, child_args, child_envp );
        VERIFY( rc == CHILD_RC );

        rc = spawnvpe( P_WAIT, ProgramName, child_args, child_envp );
        VERIFY( rc == CHILD_RC );

        /* Modify our environment that child will inherit */
        VERIFY( !setenv( VAR_NAME, VAR_TEXT, 1 ) );
        VERIFY( !setenv( "DOS4G", "QUIET", 1 ) );
        
        rc = spawnl( P_WAIT, ProgramName, ProgramName, ARG1, ARG2, ARG3, NULL );
        VERIFY( rc == CHILD_RC );

        rc = spawnlp( P_WAIT, ProgramName, ProgramName, ARG1, ARG2, ARG3, NULL );
        VERIFY( rc == CHILD_RC );

        rc = spawnv( P_WAIT, ProgramName, child_args );
        VERIFY( rc == CHILD_RC );

        rc = spawnvp( P_WAIT, ProgramName, child_args );
        VERIFY( rc == CHILD_RC );

        /* Check inherited output redirection */
        handle_out = dup( STDOUT_FILENO );
        
        handle = creat( "test.fil", S_IREAD|S_IWRITE );
        VERIFY( handle != -1 );

        status = dup2( handle, STDOUT_FILENO );
        VERIFY( status != -1 );

        status = close( handle );
        VERIFY( status == 0 );

        rc = spawnl( P_WAIT, ProgramName, ProgramName, ARG_REDIR, NULL );
        VERIFY( rc == CHILD_RC );

        status = dup2( handle_out, STDOUT_FILENO );
        VERIFY( status != -1 );
        
        handle = open( "test.fil", O_RDWR );
        VERIFY( handle != -1 );

        size = filelength( handle );
        VERIFY( size == strlen( REDIR_TEXT ) );

        status = close( handle );
        VERIFY( status == 0 );

        status = unlink( "test.fil" );
        VERIFY( status == 0 );

        signal_count = 0;
        signal_number = 0;
        /* Install SIGBREAK handler */
        VERIFY( signal( SIGBREAK, break_handler ) == SIG_DFL );

        /* Raise signal and verify results */
        VERIFY( raise( SIGBREAK ) == 0 );
        VERIFY( signal_count == 1 );
        VERIFY( signal_number == SIGBREAK );

        /* Raise again - nothing should have happened */
        VERIFY( raise( SIGBREAK ) == 0 );
        VERIFY( signal_count == 1 );

        /*** Print a pass/fail message and quit ***/
        if( NumErrors != 0 ) {
            printf( "%s: FAILURE (%d errors).\n", ProgramName, NumErrors );
            return( EXIT_FAILURE );
        }
        printf( "Tests completed (%s).\n", ProgramName );
    }

    return( 0 );
}