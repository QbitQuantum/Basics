void readTableTask(char *db, char *table)
/* Implements the readTable task */
{
FILE *outFh = NULL;
struct sqlConnection *conn = sqlConnect(db);
struct pslReader* pr = pslReaderQuery(conn, table, gWhere);
struct psl* psl;
int numRows = 0;

if (gOutput != NULL)
    outFh = mustOpen(gOutput, "w");

while ((numRows < gMaxRows) && ((psl = pslReaderNext(pr)) != NULL))
    {
    if (outFh != NULL)
        pslTabOut(psl, outFh);
    pslFree(&psl);
    numRows++;
    }

carefulClose(&outFh);
pslReaderFree(&pr);

sqlDisconnect(&conn);
checkNumRows(table, numRows);
}