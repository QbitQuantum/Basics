int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con= createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 TINYINT,F10 BIGINT, F11 VARCHAR(20));");
    int rows = 0;
    rv = stmt->prepare(statement);
    if(rv!=OK) {
        delete stmt;
        delete con;
        return 2;
    }
    rv = stmt->execute(rows);
    if(rv!=OK) {
        delete stmt;
        delete con;
        return 3;
    }
    stmt->free();
    printf("Table created\n");
    // insert into table
    strcpy(statement,"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?,?);");
    int f1var = 100;
    short int f2var = 10;
    char f3var[32]="jitendra";
    float f4var = 5.5;
    float f5var = 10.50;
    Date f6var;
    f6var.set(2007,01,21);
    Time f7var;
    f7var.set(12,29,30);
    TimeStamp f8var;
    f8var.setDate(2007,01,21);
    f8var.setTime(12,29,30);
    char f9var = 20;
    long long f10var = 12000;
    char f11var[20]="Aa1Bb2Cc3Dd4";
    rv = stmt->prepare(statement);
    if(rv!=OK) {
        delete stmt;
        delete con;
        return 4;
    }
//****************************************************************************
    int nop;
    nop = stmt->noOfParamFields();
    printf("noOfParamField Returns=%d\n",nop);
    //getParamFldInfo()
    FieldInfo *field = new FieldInfo();
    char fldName[20];
    DataType type;
    size_t length;
    int offset;
    char defaultValueBuf[10];
    bool isNull;
    bool isDefault;
    for(int i=1; i<=11; i++) {
        printf("\n***********************************************\n");
        printf("%d FIELD INFORMATION ::\n",i);;
        rv = stmt->getParamFldInfo(i,field);
        if(rv!=OK) {
            delete stmt;
            delete con;
            return 1;
        }
        printf("Field Name :%s\n", field->fldName);
        printf("Data type of the field :%d\n",field->type);
        printf("length of the field :%d\n",field->length);
        printf("Offset :%d\n",field->offset);
        printf("Default value :%s\n",field->defaultValueBuf);
        printf("Null field :%d\n",field->isNull);
        printf("Default value :%d\n",field->isDefault);
        printf("***********************************************\n");
    }
    delete field;
    int count=0;
    for(int i=0; i<10; i++) {
        rv = con->beginTrans();
        if (rv!=OK) break;
        f1var=i;
        stmt->setIntParam(1,f1var);
        stmt->setShortParam(2,f2var);
        stmt->setStringParam(3,f3var);
        stmt->setFloatParam(4,f4var);
        stmt->setFloatParam(5,f5var);
        stmt->setDateParam(6,f6var);
        stmt->setTimeParam(7,f7var);
        stmt->setTimeStampParam(8,f8var);
        stmt->setByteIntParam(9,f9var);
        stmt->setLongLongParam(10,f10var);
        stmt->setStringParam(11,f11var);
        rv = stmt->execute(rows);
        if(rv!=OK)break;
        rv = con->commit();
        if(rv!=OK)break;
        count++;
    }
    printf("Total rows inserted %d\n",count);
    stmt->free();
    //**********************************************************
    // SELECT * FROM T1;
    strcpy(statement,"SELECT * FROM T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) {
        delete stmt;
        delete con;
        return 5;
    }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,&f5var);
    stmt->bindField(6,&f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,f11var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
        printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld |F11=%s \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var,f11var);
        count++;
    }
    stmt->close();
    rv = con->commit();
    if(rv !=OK) {
        delete stmt;
        delete con;
        return 7;
    }
    printf("Total row fetched=%d\n",count);
    stmt->free();
    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) {
        delete stmt;
        delete con;
        return 8;
    }
    rv = stmt->execute(rows);
    if(rv!=OK) {
        delete stmt;
        delete con;
        return 9;
    }
    printf("Table dropped\n");
    stmt->free();
    delete stmt;
    delete con;
    return 0;
}