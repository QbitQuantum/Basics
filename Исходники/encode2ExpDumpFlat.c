void encode2ExpDumpFlat(char *outFile, char *viewSql, char *flatTable)
/* encode2ExpDumpFlat - Dump the experiment table in a semi-flat way from a relationalized Encode2 metadatabase.. */
{
FILE *f = mustOpen(outFile, "w");
struct sqlConnection *conn = sqlConnect(database);
struct starTableInfo **stiArray;
AllocArray(stiArray, ArraySize(starFields));
int i;
for (i=0; i<ArraySize(starFields); ++i)
    stiArray[i] = starTableInfoNew(conn, starFields[i]);

struct dyString *query = dyStringNew(2000);
sqlDyStringPrintf(query, "select ");
for (i=0; i<ArraySize(flatFields); ++i)
    {
    if (i != 0)
       dyStringAppendC(query, ',');
    sqlDyStringPrintf(query, "%s", flatFields[i]);
    }
for (i=0; i<ArraySize(starFields); ++i)
    {
    dyStringAppendC(query, ',');
    sqlDyStringPrintf(query, "%s", starFields[i]);
    }
dyStringPrintf(query, " from %s%s", tablePrefix, "experiment");

struct sqlResult *sr = sqlGetResult(conn, query->string);
char **row;
while ((row = sqlNextRow(sr)) != NULL)
    {
    int flatSize = ArraySize(flatFields);
    int starSize = ArraySize(starFields);
    int i;
    for (i=0; i<flatSize; ++i)
        {
	if (i != 0)
	    fputc('\t', f);
	fputs(row[i], f);
	}
    for (i=0; i<starSize; ++i)
        {
	int id = sqlUnsigned(row[i+flatSize]);
	fputc('\t', f);
	if (id == 0)
	    fputs("n/a", f);
	else
	    fputs(stiArray[i]->termsForIds[id], f);
	}
    fputc('\n', f);
    }


sqlFreeResult(&sr);
sqlDisconnect(&conn);
carefulClose(&f);

makeViewSql(viewSql);
makeFlatTableSql(flatTable);
}