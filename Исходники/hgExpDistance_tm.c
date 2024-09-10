void hgExpDistance(char *database, char *posTable, char *expTable, char *outTable)
/* hgExpDistance - Create table that measures expression distance between pairs. */
{
struct sqlConnection *conn = sqlConnect(database);
struct sqlResult *sr;
char query[256];
char **row;
struct hash *expHash = hashNew(16);
int realExpCount = -1;
struct microData *geneList = NULL, *curGene, *gene;
int geneIx, geneCount = 0;
struct microData **geneArray = NULL;
float *weights = NULL;
char *tempDir = ".";
FILE *f = hgCreateTabFile(tempDir, outTable);
long time1, time2;

time1 = clock1000();

/* Get list/hash of all items with expression values. */

/* uglyf("warning: temporarily limited to 1000 records\n"); */

sqlSafef(query, sizeof(query), "select name,expCount,expScores from %s", posTable);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    char *name = row[0];
    if (!hashLookup(expHash, name))
	{
	int expCount = sqlUnsigned(row[1]);
	int commaCount;
	float *expScores = NULL;

	sqlFloatDynamicArray(row[2], &expScores, &commaCount);
	if (expCount != commaCount)
	    errAbort("expCount and expScores don't match on %s in %s", name, posTable);
	if (realExpCount == -1)
	    realExpCount = expCount;
	if (expCount != realExpCount)
	    errAbort("In %s some rows have %d experiments others %d", 
	    	name, expCount, realExpCount);
	AllocVar(gene);
	gene->expCount = expCount;
	gene->expScores = expScores;
	hashAddSaveName(expHash, name, gene, &gene->name);
	slAddHead(&geneList, gene);
	}
    }
sqlFreeResult(&sr);
conn = sqlConnect(database);
slReverse(&geneList);
geneCount = slCount(geneList);
printf("Have %d elements in %s\n", geneCount, posTable);

weights = getWeights(realExpCount);

if (optionExists("lookup"))
    geneList = lookupGenes(conn, optionVal("lookup", NULL), geneList);
geneCount = slCount(geneList);
printf("Got %d unique elements in %s\n", geneCount, posTable);

sqlDisconnect(&conn);	/* Disconnect because next step is slow. */


if (geneCount < 1)
    errAbort("ERROR: unique gene count less than one ?");

time2 = clock1000();
verbose(2, "records read time: %.2f seconds\n", (time2 - time1) / 1000.0);

/* Get an array for sorting. */
AllocArray(geneArray, geneCount);
for (gene = geneList,geneIx=0; gene != NULL; gene = gene->next, ++geneIx)
    geneArray[geneIx] = gene;

/* Print out closest 1000 in tab file. */
for (curGene = geneList; curGene != NULL; curGene = curGene->next)
    {
    calcDistances(curGene, geneList, weights);
    qsort(geneArray, geneCount, sizeof(geneArray[0]), cmpMicroDataDistance);
    for (geneIx=0; geneIx < 1000 && geneIx < geneCount; ++geneIx)
        {
	gene = geneArray[geneIx];
	fprintf(f, "%s\t%s\t%f\n", curGene->name, gene->name, gene->distance);
	}
    dotOut();
    }

printf("Made %s.tab\n", outTable);

time1 = time2;
time2 = clock1000();
verbose(2, "distance computation time: %.2f seconds\n", (time2 - time1) / 1000.0);

/* Create and load table. */
conn = sqlConnect(database);
distanceTableCreate(conn, outTable);
hgLoadTabFile(conn, tempDir, outTable, &f);
printf("Loaded %s\n", outTable);

/* Add indices. */
sqlSafef(query, sizeof(query), "alter table %s add index(query(12))", outTable);
sqlUpdate(conn, query);
printf("Made query index\n");
if (optionExists("targetIndex"))
    {
    sqlSafef(query, sizeof(query), "alter table %s add index(target(12))", outTable);
    sqlUpdate(conn, query);
    printf("Made target index\n");
    }

hgRemoveTabFile(tempDir, outTable);

time1 = time2;
time2 = clock1000();
verbose(2, "table create/load/index time: %.2f seconds\n", (time2 - time1) / 1000.0);

}