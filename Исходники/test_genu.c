int
main(int argc, char **argv) {
   int mode;
   rodsServerConfig_t serverConfig;
   int status;
   rodsEnv myEnv;

   /* remove this call or change to LOG_NOTICE for more verbosity */
   rodsLogLevel(LOG_ERROR);

   /* this will cause the sql to be printed, comment this out to skip it  */
   rodsLogSqlReq(1);

   mode = 0;
   if (strcmp(argv[1],"1")==0) mode=1;
   if (strcmp(argv[1],"2")==0) mode=2;
   if (strcmp(argv[1],"3")==0) mode=3;
   if (strcmp(argv[1],"4")==0) mode=4;
   if (strcmp(argv[1],"5")==0) mode=5;
   if (strcmp(argv[1],"6")==0) mode=6;

   memset((char *)&myEnv, 0, sizeof(myEnv));
   status = getRodsEnv (&myEnv);
   if (status < 0) {
      rodsLog (LOG_ERROR, "main: getRodsEnv error. status = %d",
	       status);
      exit (1);
   }
   
   if (strstr(myEnv.rodsDebug, "CAT") != NULL) {
      chlDebug(myEnv.rodsDebug);
   }

   memset(&serverConfig, 0, sizeof(serverConfig));
   status = readServerConfig(&serverConfig);

   if ((status = chlOpen(serverConfig.DBUsername,
			 serverConfig.DBPassword)) != 0) {
      rodsLog (LOG_SYS_FATAL,
	       "chlopen Error. Status = %d",
	       status);
      return (status);
   }
   if (mode==1) {
      status = doTest1(argv[2], argv[3], argv[4], argv[5]);
      if (status <0) exit(2);
      exit(0);
   }
   if (mode==2) {
      status = doTest2(argv[2], argv[3], argv[4], argv[5]);
      if (status <0) exit(2);
      exit(0);
   }
   if (mode==3) {
      status = doTest3(argv[2], argv[3], argv[4], argv[5]);
      if (status <0) exit(2);
      exit(0);
   }
   if (mode==4) {
      status = doTest4(argv[2], argv[3], argv[4], argv[5]);
      if (status <0) exit(2);
      exit(0);
   }
   if (mode==5) {
      status = doTest5(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
      if (status <0) exit(2);
      exit(0);
   }
   if (mode==6) {
      status = doTest6(argv[2], argv[3], argv[4], argv[5]);
      if (status <0) exit(2);
      exit(0);
   }
   exit(0);
}