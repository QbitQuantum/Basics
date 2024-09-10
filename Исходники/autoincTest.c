int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeString, 12);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->isPrimary = true;
    idxInfo->isUnique = true;
#ifdef HASH
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
#endif
#ifdef TREE
    idxInfo->indType = treeIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
#endif
    delete idxInfo;
    pthread_t thr[THREADS];
    int message[THREADS];
    int status;
    for (int i=0; i <THREADS; i++) {
        message[i] = i;
        pthread_create (&thr[i], NULL,
                  &runInsTest, (void *) &message[i]);
    }
    for (int i=0; i <THREADS; i++) {
        pthread_join(thr[i], (void**)&status);
    }
    
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    table->setCondition(NULL);
    rv = conn.startTransaction();
    if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
    table->execute();
    int count=0;
    void *tuple = NULL;
    while ((tuple = (char*) table->fetch())) {
         count++;
    }
    printf("Tuples found: %d\n", count);
    table->closeScan();
    conn.commit();

#ifdef HASH
    Condition p1;
    int valTerm = 0;
    p1.setTerm("f1", OpEquals, &valTerm);
    table->setCondition(&p1);
    int icount=0;
    for(int i = 0; i< THREADS * ITERATION; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        valTerm = i+1;
        rv = table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL)  break;
        icount++;
        table->closeScan();
        conn.commit();
        //if (i%ITERATION == 0) printf("%d\n", i);
    }
    printf("Index Tuples found: %d\n", icount);
#endif



    dbMgr->closeTable(table);

    for (int i=0; i <THREADS; i++) {
        message[i] = i;
        pthread_create (&thr[i], NULL,
                  &runSelTest, (void *) &message[i]);
    }
    for (int i=0; i <THREADS; i++) {
        pthread_join(thr[i], (void**)&status);
    }

    dbMgr->dropTable("t1");
    
    conn.close();
    return 0;
}