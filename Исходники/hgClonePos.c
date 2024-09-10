void saveClonePos(struct clonePos *cloneList, char *database)
/* Save sorted clone position list to database. */
{
    struct sqlConnection *conn = sqlConnect(database);
    struct clonePos *clone;
    struct tempName tn;
    FILE *f;
    struct dyString *ds = newDyString(2048);

    /* Create tab file from clone list. */
    printf("Creating tab file\n");
    makeTempName(&tn, "hgCP", ".tab");
    f = mustOpen(tn.forCgi, "w");
    for (clone = cloneList; clone != NULL; clone = clone->next)
        clonePosTabOut(clone, f);
    fclose(f);

    /* Create table if it doesn't exist, delete whatever is
     * already in it, and fill it up from tab file. */
    printf("Loading clonePos table\n");
    sqlMaybeMakeTable(conn, "clonePos", createClonePos);
    sqlUpdate(conn, "NOSQLINJ DELETE from clonePos");
    sqlDyStringPrintf(ds, "LOAD data local infile '%s' into table clonePos",
                      tn.forCgi);
    sqlUpdate(conn, ds->string);

    /* Clean up. */
    remove(tn.forCgi);
    sqlDisconnect(&conn);
}