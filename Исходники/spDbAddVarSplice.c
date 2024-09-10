void spDbAddVarSplice(char *database, char *inFile, char *outDir)
/* spDbAddVarSplice - This adds information on the varient splices to the sp/uniProt database. */
{
struct sqlConnection *conn = sqlConnect(database);
char query[256];
makeDir(outDir);
FILE *varProtein = openToWrite(outDir, "varProtein.txt");
FILE *varAcc = openToWrite(outDir, "varAcc.txt");
FILE *varDisplayId = openToWrite(outDir, "varDisplayId.txt");
FILE *varAccToTaxon = openToWrite(outDir, "varAccToTaxon.txt");
FILE *varDescription = openToWrite(outDir, "varDescription.txt");
FILE *varGene = openToWrite(outDir, "varGene.txt");
FILE *varGeneLogic = openToWrite(outDir, "varGeneLogic.txt");
struct lineFile *lf = lineFileOpen(inFile, TRUE);
aaSeq seq;
ZeroVar(&seq);
while (faPepSpeedReadNext(lf, &seq.dna, &seq.size, &seq.name))
    {
    char *row[4];
    char *name = seq.name;
    if (startsWith("sp|", name))	// Skip over sp| introduced Aug 2009
        name += 3;
    int rowSize = chopString(name, "-|", row, ArraySize(row));
    if (rowSize != 3)
        errAbort("Expecting name to be in format accession-N|DISP_ID, got %s\n", name);
    char *acc = row[0];
    char *version = row[1];
    char *displayId = row[2];
    int accLen = strlen(acc);
    int verLen = strlen(version);
    int displayIdLen = strlen(displayId);

    /* Do some tests. */
    if ((accLen != 6 && accLen != 10) || isdigit(acc[0]) || !isdigit(acc[accLen-1]))
        errAbort("wierd accession %s before line %d of %s", acc, lf->lineIx, lf->fileName);
    if (!isdigit(version[0]) || verLen > 4)
        errAbort("wierd version %s before line %d of %s", version, lf->lineIx, lf->fileName);
    if (countChars(displayId, '_') != 1 || displayIdLen < 6 || displayIdLen > 16)
        errAbort("wierd displayId %s before line %d of %s", displayId, lf->lineIx, lf->fileName);
    if (accLen + 1 + verLen >= sizeof(SpAcc))
        errAbort("Need to increase size of SpAcc in spDb.h because of %s-%s - need %d characters but only have %lu", acc, version, accLen + 1 + verLen, sizeof(SpAcc));

    /* Print out parsed results. */
    fprintf(varAcc, "%s-%s\t%s\t%s\n", acc, version, acc, version);
    fprintf(varProtein, "%s-%s\t%s\n", acc, version, seq.dna);
    fprintf(varDisplayId, "%s-%s\t%s-%s\n", acc, version, acc, version);

    /* Look up taxon of base protein and use it to write to varAccToTaxon table. */
    int taxon = spTaxon(conn, acc);
    fprintf(varAccToTaxon, "%s-%s\t%d\n", acc, version, taxon);

    /*Transfer description. */
    char *description = spDescription(conn, acc);
    fprintf(varDescription, "%s-%s\t%s\n", acc, version, description);
    freez(&description);

    /* Transfer gene logic. */
    sqlSafef(query, sizeof(query), "select val from geneLogic where acc = '%s'", acc);
    char *geneLogic = sqlQuickString(conn, query);
    if (geneLogic != NULL)
        fprintf(varGeneLogic, "%s-%s\t%s\n", acc, version, geneLogic);
    freez(&geneLogic);

    /* Transfer genes. */
    struct slName *gene, *geneList = spGenes(conn, acc);
    for (gene = geneList; gene != NULL; gene = gene->next)
        fprintf(varGene, "%s-%s\t%s\n", acc, version, gene->name);
    slFreeList(&geneList);

    }
carefulClose(&varAcc);
carefulClose(&varProtein);
carefulClose(&varDisplayId);
carefulClose(&varAccToTaxon);
carefulClose(&varDescription);
carefulClose(&varGene);
carefulClose(&varGeneLogic);
sqlDisconnect(&conn);
}