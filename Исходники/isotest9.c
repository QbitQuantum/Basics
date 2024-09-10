void* runTest2(void *message)
{
    AbsSqlConnection *conn = createConnection();
    DbRetVal rv = conn->connect("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(conn);
# ifdef RDUNCOM
    rv = conn->beginTrans(READ_UNCOMMITTED);
# elif defined RDRPT
    rv = conn->beginTrans(READ_REPEATABLE);
# else
    rv = conn->beginTrans(READ_COMMITTED);
#endif
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());
    while (selectDone != 1) {::sleep(1); }
    p2RetVal = new int();
    *p2RetVal = 0;
    rv = remove(stmt, 100, true);
# ifdef RDUNCOM
    if (rv != OK) {
        printf("Test Failed:second thread failed to remove.\n");
# elif defined RDRPT 
    if (rv == OK) {
        printf("Test Failed:second thread selects.\n");
# else
    if (rv != OK) {
        printf("Test Failed:second thread failed to remove\n"); 
#endif
        *p2RetVal = 1; 
    }
    printf("P2 deleted\n");
    deleteDone =1;
    sleep(5);
    rv = conn->commit();
    printf("P2 committed\n");
    rv = conn->disconnect();
    stmt->free(); delete stmt; delete conn;
    printf("conn closed %d for Thread and pid is %d %lu\n", rv, os::getpid(), os::getthrid());
    pthread_exit(p2RetVal);
}