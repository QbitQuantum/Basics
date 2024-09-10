char *LoadTrap( const char *parms, char *buff, trap_version *trap_ver )
{
    char                trpfile[CCHMAXPATH];
    unsigned            len;
    const char          *ptr;
    APIRET              rc;
    char                trpname[CCHMAXPATH] = "";
    char                trppath[CCHMAXPATH] = "";
    trap_init_func      *init_func;

    if( parms == NULL || *parms == '\0' )
        parms = "std";
    for( ptr = parms; *ptr != '\0' && *ptr != TRAP_PARM_SEPARATOR; ++ptr )
        ;
    len = ptr - parms;
    memcpy( trpfile, parms, len );
    trpfile[len] = '\0';

    /* To prevent conflicts with the 16-bit DIP DLLs, the 32-bit versions have the "D32"
     * extension. We will search for them along the PATH (not in LIBPATH);
     */
    strcpy( trpname, trpfile );
    strcat( trpname, ".D32" );
    _searchenv( trpname, "PATH", trppath );
    if( trppath[0] == '\0' ) {
        sprintf( buff, TC_ERR_CANT_LOAD_TRAP, trpname );
        return( buff );
    }
    rc = DosLoadModule( NULL, 0, trppath, &TrapFile );
    if( rc != 0 ) {
        sprintf( buff, TC_ERR_CANT_LOAD_TRAP, trppath );
        return( buff );
    }
    strcpy( buff, TC_ERR_WRONG_TRAP_VERSION );
    if( DosQueryProcAddr( TrapFile, 1, NULL, (PFN*)&init_func ) == 0
      && DosQueryProcAddr( TrapFile, 2, NULL, (PFN*)&FiniFunc ) == 0
      && DosQueryProcAddr( TrapFile, 3, NULL, (PFN*)&ReqFunc ) == 0 ) {
        if( DosQueryProcAddr( TrapFile, 4, NULL, (PFN*)&InfoFunc ) != 0 ) {
            InfoFunc = NULL;
        }
        if( DosQueryProcAddr( TrapFile, 5, NULL, (PFN*)&HardFunc ) != 0 ) {
            HardFunc = NULL;
        }
        parms = ptr;
        if( *parms != '\0' )
            ++parms;
        *trap_ver = init_func( parms, buff, trap_ver->remote );
        if( buff[0] == '\0' ) {
            if( TrapVersionOK( *trap_ver ) ) {
                TrapVer = *trap_ver;
                return( NULL );
            }
            strcpy( buff, TC_ERR_WRONG_TRAP_VERSION );
        }
    }
    KillTrap();
    return( buff );
}