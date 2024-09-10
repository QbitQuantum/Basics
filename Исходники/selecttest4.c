int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;

    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];

    strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT);");
    if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT)");

    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
        delete stmt;
        delete con;
        return 1;
    }

    rv  = stmt->execute(rows);
    if(rv!=OK)
    {
        delete stmt;
        delete con;
        return 2;
    }
    stmt->free();
    printf("Table created\n");
    con->commit();
//  insert records

    strcpy(statement,"INSERT INTO t1 VALUES(?,?);");
    if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"INSERT INTO t1 VALUES(?,?)");

    int f1var = 1;
    int  f2var= 110;

    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
        delete stmt;
        delete con;
        return 3;
    }

    int count=0;

    for(int i=0; i<2; i++)
    {

        for(int j=0; j<5; j++)
        {
            f1var = j;
            rv = con->beginTrans();
            if(rv!=OK)break;


            stmt->setIntParam(1,f1var);
            stmt->setIntParam(2,f2var);

            rv = stmt->execute(rows);
            if(rv!=OK)break;
            rv = con->commit();
            if(rv!=OK)break;
            count++;
        }
        printf("%d rows inserted\n",count);
    }
    stmt->free();

//*******************************************

    strcpy(statement,"SELECT F3 ,f2  FROM t1;");
    if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"SELECT F3 ,f2  FROM t1");
    rv = stmt->prepare(statement);

    if(rv !=OK)
    {
        printf("Test script passed\n");

        strcpy(statement,"DROP TABLE t1;");
        if(strcmp(getenv("DSN"),"db2")==0)
            strcpy(statement,"DROP TABLE t1");
        rv = stmt->prepare(statement);
        rv = stmt->execute(rows);
        if(rv==OK)printf("Table dropped\n");
        con->commit();
        stmt->free();
        delete stmt;
        delete con;
        return 0;
    }
    else
    {
        if(strcmp(getenv("DSN"),"oracle")==0 || strcmp(getenv("DSN"),"psql")==0 || strcmp(getenv("DSN"),"sybase")==0 )
        {
            printf("Test script Passed\n");
            strcpy(statement,"DROP TABLE t1;");
            if(strcmp(getenv("DSN"),"db2")==0)
                strcpy(statement,"DROP TABLE t1");
            rv = stmt->prepare(statement);
            rv = stmt->execute(rows);
            if(rv==OK) {
                printf("Table dropped\n");
            }
            stmt->free();
            con->commit();
            delete stmt;
            delete con;
            return 0;
        }
        else
        {
            printf("Test script failed\n");
            strcpy(statement,"DROP TABLE t1;");
            if(strcmp(getenv("DSN"),"db2")==0)
                strcpy(statement,"DROP TABLE t1");
            rv = stmt->prepare(statement);
            rv = stmt->execute(rows);
            if(rv==OK)printf("Table dropped\n");
            con->commit();
            stmt->free();
            delete stmt;
            delete con;
            return 4;
        }
    }
}