int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv !=OK) {
        delete con;
        return 1;
    }
    printf("Connection opened\n");
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
//Creating Table
    char statement[400];
    printf("CREATE TABLE t1(f1 TINYINT DEFAULT 1,f2 SMALLINT DEFAULT 11,f3 INT DEFAULT 111,f4 BIGINT DEFAULT 1111,f5 CHAR(20) DEFAULT 'CSQL1',f6 VARCHAR(30) DEFAULT 'Lakshya1',f7 FLOAT DEFAULT 11.11,f8 DOUBLE DEFAULT 1111.11,f9 DATE DEFAULT '2001-01-01',f10 TIME DEFAULT '01:01:01',f11 TIMESTAMP DEFAULT '2001-01-01 01:01:01');\n");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT DEFAULT 1,f2 SMALLINT DEFAULT 11,f3 INT DEFAULT 111,f4 BIGINT DEFAULT 1111,f5 CHAR(20) DEFAULT 'CSQL1',f6 VARCHAR(30) DEFAULT 'Lakshya1',f7 FLOAT DEFAULT 11.11,f8 DOUBLE DEFAULT 1111.11,f9 DATE DEFAULT '2001-01-01',f10 TIME DEFAULT '01:01:01',f11 TIMESTAMP DEFAULT '2001-01-01 01:01:01');");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Inserting Records
    con->beginTrans();
    rows=0;
    printf("INSERT INTO t1(f1) VALUES(1);\n");
    stmt->prepare("INSERT INTO t1(f1) VALUES(1);");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(2,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);\n");
    stmt->prepare("INSERT INTO t1 VALUES(2,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(NULL,33,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);\n");
    stmt->prepare("INSERT INTO t1 VALUES(NULL,33,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    char f1var;
    short int f2var;
    int f3var;
    long long f4var;
    char f5var[20];
    char f6var[30];
    float f7var;
    double f8var;
    Date f9var;
    Time f10var;
    TimeStamp f11var;
    
//Fetching records after insert
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 6; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,&f11var);
    int count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 7;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(varchar)=NULL | ");
        else printf("f6(varchar)=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(float)=NULL | ");
        else printf("f7(float)=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(double)=NULL | ");
        else printf("f8(double)=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9(date)=NULL | ");
        else printf("f9(date)=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10(time)=NULL | ");
        else printf("f10(time)=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11(timestamp)=NULL | ");
        else printf("f11(timestamp)=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
//Updating Default fields to NULL
    con->beginTrans();
    strcpy(statement,"UPDATE t1 SET f1=NULL,f2=NULL,f3=NULL,f4=NULL,f5=NULL,f6=NULL,f7=NULL,f8=NULL,f9=NULL,f10=NULL,f11=NULL where f1=1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    printf("Prepared\n");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }
    printf("Executed\n");
    con->commit();
    stmt->free();

//Fetching records after Update
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 10; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,&f11var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 11;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(varchar)=NULL | ");
        else printf("f6(varchar)=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(float)=NULL | ");
        else printf("f7(float)=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(double)=NULL | ");
        else printf("f8(double)=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9(date)=NULL | ");
        else printf("f9(date)=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10(time)=NULL | ");
        else printf("f10(time)=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11(timestamp)=NULL | ");
        else printf("f11(timestamp)=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
//Droping table
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }
    printf("Table dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}