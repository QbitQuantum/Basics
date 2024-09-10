int
main(int argc, char **argv) {
    int status;
    rodsEnv myEnv;
    rErrMsg_t errMsg;
    rcComm_t *conn;
    rodsArguments_t myRodsArgs;
    char *optStr;
    rodsPathInp_t rodsPathInp;
    int i, nArgs;
    modAccessControlInp_t modAccessControl;
    char userName[NAME_LEN];
    char zoneName[NAME_LEN];
    int doingInherit;
    char rescAccessLevel[LONG_NAME_LEN];
    char adminModeAccessLevel[LONG_NAME_LEN];

    optStr = "RrhvVM";
   
    status = parseCmdLineOpt (argc, argv, optStr, 0, &myRodsArgs);
    if (status) {
       printf("Use -h for help\n");
       exit(1);
    }
    if (myRodsArgs.help==True) {
       usage();
       exit(0);
    }

    if (status < 0) {
        rodsLogError (LOG_ERROR, status, "main: parseCmdLineOpt error. ");
	printf("Use -h for help\n");
        exit (2);
    }

    nArgs = argc - myRodsArgs.optind;

    if (nArgs < 2) {usage(); exit(3);}

    status = getRodsEnv (&myEnv);

    if (status < 0) {
        rodsLogError(LOG_ERROR, status, "main: getRodsEnv error. ");
        exit (3);
    }

    optind=myRodsArgs.optind + 2;
    doingInherit=0;
    if (strcmp(argv[myRodsArgs.optind], ACCESS_INHERIT) == 0 ||
	strcmp(argv[myRodsArgs.optind], ACCESS_NO_INHERIT) == 0 ) {
       doingInherit=1;
       optind=myRodsArgs.optind + 1;
    }

    status = parseCmdLinePath (argc, argv, optind, &myEnv,
      UNKNOWN_OBJ_T, NO_INPUT_T, 0, &rodsPathInp);

    if (status < 0) {
        rodsLogError (LOG_ERROR, status, "main: parseCmdLinePath error. ");
	usage ();
        exit (4);
    }

    conn = rcConnect (myEnv.rodsHost, myEnv.rodsPort, myEnv.rodsUserName,
      myEnv.rodsZone, 0, &errMsg);

    if (conn == NULL) {
        exit (5);
    }
   
    status = clientLogin(conn);
    if (status != 0) {
        rcDisconnect(conn);
        exit (6);
    }

    modAccessControl.recursiveFlag = myRodsArgs.recursive;
    modAccessControl.accessLevel = argv[myRodsArgs.optind];

    if (doingInherit) {
       modAccessControl.userName = "";
       modAccessControl.zone = "";
    }
    else {
       status = parseUserName(argv[myRodsArgs.optind+1], userName, zoneName);
       if (status != 0) {
	  printf("Invalid iRODS user name format: %s\n",
		 argv[myRodsArgs.optind+1]);
	  exit(7);
       }
    }
    modAccessControl.userName = userName;
    modAccessControl.zone = zoneName;
    for (i = 0; i < rodsPathInp.numSrc && status==0; i++) {
       if (rodsPathInp.numSrc > 1 && myRodsArgs.verbose!=0) {
	  printf("path %s\n",rodsPathInp.srcPath[i].outPath);
       }
       modAccessControl.path = rodsPathInp.srcPath[i].outPath;

       if (myRodsArgs.resource) {
	  strncpy(rescAccessLevel, MOD_RESC_PREFIX, LONG_NAME_LEN);
	  strncat(rescAccessLevel, argv[myRodsArgs.optind], LONG_NAME_LEN);
	  modAccessControl.accessLevel = rescAccessLevel; /* indicate resource*/
	  modAccessControl.path = argv[optind]; /* just use the plain name */
       }
       if (myRodsArgs.admin && i==0) {    /* admin mode, add indicator */
	  strncpy(adminModeAccessLevel, MOD_ADMIN_MODE_PREFIX, LONG_NAME_LEN);
	  strncat(adminModeAccessLevel, modAccessControl.accessLevel,
		  LONG_NAME_LEN);
	  modAccessControl.accessLevel = adminModeAccessLevel;
       }
       status = rcModAccessControl(conn, &modAccessControl);
       if (status < 0) {
	  rodsLogError(LOG_ERROR, status, "rcModAccessControl failure %s",
		       errMsg.msg);
	  if (conn->rError) {
	     rError_t *Err;
	     rErrMsg_t *ErrMsg;
	     int i, len;
	     Err = conn->rError;
	     len = Err->len;
	     for (i=0;i<len;i++) {
		ErrMsg = Err->errMsg[i];
		rodsLog(LOG_ERROR, "Level %d: %s",i, ErrMsg->msg);
	     }
	  }
       }
    }

    printErrorStack(conn->rError);

    rcDisconnect(conn);

    if (status < 0) {
	exit (8);
    } else {
        exit(0);
    }

}