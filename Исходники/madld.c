mad_status MADSysLoad( const char *path, mad_client_routines *cli,
                       mad_imp_routines **imp, mad_sys_handle *sys_hdl )
{
    HMODULE             dll;
    mad_init_func       *init_func;
    mad_status          status;
    char                madname[CCHMAXPATH] = "";
    char                madpath[CCHMAXPATH] = "";

    /* To prevent conflicts with the 16-bit MAD DLLs, the 32-bit versions have the "D32"
     * extension. We will search for them along the PATH (not in LIBPATH);
     */
    strcpy( madname, path );
    strcat( madname, ".D32" );
    _searchenv( madname, "PATH", madpath );
    if( madpath[0] == '\0' || DosLoadModule( NULL, 0, madpath, &dll ) != 0 ) {
        return( MS_ERR|MS_FOPEN_FAILED );
    }
    status = MS_ERR|MS_INVALID_MAD;
    if( DosQueryProcAddr( dll, 0, "MADLOAD", (PFN FAR *)&init_func ) == 0
      && (*imp = init_func( &status, cli )) != NULL ) {
        *sys_hdl = dll;
        return( MS_OK );
    }
    DosFreeModule( dll );
    return( status );
}