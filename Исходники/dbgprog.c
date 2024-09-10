void FindLocalDebugInfo( const char *name )
{
    char        *buff, *symname;
    unsigned    len;
    handle      local;

    len = strlen( name );
    _AllocA( buff, len + 1 + 4 + 2 );
    _AllocA( symname, len + 1 + 4 );
    strcpy( buff, "@l" );
    // If a .sym file is present, use it in preference to the executable
    local = FullPathOpen( name, ExtPointer( name, OP_LOCAL ) - name, "sym", symname, len + 4 );
    if( local != NIL_HANDLE ) {
        strcat( buff, symname );
        FileClose( local );
    } else {
        strcat( buff, name );
    }
    InsertRing( RingEnd( &LocalDebugInfo ), buff, strlen( buff ), FALSE );
}