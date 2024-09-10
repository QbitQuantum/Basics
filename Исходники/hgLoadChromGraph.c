struct chromGraph *chromGraphListWithTable(char *fileName, char *db, char *table)
/* Read the chromGraph file and convert to the  chr,chromStart format. */
{
    struct sqlConnection *conn = sqlConnect(db);
    struct hash *posHash = NULL;
    struct lineFile *lf;
    struct chromGraph *list = NULL;
    char *words[2];
    checkTableForFields(conn, table);
    posHash = posHashFromTable(conn, table);
    sqlDisconnect(&conn);
    lf = lineFileOpen(fileName, TRUE);
    while (lineFileRow(lf, words))
    {
        struct chromGraph *cg;
        /* Look up ID in hash. */
        struct slPair *infoFromHash = hashFindVal(posHash, words[0]);
        if (!infoFromHash)
            warn("%s line %d: %s not found in %s table", fileName, lf->lineIx, words[0], table);
        else
        {
            AllocVar(cg);
            cg->chrom = cloneString(infoFromHash->name);
            cg->chromStart = ptToInt(infoFromHash->val);
            cg->val = sqlDouble(words[1]);
            slAddHead(&list, cg);
        }
    }
    slReverse(&list);
    /* Free stuff up. */
    lineFileClose(&lf);
    hashFreeWithVals(&posHash, slPairFree);
    return list;
}