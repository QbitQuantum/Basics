static void loadDatabase(char *database, char *track, int bedSize, struct bedStub *bedList)
/* Load database from bedList. */
{
struct sqlConnection *conn;
struct dyString *dy = newDyString(1024);
char *tab = (char *)NULL;
int loadOptions = (optionExists("onServer") ? SQL_TAB_FILE_ON_SERVER : 0);

if ( ! noLoad )
    conn = sqlConnect(database);

if ((char *)NULL != tmpDir)
    tab = cloneString(rTempName(tmpDir,"loadBed",".tab"));
else
    tab = cloneString("bed.tab");

if (bedDetail && sqlTable == NULL) 
    errAbort("bedDetail format requires sqlTable option");
if (bedDetail && !strictTab) 
    errAbort("bedDetail format must be tab separated");
if (bedDetail && !noBin) 
    noBin = TRUE;

/* First make table definition. */
if (sqlTable != NULL && !oldTable)
    {
    /* Read from file. */
    char *sql, *s;
    readInGulp(sqlTable, &sql, NULL);
    /* Chop off end-of-statement semicolon if need be. */
    s = strchr(sql, ';');
    if (s != NULL) *s = 0;
    
    if ( !noLoad )
        {
        if (renameSqlTable)
            {
            char *pos = stringIn("CREATE TABLE ", sql);
            if (pos == NULL)
                errAbort("Can't find CREATE TABLE in %s\n", sqlTable);
            char *oldSql = cloneString(sql);
            nextWord(&pos); nextWord(&pos);
            char *tableName = nextWord(&pos);
            sql = replaceChars(oldSql, tableName, track);
            }
        verbose(1, "Creating table definition for %s\n", track);
        sqlRemakeTable(conn, track, sql);
        if (!noBin) 
	    addBinToEmptyTable(conn, track);
	adjustSqlTableColumns(conn, track, bedSize);
	}
    
    freez(&sql);
    }
else if (!oldTable)
    {
    int minLength;

    if (noLoad)
	minLength=6;
    else if (maxChromNameLength)
	minLength = maxChromNameLength;
    else
	minLength = hGetMinIndexLength(database);
    verbose(2, "INDEX chrom length: %d\n", minLength);

    /* Create definition statement. */
    verbose(1, "Creating table definition for %s\n", track);
    dyStringPrintf(dy, "CREATE TABLE %s (\n", track);
    if (!noBin)
       dyStringAppend(dy, "  bin smallint unsigned not null,\n");
    dyStringAppend(dy, "  chrom varchar(255) not null,\n");
    dyStringAppend(dy, "  chromStart int unsigned not null,\n");
    dyStringAppend(dy, "  chromEnd int unsigned not null,\n");
    if (bedSize >= 4)
       maybeBedGraph(4, dy, "  name varchar(255) not null,\n");
    if (bedSize >= 5)
	{
	if (allowNegativeScores)
	    maybeBedGraph(5, dy, "  score int not null,\n");
	else
	    maybeBedGraph(5, dy, "  score int unsigned not null,\n");
	}
    if (bedSize >= 6)
       maybeBedGraph(6, dy, "  strand char(1) not null,\n");
    if (bedSize >= 7)
       maybeBedGraph(7, dy, "  thickStart int unsigned not null,\n");
    if (bedSize >= 8)
       maybeBedGraph(8, dy, "  thickEnd int unsigned not null,\n");
    /*	As of 2004-11-22 the reserved field is used as itemRgb in code */
    if (bedSize >= 9)
       maybeBedGraph(9, dy, "  reserved int unsigned  not null,\n");
    if (bedSize >= 10)
       maybeBedGraph(10, dy, "  blockCount int unsigned not null,\n");
    if (bedSize >= 11)
       maybeBedGraph(11, dy, "  blockSizes longblob not null,\n");
    if (bedSize >= 12)
       maybeBedGraph(12, dy, "  chromStarts longblob not null,\n");
    if (bedSize >= 13)
       maybeBedGraph(13, dy, "  expCount int unsigned not null,\n");
    if (bedSize >= 14)
       maybeBedGraph(14, dy, "  expIds longblob not null,\n");
    if (bedSize >= 15)
       maybeBedGraph(15, dy, "  expScores longblob not null,\n");
    dyStringAppend(dy, "#Indices\n");
    if (nameIx && (bedSize >= 4) && (0 == bedGraph))
       dyStringAppend(dy, "  INDEX(name(16)),\n");
    if (noBin)
	{
	dyStringPrintf(dy, "  INDEX(chrom(%d),chromStart)\n", minLength);
	}
    else
	{
        dyStringPrintf(dy, "  INDEX(chrom(%d),bin)\n", minLength);
	}
    dyStringAppend(dy, ")\n");
    if (noLoad)
	verbose(2,"%s", dy->string);
    else
	sqlRemakeTable(conn, track, dy->string);
    }

verbose(1, "Saving %s\n", tab);
writeBedTab(tab, bedList, bedSize);

if ( ! noLoad )
    {
    verbose(1, "Loading %s\n", database);
    if (customTrackLoader)
	sqlLoadTabFile(conn, tab, track, loadOptions|SQL_TAB_FILE_WARN_ON_WARN);
    else
	sqlLoadTabFile(conn, tab, track, loadOptions);

    if (! noHistory)
	{
	char comment[256];
	/* add a comment to the history table and finish up connection */
	safef(comment, sizeof(comment),
	    "Add %d element(s) from bed list to %s table",
		slCount(bedList), track);
	hgHistoryComment(conn, comment);
	}
    if(fillInScoreColumn != NULL)
        {
        char query[500];
        char buf[500];
        struct sqlResult *sr;
        safef(query, sizeof(query), "select sum(score) from %s", track);
        if(sqlQuickQuery(conn, query, buf, sizeof(buf)))
            {
            unsigned sum = sqlUnsigned(buf);
            if (!sum)
                {
                safef(query, sizeof(query), "select min(%s), max(%s) from %s", fillInScoreColumn, fillInScoreColumn, track);
                if ((sr = sqlGetResult(conn, query)) != NULL)
                    {
                    char **row = sqlNextRow(sr);
                    if(row != NULL)
                        {
                        float min = sqlFloat(row[0]);
                        float max = sqlFloat(row[1]);
			if ( !(max == -1 && min == -1)) // if score is -1 then ignore, as if it werent present
			    {
			    if (max == min || sameString(row[0],row[1])) // this will lead to 'inf' score value in SQL update causing an error
				errAbort("Could not set score in table %s max(%s)=min(%s)=%s\n", track, fillInScoreColumn, fillInScoreColumn, row[0]);
                            sqlFreeResult(&sr);

			    // Calculate a, b s/t f(x) = ax + b maps min-max => minScore-1000
			    float a = (1000-minScore) / (max - min);
			    float b = 1000 - ((1000-minScore) * max) / (max - min);

			    safef(query, sizeof(query), "update %s set score = round((%f * %s) + %f)",  track, a, fillInScoreColumn, b);
			    int changed = sqlUpdateRows(conn, query, NULL);
			    verbose(2, "update query: %s; changed: %d\n", query, changed);
			    }
			else
			    {
                            sqlFreeResult(&sr);
			    verbose(2, "score not updated; all values for column %s are -1\n", fillInScoreColumn);
			    }
			}
                    }
                }
            }

        }
    sqlDisconnect(&conn);
    /*	if temp dir specified, unlink file to make it disappear */
    if ((char *)NULL != tmpDir)
	unlink(tab);
    }
else
    verbose(1, "No load option selected, see file: %s\n", tab);

}	/*	static void loadDatabase()	*/