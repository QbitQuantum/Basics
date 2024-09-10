void hgSoftberryHom(char *database, int fileCount, char *files[])
/* hgSoftberryHom - Make table storing Softberry protein homology information. */
{
int i;
char *fileName;
char *table = "softberryHom";
char *tabFileName = "softberryHom.tab";
FILE *f = mustOpen(tabFileName, "w");
struct sqlConnection *conn = NULL;
struct dyString *ds = newDyString(2048);

for (i=0; i<fileCount; ++i)
    {
    fileName = files[i];
    printf("Processing %s\n", fileName);
    makeTabLines(fileName, f);
    }
carefulClose(&f);

/* Create table if it doesn't exist, delete whatever is
 * already in it, and fill it up from tab file. */
conn = sqlConnect(database);
printf("Loading %s table\n", table);
sqlMaybeMakeTable(conn, table, createTable);
sqlDyStringPrintf(ds, "DELETE from %s", table);
sqlUpdate(conn, ds->string);
dyStringClear(ds);
sqlDyStringPrintf(ds, "LOAD data local infile '%s' into table %s", 
    tabFileName, table);
sqlUpdate(conn, ds->string);
sqlDisconnect(&conn);
}