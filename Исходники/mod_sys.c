static int modsys_exec( INSTANCE * my, int * params )
{
    int mode = params[0];
    char * filename = ( char * ) string_get( params[1] );
    int argc = params[2];
    char ** argv;
    int n = 0;
#ifndef WIN32
    pid_t child;
#endif
    int status = -1;

    // fill argv
    argv = ( char ** ) calloc( argc + 2, sizeof( char * ) );
    argv[0] = filename;
    for ( n = 0; n < argc; n++ )
        argv[n + 1] = ( char * ) string_get((( int * )( params[3] ) )[n] );

    // Execute program
#ifdef WIN32
    status = spawnvp( mode, filename, ( const char ** )argv );
#else
    if (( child = fork() ) == -1 )
    {
        //Error
        status = -1 ;
    }
    else if ( child == 0 )
    {
        execvp( filename, ( const char ** )argv );
        exit(-1);
    }
    else
    {
        /* father */
        switch ( mode )
        {
            case _P_WAIT:
                if ( waitpid( child, &status, WUNTRACED ) != child )
                    status = -1;
                else
                    status = (int)(char)WEXITSTATUS(status);
                break;

            case _P_NOWAIT:
                status = child;
                break;
        }
    }
#endif

    // Free resources
    string_discard( params[1] );
    if ( argv ) free( argv );

    return ( status ) ;
}