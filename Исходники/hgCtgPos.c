void saveCtgPos(struct ctgPos *ctgList, char *database)
/* Save ctgList to database. */
{
struct sqlConnection *conn = sqlConnect(database);
struct ctgPos *ctg;
char *tabFileName = "ctgPos.tab";
FILE *f;
struct dyString *ds = newDyString(2048);

/* Create tab file from ctg list. */
printf("Creating tab file\n");
f = mustOpen(tabFileName, "w");
for (ctg = ctgList; ctg != NULL; ctg = ctg->next)
    ctgPosTabOut(ctg, f);
fclose(f);

/* Create table if it doesn't exist, delete whatever is
 * already in it, and fill it up from tab file. */
printf("Loading ctgPos table\n");
sqlMaybeMakeTable(conn, "ctgPos", createCtgPos);
sqlUpdate(conn, "NOSQLINJ DELETE from ctgPos");
sqlDyStringPrintf(ds, "LOAD data local infile '%s' into table ctgPos", 
    tabFileName);
sqlUpdate(conn, ds->string);

/* Clean up. */
remove(tabFileName);
sqlDisconnect(&conn);
}