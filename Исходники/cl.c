/*
 * Link any object and library files.  Returns LINK_NOACTION if there was no
 * file to compile, LINK_ERROR if the linker returned a bad status code or
 * if the compiler could not be spawned, or else LINK_SUCCESS if everything
 * went smoothly.
 */
static int link( const OPT_STORAGE *cmdOpts, CmdLine *linkCmdLine )
/*****************************************************************/
{
    char **             args;
    char *              filename;
    int                 fileType;
    int                 numFiles;
    int                 rc;
    char *              defFile;
    char *              prevDefFile = NULL;

    cmdOpts = cmdOpts;
    /*** Process all object and library file names ***/
    for( numFiles=0; ; numFiles++ ) {
        filename = GetNextFile( &fileType, TYPE_OBJ_FILE, TYPE_LIB_FILE, TYPE_RES_FILE, TYPE_INVALID_FILE );
        if( filename == NULL )  break;
        AppendCmdLine( linkCmdLine, CL_L_FILENAMES_SECTION, filename );
    }

    /*** Process .def files ***/
    for( ;; ) {
        defFile = GetNextFile( NULL, TYPE_DEF_FILE, TYPE_INVALID_FILE );
        if( defFile == NULL )  break;
        if( prevDefFile != NULL ) {
            Warning( "Overriding %s with %s", prevDefFile, defFile );
        }
        prevDefFile = defFile;
    };
    if( prevDefFile != NULL ) {
        AppendFmtCmdLine( linkCmdLine, CL_L_OPTS_SECTION, "/DEF:%s", prevDefFile );
    } else {
        if( numFiles == 0 )  return( LINK_NOACTION );
    }

    /*** Spawn the linker ***/
    AppendCmdLine( linkCmdLine, CL_L_PROGNAME_SECTION, LINKER );
    args = MergeCmdLine( linkCmdLine, INVALID_MERGE_CMDLINE );
    rc = spawnvp( P_WAIT, LINKER, (const char **)args );
    if( rc != 0 ) {
        if( rc == -1  ||  rc == 255 ) {
            FatalError( "Unable to execute '%s'", LINKER );
        } else {
            return( LINK_ERROR );
        }
    }
    return( LINK_SUCCESS );
}