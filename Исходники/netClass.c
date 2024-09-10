void netClass(char *inName, char *tDb, char *qDb, char *outName)
/* netClass - Add classification info to net. */
{
struct chainNet *net;
struct lineFile *lf = lineFileOpen(inName, TRUE);
FILE *f = mustOpen(outName, "w");
struct chrom *qChromList, *chrom;
struct hash *qChromHash;
struct hash *arHash = NULL;
struct sqlConnection *tConn = sqlConnect(tDb);
struct sqlConnection *qConn = sqlConnect(qDb);

qLm = lmInit(0);

if (!noAr)
    arHash = getAncientRepeats(tConn, qConn);

getChroms(qConn, &qChromHash, &qChromList);

verbose(1, "Reading gaps in %s\n", qDb);
if (sqlTableExists(qConn, "gap"))
    {
    getSeqGapsUnsplit(qConn, qChromHash);
    }
else
    {
    for (chrom = qChromList; chrom != NULL; chrom = chrom->next)
	chrom->nGaps = getSeqGaps(qConn, chrom->name);
    }

if (qNewR)
    {
    verbose(1, "Reading new repeats from %s\n", qNewR);
    for (chrom = qChromList; chrom != NULL; chrom = chrom->next)
        chrom->newRepeats = getNewRepeats(qNewR, chrom->name);
    }

verbose(1, "Reading simpleRepeats in %s\n", qDb);
getTrfUnsplit(qConn, qChromHash);

if (qRepeatTable)
    {
    verbose(1, "Reading repeats in %s from table %s\n", qDb, qRepeatTable);
    getRepeatsUnsplitTable(qConn, qChromHash, qRepeatTable);
    }
else
    {
    verbose(1, "Reading repeats in %s\n", qDb);
    if (sqlTableExists(qConn, "rmsk"))
	getRepeatsUnsplit(qConn, qChromHash, arHash);
    else
	{
	for (chrom = qChromList; chrom != NULL; chrom = chrom->next)
	    getRepeats(qConn, arHash, chrom->name, &chrom->repeats,
		       &chrom->oldRepeats);
	}
    }

while ((net = chainNetRead(lf)) != NULL)
    {
    struct rbTree *tN, *tRepeats, *tOldRepeats, *tTrf;
    char *tName = net->name;
    if (liftHashT != NULL)
	{
	struct liftSpec *lft = hashMustFindVal(liftHashT, net->name);
	tName = lft->newName;
	}

    verbose(1, "Processing %s.%s\n", tDb, net->name);
    tN = getSeqGaps(tConn, tName);
    tAddN(net, net->fillList, tN);
    rbTreeFree(&tN);
    qAddN(net, net->fillList, qChromHash);

    if (tRepeatTable)
	getRepeatsTable(tConn, tRepeatTable, tName, &tRepeats, &tOldRepeats);
    else
	getRepeats(tConn, arHash, tName, &tRepeats, &tOldRepeats);
    tAddR(net, net->fillList, tRepeats);
    if (!noAr)
	tAddOldR(net, net->fillList, tOldRepeats);
    rbTreeFree(&tRepeats);
    rbTreeFree(&tOldRepeats);
    qAddR(net, net->fillList, qChromHash);
    if (!noAr)
	qAddOldR(net, net->fillList, qChromHash);

    tTrf = getTrf(tConn, tName);
    tAddTrf(net, net->fillList, tTrf);
    rbTreeFree(&tTrf);
    qAddTrf(net, net->fillList, qChromHash);

    if (tNewR)
        {
	struct rbTree *tree = getNewRepeats(tNewR, tName);
	tAddNewR(net, net->fillList, tree);
	rbTreeFree(&tree);
	}
    if (qNewR)
        qAddNewR(net, net->fillList, qChromHash);
    chainNetWrite(net, f);
    chainNetFree(&net);
    }
sqlDisconnect(&tConn);
sqlDisconnect(&qConn);
}