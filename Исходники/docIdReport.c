void docIdReport(char *database)
/* docIdReport - generate report from docIdSub table. */
{
struct sqlConnection *conn = sqlConnect(database);
struct docIdSub *docIdSub;
char query[10 * 1024];
struct sqlResult *sr;
char **row;
safef(query, sizeof query, "select * from %s", docIdTable);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    docIdSub = docIdSubLoad(row);
    verbose(2, "ix %d\n", docIdSub->ix);
    verbose(2, "submitDate %s\n", docIdSub->submitDate);
    verbose(2, "md5sum %s\n", docIdSub->md5sum);
    verbose(2, "valReport %s\n", docIdSub->valReport);
    verbose(2, "metaData %s\n", docIdSub->metaData);
    verbose(2, "submitPath %s\n", docIdSub->submitPath);
    verbose(2, "submitter %s\n", docIdSub->submitter);

    cgiDecode(docIdSub->metaData, docIdSub->metaData, strlen(docIdSub->metaData));
    char *tempFile = "temp";
    FILE *f = mustOpen(tempFile, "w");
    fwrite(docIdSub->metaData, strlen(docIdSub->metaData), 1, f);
    fclose(f);
    boolean validated;
    struct mdbObj *mdbObj = mdbObjsLoadFromFormattedFile(tempFile, &validated);
    printf("%s %s %s %s %s\n", docIdDecorate(docIdSub->ix),  mdbObjFindValue(mdbObj, "dataType"), mdbObjFindValue(mdbObj, "view"), mdbObjFindValue(mdbObj, "cell"), mdbObjFindValue(mdbObj, "lab"));
    }

sqlFreeResult(&sr);
sqlDisconnect(&conn);
}