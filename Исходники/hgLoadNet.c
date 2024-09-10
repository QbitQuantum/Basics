void loadDatabase(char *database, char *tab, char *track)
/* Load database from tab file. */
{
    struct sqlConnection *conn = sqlConnect(database);
    struct dyString *dy = newDyString(1024);
    /* First make table definition. */
    if (sqlTable != NULL)
    {
        /* Read from file. */
        char *sql, *s;
        readInGulp(sqlTable, &sql, NULL);

        /* Chop of end-of-statement semicolon if need be. */
        s = strchr(sql, ';');
        if (s != NULL) *s = 0;

        sqlRemakeTable(conn, track, sql);
        freez(&sql);
    }
    else if (!oldTable)
    {
        /* Create definition statement. */
        verbose(1, "Creating table definition for %s\n", track);
        sqlDyStringPrintf(dy, "CREATE TABLE %s (\n", track);
        if (!noBin)
            dyStringAppend(dy, "  bin smallint unsigned not null,\n");
        dyStringAppend(dy, "  level int unsigned not null,\n");
        dyStringAppend(dy, "  tName varchar(255) not null,\n");
        dyStringAppend(dy, "  tStart int unsigned not null,\n");
        dyStringAppend(dy, "  tEnd int unsigned not null,\n");
        dyStringAppend(dy, "  strand char(1) not null,\n");
        dyStringAppend(dy, "  qName varchar(255) not null,\n");
        dyStringAppend(dy, "  qStart int unsigned not null,\n");
        dyStringAppend(dy, "  qEnd int unsigned not null,\n");
        dyStringAppend(dy, "  chainId int unsigned not null,\n");
        dyStringAppend(dy, "  ali int unsigned not null,\n");
        dyStringAppend(dy, "  score double not null,\n");
        dyStringAppend(dy, "  qOver int not null, \n");
        dyStringAppend(dy, "  qFar int not null, \n");
        dyStringAppend(dy, "  qDup int not null, \n");
        dyStringAppend(dy, "  type varchar(255) not null,\n");
        dyStringAppend(dy, "  tN int not null, \n");
        dyStringAppend(dy, "  qN int not null, \n");
        dyStringAppend(dy, "  tR int not null, \n");
        dyStringAppend(dy, "  qR int not null, \n");
        dyStringAppend(dy, "  tNewR int not null, \n");
        dyStringAppend(dy, "  qNewR int not null, \n");
        dyStringAppend(dy, "  tOldR int not null, \n");
        dyStringAppend(dy, "  qOldR int not null, \n");
        dyStringAppend(dy, "  tTrf int not null, \n");
        dyStringAppend(dy, "  qTrf int not null, \n");
        dyStringAppend(dy, "#Indices\n");
        if (!noBin)
            dyStringAppend(dy, "  INDEX(tName(16),bin),\n");
        dyStringAppend(dy, "  INDEX(tName(16),tStart)\n");
        dyStringAppend(dy, ")\n");
        sqlRemakeTable(conn, track, dy->string);
    }

    dyStringClear(dy);
    sqlDyStringPrintf(dy, "load data local infile '%s' into table %s", tab, track);
    verbose(1, "Loading %s into %s\n", track, database);
    sqlUpdate(conn, dy->string);
    /* add a comment to the history table and finish up connection */
    hgHistoryComment(conn, "Loaded net table %s", track);
    sqlDisconnect(&conn);
}