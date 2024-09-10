/***********************************************************************
 *              pif_cmd
 *
 * execute a pif file.
 */
static VOID pif_cmd( char *filename, char *cmdline)
{ 
    HANDLE hFile;
    char progpath[MAX_PATH];
    char buf[128];
    char progname[64];
    char title[31];
    char optparams[65];
    char startdir[65];
    char *p;
    int closeonexit;
    int textmode;
    if( (hFile = CreateFileA( filename, GENERIC_READ, FILE_SHARE_READ,
                    NULL, OPEN_EXISTING, 0, 0 )) == INVALID_HANDLE_VALUE)
    {
        WINE_ERR("open file %s failed\n", wine_dbgstr_a(filename));
        return;
    }
    if( !read_pif_file( hFile, progname, title, optparams, startdir,
                &closeonexit, &textmode)) {
        WINE_ERR( "failed to read %s\n", wine_dbgstr_a(filename));
        CloseHandle( hFile);
        sprintf( buf, "%s\nInvalid file format. Check your pif file.", 
                filename);
        MessageBoxA( NULL, buf, "16 bit DOS subsystem", MB_OK|MB_ICONWARNING);
        SetLastError( ERROR_BAD_FORMAT);
        return;
    }
    CloseHandle( hFile);
    if( (p = strrchr( progname, '.')) && !strcasecmp( p, ".bat"))
        WINE_FIXME(".bat programs in pif files are not supported.\n"); 
    /* first change dir, so the search below can start from there */
    if( startdir[0] && !SetCurrentDirectoryA( startdir)) {
        WINE_ERR("Cannot change directory %s\n", wine_dbgstr_a( startdir));
        sprintf( buf, "%s\nInvalid startup directory. Check your pif file.", 
                filename);
        MessageBoxA( NULL, buf, "16 bit DOS subsystem", MB_OK|MB_ICONWARNING);
    }
    /* search for the program */
    if( !SearchPathA( NULL, progname, NULL, MAX_PATH, progpath, NULL )) {
        sprintf( buf, "%s\nInvalid program file name. Check your pif file.", 
                filename);
        MessageBoxA( NULL, buf, "16 bit DOS subsystem", MB_OK|MB_ICONERROR);
        SetLastError( ERROR_FILE_NOT_FOUND);
        return;
    }
    if( textmode)
        if( AllocConsole())
            SetConsoleTitleA( title) ;
    /* if no arguments on the commandline, use them from the pif file */
    if( !cmdline[0] && optparams[0])
        cmdline = optparams;
    /* FIXME: do something with:
     * - close on exit
     * - graphic modes
     * - hot key's
     * - etc.
     */ 
    start_dos_exe( progpath, cmdline );
}