void hgMaxExp(char *database, char *table)
/* Output maximum expScore in table */
{
struct sqlConnection *conn = sqlConnect(database);
struct sqlResult *sr;
char query[256];
char **row;

/* Get list of all items with expression values. */
char *fieldNames = "name, expCount, expScores";
sqlSafef(query, sizeof(query), "select %s from %s", fieldNames, table);
sr = sqlGetResult(conn, query);
float maxScore = 0.0;
float minScore = 100000.0;
while ((row = sqlNextRow(sr)) != NULL)
    {
    char *name = row[0];
    int expCount = sqlUnsigned(row[1]);
    int commaCount;
    float *expScores = NULL;
    sqlFloatDynamicArray(row[2], &expScores, &commaCount);
    if (expCount != commaCount)
        errAbort("expCount and expScores don't match on %s in %s", name, table);
    int i;
    for (i=0; i<expCount; i++)
        {
        maxScore = max(maxScore, expScores[i]);
        minScore = min(minScore, expScores[i]);
        }
    }
sqlFreeResult(&sr);
conn = sqlConnect(database);
sqlDisconnect(&conn);	/* Disconnect because next step is slow. */
printf("max: %0.2f  min: %0.2f\n", maxScore, minScore);
}