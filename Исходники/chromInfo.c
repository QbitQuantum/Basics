boolean chromSeqFileExists(char *db, char *chrom)
/* Check whether chromInfo exists for a database, find the path of the */
/* sequence file for this chromosome and check if the file exists. */
{
char seqFile[512];
struct sqlConnection *conn = sqlConnect(db);
char query[256];
char *res = NULL;
boolean exists = FALSE;

/* if the database exists, check for the chromInfo file */
if (sqlDatabaseExists(db))
    {
    safef(query, sizeof(query), "select fileName from chromInfo where chrom = '%s'", chrom);
    res = sqlQuickQuery(conn, query, seqFile, 512);
    sqlDisconnect(&conn);
    }

/* if there is not table or no information in the table or if the table */
/* exists but the file can not be opened return false, otherwise sequence */
/* file exists and return true */
if (res != NULL)
    {
    /* chromInfo table exists so check that sequence file can be opened */
    FILE *f = fopen(seqFile, "rb");
    if (f != NULL)
        {
        exists = TRUE;
        fclose(f);
        }
    }
return exists;
}