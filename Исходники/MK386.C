void make( char *maker ) {
    static char make_opt[ _MAX_PATH ];
//  static char *args[3];
    int err;

    sprintf( make_opt,
" -%cMAP -%cDEBUG -%cNODEFLIB -%cKEEP_SRC -%cKEEP_LST -%cLINK -%cASSEMBLE -%cCOMPILE",
        Def( _map_file), Def( _debug), Def( _nodef_lib),
        Def( _keep_gen ), Def( _dump_lst ),
        Def( _link), Def( _assemble ), Def( _compile ) );
    if ( _keep_rsp )
        strcat( make_opt, " -K" );
    if ( _build_all )
        strcat( make_opt, " -B" );
    printf( "%s%s\n", maker, make_opt );
    err = spawnlp( P_OVERLAY, maker, maker, make_opt, NULL );

    if ( err <  0 )
        error( ERR_RUNTIME, maker );
    else if ( err > 0 )
        error( err, maker );
}