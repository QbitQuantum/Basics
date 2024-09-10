void checkDbTables(char *database, char *composite, struct hash *mdbHash, struct hash *allBbiNames)
// search the database for tables that begin with composite and call checkTable
{
struct sqlConnection *conn = sqlConnect(database);
char buffer[10 * 1024];

verbose(1, "----------------------------------------------\n");
verbose(1, "Checking that tables starting with composite in db are in metaDb\n (also checks dummy table and the bbi symlink and its target)\n");
verbose(1, "----------------------------------------------\n");
sqlSafef(buffer, sizeof buffer, "show tables like '%s%%'", composite);

struct sqlResult *sr;
sr = sqlGetResult(conn, buffer);
char **row;
struct slName *list = NULL;
while ((row = sqlNextRow(sr)) != NULL)
    {
    struct slName *el = slNameNew(row[0]);
    slAddHead(&list, el);
    }
sqlFreeResult(&sr);

for(; list; list = list->next)
    checkTable(conn, list->name, mdbHash, allBbiNames);
sqlDisconnect(&conn);
}