void* print_message_function(void *ptr)
{
    //if (flag == 0) {flag =1; sleep(2); }
    char tblname[20];
    sprintf(tblname, "T%d", *(int*)ptr );
    Connection conn;
    DbRetVal rv=conn.open("root","manager");
    printf("Thread Return value of open %d %d\n", rv, getpid());
    if(rv!=OK)
    {
      return NULL;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}


    TableDef tabDef;
    tabDef.addField("f1", typeInt);
    tabDef.addField("f2", typeInt);
    rv = dbMgr->createTable(tblname, tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return NULL; }
    printf("Table created\n");

    rv = conn.close();
    printf("Thread Return value of close %d %d\n", rv, getpid());
}