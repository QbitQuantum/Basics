void hgGnfMicroarray(char *expTable, char *dataTable, char *atlasFile)
/** Main function that does all the work for new-style*/
{
struct lineFile *lf = lineFileOpen(atlasFile, TRUE);
char *line;
int i, wordCount, expCount;
char **row;
float *data;
char *affyId;
struct hash *hash = newHash(17);
FILE *f = NULL;
int dataCount = 0;

/* Open Atlas file and use first line to create experiment table. */
if (!lineFileNextReal(lf, &line))
    errAbort("%s is empty", lf->fileName);
if (startsWith("Affy", line))
    line += 4;
if (startsWith("Gene Name", line))
    line += 9;
if (line[0] != '\t')
    errAbort("%s doesn't seem to be a new format atlas file", lf->fileName);
expCount = lineToExpTable(line+1, expTable);
if (expCount <= 0)
    errAbort("No experiments in %s it seems", lf->fileName);
warn("%d experiments\n", expCount);

f = hgCreateTabFile(tabDir, dataTable);

AllocArray(row, expCount);
AllocArray(data, expCount);
while (lineFileNextReal(lf, &line))
    {
    affyId = nextWord(&line);
    wordCount = chopByWhite(line, row, expCount);
    if (wordCount != expCount)
        errAbort("Expecting %d data points, got %d line %d of %s", 
		expCount, wordCount, lf->lineIx, lf->fileName);
    if (chopName != NULL)
        {
	char *e = stringIn(chopName, affyId);
	if (e != NULL)
	    *e = 0;
	}
    if (hashLookup(hash, affyId))
	{
        warn("Duplicate %s, skipping all but first.", affyId);
	continue;
	}
    for (i=0; i<expCount; ++i)
        {
        data[i] = sqlFloat(row[i]);
        }
    shortDataOut(f, affyId, expCount, data);
    ++dataCount;
    if (limit != 0 && dataCount >= limit)
        break;
    }
lineFileClose(&lf);

if (doLoad)
    {
    struct sqlConnection *conn = sqlConnect(database);
    expDataCreateTable(conn, dataTable);
    hgLoadTabFile(conn, tabDir, dataTable, &f);
    hgRemoveTabFile(tabDir, dataTable);
    sqlDisconnect(&conn);
    }
}