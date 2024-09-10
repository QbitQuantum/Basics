static void DoCVPack( void )
/**************************/
{
#if !defined( __UNIX__ ) || defined(__WATCOMC__)
    int         retval;
    char        *name;

    if( (LinkFlags & CVPACK_FLAG) && (LinkState & LINK_ERROR) == 0 ) {
        if( SymFileName != NULL ) {
            name = SymFileName;
        } else {
            name = Root->outfile->fname;
        }
        retval = (int)spawnlp( P_WAIT, CVPACK_EXE, CVPACK_EXE, "/nologo",
                          name, NULL );
        if( retval == -1 ) {
            PrintIOError( ERR+MSG_CANT_EXECUTE, "12", CVPACK_EXE );
        }
    }
#endif
}