int main()
{

    AbsSqlConnection *conn = createConnection();
    DbRetVal rv = conn->connect("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return 1; }
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(conn);

    char statement[1024]="create table t1 (f1 int, f2 char(196), primary key(f1));";
    int ret = executeDdlQuery(conn, stmt, statement);
    if (ret != 0) { return 1; }
    pthread_t thr[2];
    int *status1, *status2;
    pthread_create (&thr[0], NULL, &runTest1,  NULL);
    pthread_create (&thr[1], NULL, &runTest2,  NULL);
    printf("All threads started\n");

    pthread_join(thr[0], (void**)&status1);
    pthread_join(thr[1], (void**)&status2);
    strcpy(statement, "drop table t1;");
    ret = executeDdlQuery(conn, stmt, statement);
    if (ret != 0) { return 1; }
    conn->disconnect();
    stmt->free(); delete stmt; delete conn;
    if (*status1 != 0 || *status2 != 0) return 1;
    if (p1RetVal) { delete p1RetVal; p1RetVal = NULL; }
    if (p2RetVal) { delete p2RetVal; p2RetVal = NULL; }
    return 0;
}