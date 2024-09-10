int run(
    int no,
    const char *bin
)
{
#ifdef _WIN32
    intptr_t ret;
    char test[ 5 ];
 # ifdef WIN32_VS
    sprintf_s( test, 5, "%u", no );
 # else
    sprintf( test, "%u", no );
 # endif
    printf( "(%u) ", no );

    if( verbose && keep_running )
        ret = _spawnl( _P_WAIT, bin, bin, STR_RUN_TEST, test, STR_KEEP_RUNNING, STR_VERBOSE, NULL );
    else if( verbose )
        ret = _spawnl( _P_WAIT, bin, bin, STR_RUN_TEST, test, STR_VERBOSE, NULL );
    else if( keep_running )
        ret = _spawnl( _P_WAIT, bin, bin, STR_RUN_TEST, test, STR_KEEP_RUNNING, NULL );
    else
        ret = _spawnl( _P_WAIT, bin, bin, STR_RUN_TEST, test, NULL );

    if( ret == EXIT_SUCCESS )
        return 0;
    else
        return EXIT_FAILURE;

#else /* ifdef _WIN32 */
    pid_t pid;
    int res = 0;
    char test[ 5 ];
    sprintf( test, "%u", no );
    printf( "(%u) ", no );
    fflush( stdout );
    pid = fork();

    if( pid == -1 ) // failed
    {
        printf( "Error forking test: %s\n", strerror( errno ) );
        exit( 1 );
    }
    else if( pid == 0 ) // child process
    {
        // launch process
        if( verbose && keep_running )
        {
            if( execlp( bin, bin, STR_RUN_TEST, test, STR_VERBOSE, STR_KEEP_RUNNING, NULL ) < 0 )
            {
                printf( "Error running test: %s\n", strerror( errno ) );
                return EXIT_FAILURE;
            }
        }
        else if( verbose )
        {
            if( execlp( bin, bin, STR_RUN_TEST, test, STR_VERBOSE, NULL ) < 0 )
            {
                printf( "Error running test: %s\n", strerror( errno ) );
                return EXIT_FAILURE;
            }
        }
        else if( keep_running )
        {
            if( execlp( bin, bin, STR_RUN_TEST, test, STR_KEEP_RUNNING, NULL ) < 0 )
            {
                printf( "Error running test: %s\n", strerror( errno ) );
                return EXIT_FAILURE;
            }
        }
        else
        {
            if( execlp( bin, bin, STR_RUN_TEST, test, NULL ) < 0 )
            {
                printf( "Error running test: %s\n", strerror( errno ) );
                return EXIT_FAILURE;
            }
        }

        exit( 0 );
    }
    else
    {
        if( wait( &res ) == pid )
        {
            if( WEXITSTATUS( res ) == EXIT_SUCCESS )
                return 0;
            else
                return EXIT_FAILURE;
        }
    }

    return 0;

#endif /* ifdef _WIN32 */
} /* run */