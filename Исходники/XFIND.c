char *xfind( char *fname, char *rundir ) {
    static char fpath[ LINE_MAX ];

    assert( fname != NULL );
    assert( rundir != NULL );
    /* where call cl386 */
    make_path( fname, rundir, fpath );
/*#if DEBUG
    printf( "*** 1.FindFile '%s'\n", fpath );
#endif*/
    if ( access( fpath , F_OK ) == 0 )
        return fpath;
/*#if DEBUG
    printf( "*** 2.FindFile in %%PATH%% '%s'\n", fname );
#endif*/
    /* in PATH */
    _searchenv( fname, "PATH", fpath );
/*#if DEBUG
    printf( "*** 3.FindFile found '%s'\n", fpath );
#endif*/
    if ( fpath[0] )
        return fpath;
    strcpy(fpath,fname);;
    return fpath;
}