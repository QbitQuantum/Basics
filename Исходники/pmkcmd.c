static int RunCommand( char *cmd )
{
    char        *p;
    const char  **argv;
    int         i;
    bool        skip_sp;

    skip_sp = true;
    i = 1;
    for( p = cmd; *p != '\0'; ++p ) {
        if( *p == ' ' ) {
            skip_sp = true;
        } else if( skip_sp ) {
            ++i;
            skip_sp = false;
        }
    }
    argv = (const char **)malloc( i * sizeof( char * ) );
    if( argv == NULL )
        return( 1 );    // error no memory
    skip_sp = true;
    i = 0;
    for( p = cmd; *p != '\0'; ++p ) {
        if( *p == ' ' ) {
            if( skip_sp )
                continue;
            skip_sp = true;
            *p = '\0';
        } else if( skip_sp ) {
            skip_sp = false;
            argv[i++] = p;
        }
    }
    argv[i] = NULL;
    i = (int)spawnvp( P_WAIT, cmd, argv );
    free( (void *)argv );
    return( i );
}