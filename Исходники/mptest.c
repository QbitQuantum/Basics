int sqlite_test()
{
  const char *zClient;
  int iClient;
  int n, i;
  int openFlags = SQLITE_OPEN_READWRITE;
  int rc;
  char *zScript;
  int taskId;
  const char *zTrace;
  const char *zCOption;

  g.argv0 = argv[0];
  g.iTrace = 1;
  if( argc<2 ) usage(argv[0]);
  g.zDbFile = argv[1];
  if( strglob("*.test", g.zDbFile) ) usage(argv[0]);
  if( strcmp(sqlite3_sourceid(), SQLITE_SOURCE_ID)!=0 ){
    fprintf(stderr, "SQLite library and header mismatch\n"
                    "Library: %s\n"
                    "Header:  %s\n",
                    sqlite3_sourceid(), SQLITE_SOURCE_ID);
    exit(1);
  }
  n = argc-2;
  sqlite3_snprintf(sizeof(g.zName), g.zName, "%05d.mptest", GETPID());
  g.zVfs = findOption(argv+2, &n, "vfs", 1);
  zClient = findOption(argv+2, &n, "client", 1);
  g.zErrLog = findOption(argv+2, &n, "errlog", 1);
  g.zLog = findOption(argv+2, &n, "log", 1);
  zTrace = findOption(argv+2, &n, "trace", 1);
  if( zTrace ) g.iTrace = atoi(zTrace);
  if( findOption(argv+2, &n, "quiet", 0)!=0 ) g.iTrace = 0;
  g.bSqlTrace = findOption(argv+2, &n, "sqltrace", 0)!=0;
  g.bSync = findOption(argv+2, &n, "sync", 0)!=0;
  if( g.zErrLog ){
    g.pErrLog = fopen(g.zErrLog, "a");
  }else{
    g.pErrLog = stderr;
  }
  if( g.zLog ){
    g.pLog = fopen(g.zLog, "a");
  }else{
    g.pLog = stdout;
  }
  
  sqlite3_config(SQLITE_CONFIG_LOG, sqlErrorCallback, 0);
  if( zClient ){
    iClient = atoi(zClient);
    if( iClient<1 ) fatalError("illegal client number: %d\n", iClient);
    sqlite3_snprintf(sizeof(g.zName), g.zName, "%05d.client%02d",
                     GETPID(), iClient);
  }else{
    if( g.iTrace>0 ){
      printf("With SQLite " SQLITE_VERSION " " SQLITE_SOURCE_ID "\n" );
      for(i=0; (zCOption = sqlite3_compileoption_get(i))!=0; i++){
        printf("-DSQLITE_%s\n", zCOption);
      }
      fflush(stdout);
    }
    iClient =  0;
    unlink(g.zDbFile);
    openFlags |= SQLITE_OPEN_CREATE;
  }
  rc = sqlite3_open_v2(g.zDbFile, &g.db, openFlags, g.zVfs);
  if( rc ) fatalError("cannot open [%s]", g.zDbFile);
  sqlite3_enable_load_extension(g.db, 1);
  sqlite3_busy_handler(g.db, busyHandler, 0);
  sqlite3_create_function(g.db, "vfsname", 0, SQLITE_UTF8, 0,
                          vfsNameFunc, 0, 0);
  sqlite3_create_function(g.db, "eval", 1, SQLITE_UTF8, 0,
                          evalFunc, 0, 0);
  g.iTimeout = DEFAULT_TIMEOUT;
  if( g.bSqlTrace ) sqlite3_trace(g.db, sqlTraceCallback, 0);
  if( !g.bSync ) trySql("PRAGMA synchronous=OFF");
  if( iClient>0 ){
    if( n>0 ) unrecognizedArguments(argv[0], n, argv+2);
    if( g.iTrace ) logMessage("start-client");
    while(1){
      char *zTaskName = 0;
      rc = startScript(iClient, &zScript, &taskId, &zTaskName);
      if( rc==SQLITE_DONE ) break;
      if( g.iTrace ) logMessage("begin %s (%d)", zTaskName, taskId);
      runScript(iClient, taskId, zScript, zTaskName);
      if( g.iTrace ) logMessage("end %s (%d)", zTaskName, taskId);
      finishScript(iClient, taskId, 0);
      sqlite3_free(zTaskName);
      sqlite3_sleep(10);
    }
    if( g.iTrace ) logMessage("end-client");
  }else{
    sqlite3_stmt *pStmt;
    int iTimeout;
    if( n==0 ){
      fatalError("missing script filename");
    }
    if( n>1 ) unrecognizedArguments(argv[0], n, argv+2);
    runSql(
      "CREATE TABLE task(\n"
      "  id INTEGER PRIMARY KEY,\n"
      "  name TEXT,\n"
      "  client INTEGER,\n"
      "  starttime DATE,\n"
      "  endtime DATE,\n"
      "  script TEXT\n"
      ");"
      "CREATE INDEX task_i1 ON task(client, starttime);\n"
      "CREATE INDEX task_i2 ON task(client, endtime);\n"
      "CREATE TABLE counters(nError,nTest);\n"
      "INSERT INTO counters VALUES(0,0);\n"
      "CREATE TABLE client(id INTEGER PRIMARY KEY, wantHalt);\n"
    );
    zScript = readFile(argv[2]);
    if( g.iTrace ) logMessage("begin script [%s]\n", argv[2]);
    runScript(0, 0, zScript, argv[2]);
    sqlite3_free(zScript);
    if( g.iTrace ) logMessage("end script [%s]\n", argv[2]);
    waitForClient(0, 2000, "during shutdown...\n");
    trySql("UPDATE client SET wantHalt=1");
    sqlite3_sleep(10);
    g.iTimeout = 0;
    iTimeout = 1000;
    while( ((rc = trySql("SELECT 1 FROM client"))==SQLITE_BUSY
        || rc==SQLITE_ROW) && iTimeout>0 ){
      sqlite3_sleep(10);
      iTimeout -= 10;
    }
    sqlite3_sleep(100);
    pStmt = prepareSql("SELECT nError, nTest FROM counters");
    iTimeout = 1000;
    while( (rc = sqlite3_step(pStmt))==SQLITE_BUSY && iTimeout>0 ){
      sqlite3_sleep(10);
      iTimeout -= 10;
    }
    if( rc==SQLITE_ROW ){
      g.nError += sqlite3_column_int(pStmt, 0);
      g.nTest += sqlite3_column_int(pStmt, 1);
    }
    sqlite3_finalize(pStmt);
  }
  sqlite3_close(g.db);  
  maybeClose(g.pLog);
  maybeClose(g.pErrLog);
  if( iClient==0 ){
    printf("Summary: %d errors in %d tests\n", g.nError, g.nTest);
  }
  return g.nError>0;
}