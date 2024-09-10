mad_status MADSysLoad( const char *path, mad_client_routines *cli, mad_imp_routines **imp, mad_sys_handle *sys_hdl )
{
    mad_sys_handle      shlib;
    mad_init_func       *init_func;
    char                newpath[_MAX_PATH];
    char                full_path[_MAX_PATH];
    mad_status          status;

    *sys_hdl = NULL_SYSHDL;
    strcpy( newpath, path );
    strcat( newpath, ".so" );
    shlib = dlopen( newpath, RTLD_NOW );
    if( shlib == NULL ) {
        _searchenv( newpath, "PATH", full_path );
        shlib = dlopen( full_path, RTLD_NOW );
        if( shlib == NULL ) {
            return( MS_ERR | MS_FOPEN_FAILED );
        }
    }
    status = MS_ERR | MS_INVALID_MAD;
    init_func = (mad_init_func *)dlsym( shlib, "MADLOAD" );
    if( init_func != NULL && (*imp = init_func( &status, cli )) != NULL ) {
        *sys_hdl = shlib;
        return( MS_OK );
    }
    dlclose( shlib );
    return( status );
}