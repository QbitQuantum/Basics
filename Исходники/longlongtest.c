int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return 1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    TableDef tabDef;
    tabDef.addField("f1", typeLongLong, 0, NULL, true);
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 3; }
    printf("Table created\n");
#ifdef WITHINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
#endif
#ifdef WITHTREEINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = treeIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
#endif
#ifdef WITHTRIEINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = trieIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
#endif


    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return 4; }
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    long long i;
    rv =conn.startTransaction();
    for(i = 0; i< 5; i++)
    {
        if (rv != OK) exit(5);
        id= i;
        strcpy(name, "PRABAKARAN0123456750590");
        ret = table->insertTuple();
        if (ret != 0) break;
    }
    conn.commit();

    conn.startTransaction();
    select(table, OpEquals);
    conn.commit();

    conn.startTransaction();
    select(table, OpNotEquals);
    conn.commit();

    conn.startTransaction();
    select(table, OpLessThan);
    conn.commit();

    conn.startTransaction();
    select( table, OpLessThanEquals);
    conn.commit();

    conn.startTransaction();
    select( table, OpGreaterThan);
    conn.commit();

    conn.startTransaction();
    select( table, OpGreaterThanEquals);
    conn.commit();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}