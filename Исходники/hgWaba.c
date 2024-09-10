void hgWaba(char *database, char *species, char *chromosome, 
	int chromOffset, int wabaFileCount, char *wabaFile[])
/* hgWaba - load Waba alignments into database. */
{
struct sqlConnection *conn = sqlConnect(database);
FILE *fullTab, *chromTab;
FILE *in;
struct xaAli *xa, *xaList = NULL;
char fullTabName[512], chromTabName[512];
char fullTable[128], chromTable[128];
char *inFile;
int i;
struct dyString *query = newDyString(2048);

/* Loop through each waba file grabbing sequence into
 * memory, then sort. */
for (i = 0; i < wabaFileCount; ++i)
    {
    inFile = wabaFile[i];
    printf("Processing %s\n", inFile);
    in = xaOpenVerify(inFile);

    while ((xa = xaReadNext(in, FALSE)) != NULL)
        {
	xa->tStart += chromOffset;
	xa->tEnd += chromOffset;
	slAddHead(&xaList, xa);
	}
    carefulClose(&in);
    }
printf("Sorting %d alignments by chromosome position\n", slCount(xaList));
slSort(&xaList, xaAliCmpTstart);

/* Create names of tables and the tables themselves. 
 * Clear anything in the chrom table. */
sprintf(fullTable, "waba%s", species);
sprintf(chromTable, "%s_waba%s", chromosome, species);
dyStringClear(query);
sqlDyStringPrintf(query, wabaFullCreate, fullTable);
sqlMaybeMakeTable(conn, fullTable, query->string);
dyStringClear(query);
sqlDyStringPrintf(query, wabaChromCreate, chromTable);
sqlMaybeMakeTable(conn, chromTable, query->string);
if (chromOffset == 0)
    {
    dyStringClear(query);
    sqlDyStringPrintf(query, "DELETE from %s", chromTable);
    sqlUpdate(conn, query->string);
    }

/* Make a temp file for each table we'll update. */
strcpy(fullTabName, "full_waba.tab");
fullTab = mustOpen(fullTabName, "w");
strcpy(chromTabName, "chrom_waba.tab");	
chromTab = mustOpen(chromTabName, "w");

/* Write out tab-delimited files. */
printf("Writing tab-delimited files\n");
for (xa = xaList; xa != NULL; xa = xa->next)
    {
    int squeezedSize;
    squeezedSize = squeezeSym(xa->tSym, xa->hSym, xa->symCount, xa->hSym);
    if( squeezedSize != xa->tEnd - xa->tStart ) {
		printf("%s squeezedSize: %d, tEnd, tStart: %d, %d, diff: %d\n", xa->query, squeezedSize, xa->tEnd, xa->tStart, xa->tEnd - xa->tStart );
        } else {
    fprintf(fullTab, "%s\t%d\t%d\t%c\t%s\t%d\t%d\t%d\t%d\t%s\t%s\t%s\n",
    	/*xa->query, xa->qStart, xa->qEnd, xa->qStrand,*/
    	xa->name, xa->qStart, xa->qEnd, xa->qStrand,
	chromosome, xa->tStart, xa->tEnd,
	xa->milliScore, xa->symCount, 
	xa->qSym, xa->tSym, xa->hSym);
    assert(squeezedSize == xa->tEnd - xa->tStart);
    fprintf(chromTab, "%s\t%d\t%d\t%c\t%d\t%s\n",
        /*xa->query, xa->tStart, xa->tEnd, xa->qStrand,*/
        xa->name, xa->tStart, xa->tEnd, xa->qStrand,
	xa->milliScore, xa->hSym);
        }
    }
fclose(fullTab);
fclose(chromTab);

printf("Loading %s table in %s\n", chromTable, database);
dyStringClear(query);
sqlDyStringPrintf(query, 
   "LOAD data local infile '%s' into table %s", chromTabName, chromTable);
sqlUpdate(conn, query->string);

printf("Loading %s table in %s\n", fullTable, database);
dyStringClear(query);
sqlDyStringPrintf(query, 
   "LOAD data local infile '%s' into table %s", fullTabName, fullTable);
sqlUpdate(conn, query->string);

printf("Done!\n");

// remove(fullTabName);
// remove(chromTabName);
sqlDisconnect(&conn);
freeDyString(&query);
}