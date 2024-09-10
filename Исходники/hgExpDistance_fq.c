void hgExpDistance(char *database, char *posTable, char *expTable, char *outTable)
/* hgExpDistance - Create table that measures expression distance between pairs. */
{
struct sqlConnection *conn = sqlConnect(database);
struct sqlResult *sr;
char query[256];
char **row;
struct hash *expHash = hashNew(16);
int realExpCount = -1;
struct microData *gene;
int rc, t;
pthread_t *threads = NULL;
pthread_attr_t attr;
int *threadID = NULL;
void *status;
char *tempDir = ".";
int arrayNum; 
struct microDataDistance *geneDistPtr = NULL;	
struct microDataDistance *geneDistArray = NULL;	
int geneIx;
FILE *f = NULL;

/* Get list/hash of all items with expression values. */
safef(query, sizeof(query), "select name,expCount,expScores from %s", posTable);
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

f = hgCreateTabFile(tempDir, outTable);
synQ = synQueueNew();

/* instantiate threads */
AllocArray( threadID, numThreads );
AllocArray( threads, numThreads );
pthread_attr_init( &attr );
pthread_mutex_init( &mutexDotOut, NULL );
pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

for (t = 0; t < numThreads; t++) {
	threadID[t] = t;
	rc = pthread_create( &threads[t], &attr, computeDistance, 
						(void *) &threadID[t]);
	if (rc)
		errAbort("ERROR: in pthread_create() %d\n", rc );
} 

/* this thread will write to the file from the queue */
for (arrayNum = 0; arrayNum < geneCount; arrayNum++) {
	geneDistArray = (struct microDataDistance *)synQueueGet( synQ );
	geneDistPtr = geneDistArray;
    	/* Print out closest GENEDISTS distances in tab file. */
    	for (geneIx=0; geneIx < GENEDISTS && geneIx < geneCount; 
						++geneIx, geneDistPtr++)
		if (geneDistPtr != NULL)
			fprintf(f, "%s\t%s\t%f\n", geneDistPtr->name1, 
				geneDistPtr->name2, geneDistPtr->distance);
		else
			errAbort("ERROR: writing distance %d to file\n", 
							geneIx);
	freeMem( geneDistArray );
}

/* synchronize all threads */
for (t = 0; t < numThreads; t++) {
	rc = pthread_join( threads[t], &status);
	if (rc)
		errAbort("ERROR: in pthread_join() %d\n", rc );
} 

printf("Made %s.tab\n", outTable);

slFreeList( &geneList );

pthread_mutex_destroy( &mutexDotOut );
pthread_attr_destroy( &attr );

/* Create and load table. */
conn = sqlConnect(database);
distanceTableCreate(conn, outTable);
hgLoadTabFile(conn, tempDir, outTable, &f);
printf("Loaded %s\n", outTable);

/* Add indices. */
safef(query, sizeof(query), "alter table %s add index(query(12))", outTable);
sqlUpdate(conn, query);
printf("Made query index\n");
if (optionExists("targetIndex"))
    {
    safef(query, sizeof(query), "alter table %s add index(target(12))", outTable);
    sqlUpdate(conn, query);
    printf("Made target index\n");
    }

hgRemoveTabFile(tempDir, outTable);
}