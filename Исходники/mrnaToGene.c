void mrnaToGene(char *db, char *cdsDb, char *cdsFile, char *pslSpec,
                char *genePredFile)
/* convert an PSL mRNA table to a genePred file */
{
    struct sqlConnection *conn = NULL;
    FILE* genePredFh;

    if (db != NULL)
        conn = sqlConnect(db);
    else if (cdsDb != NULL)
        conn = sqlConnect(cdsDb);
    genePredFh = mustOpen(genePredFile, "w");

    if (cdsFile != NULL)
        loadCdsFile(cdsFile);

    if (db == NULL)
        convertPslFile(conn, pslSpec, genePredFh);
    else
        convertPslTable(conn, pslSpec, genePredFh);

    if (ferror(genePredFh))
        errAbort("error writing %s", genePredFile);
    carefulClose(&genePredFh);
    sqlDisconnect(&conn);
}