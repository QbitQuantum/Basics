int
main( int argc, char **argv ) {
    int status;
    rodsEnv myEnv;
    rErrMsg_t errMsg;
    rcComm_t *conn;
    rodsArguments_t myRodsArgs;
    char *optStr, buffer[HUGE_NAME_LEN], hostname[LONG_NAME_LEN];
    objType_t srcType;
    rodsPathInp_t rodsPathInp;

    optStr = "hr";

    status = parseCmdLineOpt( argc, argv, optStr, 0, &myRodsArgs );

    if ( status < 0 ) {
        printf( "Use -h for help\n" );
        exit( 1 );
    }
    if ( myRodsArgs.help == True ) {
        usage();
        exit( 0 );
    }

    status = getRodsEnv( &myEnv );

    if ( status < 0 ) {
        rodsLogError( LOG_ERROR, status, "main: getRodsEnv error. " );
        exit( 1 );
    }

    if ( strcmp( argv[argc - 1], "i:" ) == 0 ) {
        srcType = UNKNOWN_OBJ_T;
        strcpy( argv[argc - 1], "." );
    }
    else if ( strncmp( argv[argc - 1], "i:", 2 ) == 0 ) {
        srcType = UNKNOWN_OBJ_T;
        snprintf( buffer, sizeof( buffer ), "%s", argv[argc - 1] + 2 );
        argv[argc - 1] = buffer;
    }
    else {
        srcType = UNKNOWN_FILE_T;
    }

    status = parseCmdLinePath( argc, argv, optind, &myEnv,
                               srcType, NO_INPUT_T, 0, &rodsPathInp );

    if ( status < 0 ) {
        rodsLogError( LOG_ERROR, status, "main: parseCmdLinePath error. " );
        usage();
        exit( 1 );
    }

    // =-=-=-=-=-=-=-
    // initialize pluggable api table
    irods::pack_entry_table& pk_tbl  = irods::get_pack_table();
    irods::api_entry_table&  api_tbl = irods::get_client_api_table();
    init_api_table( api_tbl, pk_tbl );

    conn = rcConnect( myEnv.rodsHost, myEnv.rodsPort, myEnv.rodsUserName,
                      myEnv.rodsZone, 0, &errMsg );

    if ( conn == NULL ) {
        exit( 2 );
    }

    if ( strcmp( myEnv.rodsUserName, PUBLIC_USER_NAME ) != 0 ) {
        status = clientLogin( conn );
        if ( status != 0 ) {
            rcDisconnect( conn );
            exit( 7 );
        }
    }

    status = gethostname( hostname, LONG_NAME_LEN );
    if ( status < 0 ) {
        printf( "cannot resolve server name, aborting!\n" );
        exit( 4 );
    }

    status = scanObj( conn, &myRodsArgs, &rodsPathInp, hostname );

    printErrorStack( conn->rError );
    rcDisconnect( conn );

    exit( status );

}