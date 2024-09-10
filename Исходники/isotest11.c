int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return 1; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    int ret = createTable(dbMgr);
    if (ret != 0) { return 1; }

    pthread_t thr[2];
    int *status1, *status2;
    pthread_create (&thr[0], NULL, &runTest1,  NULL);
    pthread_create (&thr[1], NULL, &runTest2,  NULL);
    printf("All threads started\n");

    pthread_join(thr[0], (void**)&status1);
    pthread_join(thr[1], (void**)&status2);
    ret = 0;
    if (*status1 != 0 || *status2 != 0) ret = 1;
    if (p1RetVal) { delete p1RetVal; p1RetVal = NULL; }
    if (p2RetVal) { delete p2RetVal; p2RetVal = NULL; }
    dbMgr->dropTable("t1");
    conn.close();
    return ret;
}