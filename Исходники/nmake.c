/*
 * Spawn the Watcom wmake.  Returns NMAKE_ERROR if wmake returned a bad
 * status code or if it could not be spawned, or else NMAKE_SUCCESS if
 * everything went smoothly.
 */
static int nmake( const OPT_STORAGE *cmdOpts, CmdLine *cmdLine )
/**************************************************************/
{
    char **             args;
    int                 rc;
    int                 count;
    char *              cwd;
    char                flagstmp[32] = {0};

    /*** get value for MAKEDIR field ***/
    cwd = getcwd( NULL, 0 );

    /*** construct MAKEFLAGS field ***/
    if( cmdOpts->a )      strcat(flagstmp, "A");
    if( cmdOpts->c )      strcat(flagstmp, "C");
    if( cmdOpts->d )      strcat(flagstmp, "D");
    if( cmdOpts->e )      strcat(flagstmp, "E");
    if( cmdOpts->nologo ) strcat(flagstmp, "L");
    if( cmdOpts->n )      strcat(flagstmp, "N");
    if( cmdOpts->p )      strcat(flagstmp, "P");
    if( cmdOpts->r )      strcat(flagstmp, "R");
    if( cmdOpts->s )      strcat(flagstmp, "S");
    if( cmdOpts->u )      strcat(flagstmp, "U");
    if( cmdOpts->y )      strcat(flagstmp, "Y");

    /*** pass builtin macros to wmake, so nmake wrapper gets called in recursive actions ***/
    AppendFmtCmdLine( cmdLine, NMAKE_OPTS_SECTION, "MAKE=\"%s\"", "nmake" );
    AppendFmtCmdLine( cmdLine, NMAKE_OPTS_SECTION, "MAKEDIR=\"%s\"", cwd );
    AppendFmtCmdLine( cmdLine, NMAKE_OPTS_SECTION, "MAKEFLAGS=\"%s\"", flagstmp );

    /*** merge commands ***/
    AppendCmdLine( cmdLine, NMAKE_PROGNAME_SECTION, MAKE );
    args = MergeCmdLine( cmdLine, INVALID_MERGE_CMDLINE );

    /*** Spawn the wmake ***/
    if( cmdOpts->showwopts ) {
        for( count=0; args[count]!=NULL; count++ ) {
            fprintf( stderr, "%s ", args[count] );
        }
        fprintf( stderr, "\n" );
    }
    if( !cmdOpts->noinvoke ) {
        rc = spawnvp( P_WAIT, MAKE, (const char **)args );
        if( rc != 0 ) {
            if( rc == -1  ||  rc == 255 ) {
                FatalError( "Unable to execute '%s'", MAKE );
            } else {
                return( NMAKE_ERROR );
            }
        }
    }
    DestroyCmdLine( cmdLine );

    return( NMAKE_SUCCESS );
}