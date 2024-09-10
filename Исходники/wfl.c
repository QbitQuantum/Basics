static int tool_exec( tool_type utl, char *p1, char *p2 )
/*******************************************************/
{
    int     rc;
    
    FindToolPath( utl );
    if( !Flags.quiet ) {
        fputs( "\t", stdout );
        fputs( tools[utl].name, stdout );
        fputs( " ", stdout );
        fputs( p1, stdout );
        if( p2 != NULL ) {
            fputs( " ", stdout );
            fputs( p2, stdout );
        }
        fputs( "\n", stdout );
    }
    fflush( NULL );
    if( p2 == NULL ) {
        rc = spawnlp( P_WAIT, tools[utl].path, tools[utl].name, p1, NULL );
    } else {
        rc = spawnlp( P_WAIT, tools[utl].path, tools[utl].name, p1, p2, NULL );
    }
    if( rc != 0 ) {
        if( (rc == -1) || (rc == 255) ) {
            if( utl == TYPE_LINK ) {
                PrintMsg( CL_UNABLE_TO_INVOKE_LINKER );
            } else if( utl == TYPE_PACK ) {
                PrintMsg( CL_UNABLE_TO_INVOKE_CVPACK );
            } else {
                PrintMsg( CL_UNABLE_TO_INVOKE_COMPILER );
            }
        } else {
            if( utl == TYPE_LINK ) {
                PrintMsg( CL_BAD_LINK );
            } else if( utl == TYPE_PACK ) {
                PrintMsg( CL_BAD_LINK );
            } else {
                PrintMsg( CL_BAD_COMPILE, p1 );
            }
        }
    }
    return( rc );
}