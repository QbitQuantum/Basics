void GetProg( char *cmd, char *eoc )
{
    char        save;
    char        prog_name[_MAX_PATH];
    char        buff1[_MAX_PATH2];
    char        buff2[_MAX_PATH2];
    char        *drive;
    char        *dir;
    char        *fname;
    char        *ext;
    char        *sfname;
#ifdef __WINDOWS__
    unsigned    a,b;
    char        **drivep;
    char        **dirp;
    char        buff3[_MAX_DRIVE+MAX_PATH+5];
#endif

    save = *eoc;
    *eoc = '\0';
    _splitpath2( (char *)cmd, (char *)buff1,
        (char **)&drive, (char **)&dir, (char **)&fname, (char **)&ext );
    *eoc = save;
#ifdef __NETWARE__
    if( ext[0] == '\0' )
        ext = ".nlm";
#elif defined( __DOS__ ) && defined( _PLS )
    if( ext[0] == '\0' )
        ext = ".exp";
#elif !defined( __UNIX__ )
    if( ext[0] == '\0' )
        ext = ".exe";
#endif
    _makepath( (char *)prog_name, (char *)drive, (char *)dir, (char *)fname, (char *)ext );

    if( drive[0] == '\0' && dir[0] == '\0' ) {
        _searchenv( (char *)prog_name, "PATH", ExeName );
    } else if( access( (char *)prog_name, R_OK ) == 0 ) {
        strcpy( ExeName, (char *)prog_name );
    }

    if( ExeName[0] == '\0' ) {
        Output( MsgArray[MSG_PROGRAM - ERR_FIRST_MESSAGE] );
        Output( (char *)prog_name );
        Output( "\r\n" );
        fatal();
    }

#ifdef __WINDOWS__
    /*
     * for windows, we need to make our current directory the
     * same as that for the EXE, since windows moves our current directory
     * to that of the sampler
     */
    _splitpath2( ExeName, buff2, &drive, &dir, NULL, NULL );
    a = tolower( drive[0] ) - 'a' + 1;
    _dos_setdrive( a, &b );
    dir[strlen( dir ) - 1] = '\0';
    chdir( dir );
#endif

    _splitpath2( SampName, (char *)buff2,
        (char **)&drive, (char **)&dir, (char **)&sfname, (char **)&ext );

    /*
     * for windows, we need to give the sample file an absolute
     * path name so that both threads of the sampler can write
     * to the sample file
     */
#ifdef __WINDOWS__
    drivep = (drive[0] == '\0') ? &drive : NULL;
    dirp   = (dir[0]   == '\0') ? &dir   : NULL;
    if( drivep != NULL || dirp != NULL ) {
        _splitpath2( ExeName, buff3, drivep, dirp, NULL, NULL );
    }
#endif

    _makepath( SampName, (char *)drive, (char *)dir, (char *)(sfname[0] == '\0' ? fname : sfname),
               ext[0] == '\0' ? (char *)"smp" : (char *)ext );

#ifdef __WINDOWS__
    _fstrcpy( SharedMemory->SampName, SampName );
#endif
}