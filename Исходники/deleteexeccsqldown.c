int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = SqlFactory :: createConnection(CSqlGateway);
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;

    AbsSqlStatement *stmt = SqlFactory :: createStatement(CSqlGateway);
    stmt->setConnection(con);
    char statement[200];

    strcpy(statement,"delete from t1 where f1 = 10;");
    int rows=0;
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    sleep(15);
    con->commit();
    stmt->free();
    printf("csql down: delete from t1(cached table) success\n");
    
    strcpy(statement,"delete from t2 where f1 = 10;");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: delete from t2(not cached mysql table) failed\n"); delete stmt; delete con; return 4; }
    printf("csql down: delete from t2(not cached mysql table) success\n");
    con->commit();
    stmt->free();

    strcpy(statement,"delete from t3 where f1 = 10;");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { printf("csql down: delete from t3(not cached csql table) failed\n"); delete stmt; delete con; return 5; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: delete from t3(not cached csql table) failed\n"); delete stmt; delete con; return 6; }
    printf("csql down: delete from t3(not cached csql table) success\n");
    con->commit();
    
    stmt->free();
    
    delete stmt;
    delete con;
    return 0;
}