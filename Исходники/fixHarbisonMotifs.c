void fixHarbisonMotifs(char *database)
/* fixHarbisonMotifs - Trim motifs that have beginning or ending columns that 
 * are degenerate.. */
{
char *motifTable = "transRegCodeMotif";
char *siteTable = "transRegCode";
struct sqlConnection *conn = sqlConnect(database);
struct sqlResult *sr;
char query[512], **row;
struct motifSize *msList = NULL, *ms;
struct hash *msHash = newHash(16);
boolean anyMinNotMax = FALSE;
boolean anyMissingMotif = FALSE;
boolean anyMotifNotFound = FALSE;
struct dnaMotif *motif;

/* Stream through site table collecting data about motif sizes. */
safef(query, sizeof(query), 
	"select name,chromEnd-chromStart from %s", siteTable);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    char *name = row[0];
    int size = atoi(row[1]);
    ms = hashFindVal(msHash, name);
    if (ms == NULL)
        {
	AllocVar(ms);
	hashAddSaveName(msHash, name, ms, &ms->name);
	ms->minSize = ms->maxSize = size;
	slAddHead(&msList, ms);
	}
    else
        {
	if (size < ms->minSize)
	    ms->minSize = size;
	if (size > ms->maxSize)
	    ms->maxSize = size;
	}
    }
sqlFreeResult(&sr);

/* Go through and report if minSize != maxSize. */
for (ms = msList; ms != NULL; ms = ms->next)
    {
    if (ms->minSize != ms->maxSize)
        {
	anyMinNotMax = TRUE;
	warn("%s size inconsistent:  min %d, max %d", 
		ms->name, ms->minSize, ms->maxSize);
	}
    }
if (!anyMinNotMax)
    warn("All sizes agree in %s", siteTable);

/* Stream through motifs and add to msList. */
safef(query, sizeof(query), "select * from %s", motifTable);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    motif = dnaMotifLoad(row);
    ms = hashFindVal(msHash, motif->name);
    if (ms == NULL)
        {
	anyMissingMotif = TRUE;
	warn("Motif %s is in %s but not %s", 
		motif->name, motifTable, siteTable);
	}
    else
        {
	ms->motif = motif;
	}
    }
sqlFreeResult(&sr);
if (!anyMissingMotif)
    warn("All motifs in %s are also in %s", motifTable, siteTable);

/* Make sure that all items in msList have a motif. */
for (ms = msList; ms != NULL; ms = ms->next)
    {
    if (ms->motif == NULL)
        {
	anyMotifNotFound = TRUE;
	warn("Motif %s is in %s but not %s",
		ms->name, siteTable, motifTable);
	}
    }
if (!anyMotifNotFound)
    warn("All motifs in %s are also in %s", siteTable, motifTable);
    
/* Loop through table and deal with motifs that have different number
 * of columns in motif and site tables. */
for (ms = msList; ms != NULL; ms = ms->next)
    {
    motif = ms->motif;
    if (motif != NULL && ms->minSize == ms->maxSize)
        {
	if (motif->columnCount != ms->minSize)
	    {
	    warn("Motif %s has %d columns in %s but %d columns in %s",
	    	ms->name, ms->minSize, siteTable, 
		motif->columnCount, motifTable);
	    fixMotif(motif, ms->minSize, motifTable, conn);
	    }
	}
    }

sqlDisconnect(&conn);
}