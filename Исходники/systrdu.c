_WCRTLINK int system( const CHAR_TYPE *cmd )
{
    register CHAR_TYPE *name;
    int ret_code;

    name = getenv("COMSPEC");
    if( cmd == NULL ) {
        return( 1 );
    }
    if( name == NULL ) {
        name = "z:\\command.exe";
    }

    ret_code = spawnlp( P_WAIT, name, "command", "/c", cmd, NULL );
    return( ret_code );
}