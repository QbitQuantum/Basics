void hgLoadMafSummary(char *db, char *table, char *fileName)
/* hgLoadMafSummary - Load a summary table of pairs in a maf into a database. */
{
long mafCount = 0, allMafCount = 0;
struct mafComp *mcMaster = NULL;
struct mafAli *maf;
struct mafFile *mf = mafOpen(fileName);
struct sqlConnection *conn;
FILE *f = hgCreateTabFile(".", table);
long componentCount = 0;
struct hash *componentHash = newHash(0);

if (!test)
    {
    conn = sqlConnect(database);
    mafSummaryTableCreate(conn, table, hGetMinIndexLength(db));
    }
verbose(1, "Indexing and tabulating %s\n", fileName);

/* process mafs */
while ((maf = mafNext(mf)) != NULL)
    {
    mcMaster = mafMaster(maf, mf, fileName);
    allMafCount++;
    if (mcMaster->srcSize < minSeqSize)
	continue;
    while (mcMaster->size > maxSize)
        {
        /* break maf into maxSize pieces */
        int end = mcMaster->start + maxSize;
        struct mafAli *subMaf = 
                mafSubset(maf, mcMaster->src, mcMaster->start, end);
        verbose(3, "Splitting maf %s:%d len %d\n", mcMaster->src,
                                        mcMaster->start, mcMaster->size);
        componentCount += 
            processMaf(subMaf, componentHash, f, mf, fileName);
        mafAliFree(&subMaf);
        subMaf = mafSubset(maf, mcMaster->src, 
                                end, end + (mcMaster->size - maxSize));
        mafAliFree(&maf);
        maf = subMaf;
        mcMaster = mafMaster(maf, mf, fileName);
        }
    if (mcMaster->size != 0)
        {
        /* remainder of maf after splitting off maxSize submafs */
        componentCount += 
            processMaf(maf, componentHash, f, mf, fileName);
        }
    mafAliFree(&maf);
    mafCount++;
    }
mafFileFree(&mf);
flushSummaryBlocks(componentHash, f);
verbose(1, 
    "Created %ld summary blocks from %ld components and %ld mafs from %s\n",
        summaryCount, componentCount, allMafCount, fileName);
if (test)
    return;
verbose(1, "Loading into %s table %s...\n", database, table);
hgLoadTabFile(conn, ".", table, &f);
verbose(1, "Loading complete");
hgEndUpdate(&conn, "Add %ld maf summary blocks from %s\n", 
                        summaryCount, fileName);
}