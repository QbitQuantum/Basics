static void gapToLift(char *db, char *outFile)
/* gapToLift - create lift file from gap table(s). */
{
FILE *out = mustOpen(outFile, "w");
struct sqlConnection *conn = sqlConnect(db);
struct chromInfo *cInfoList = loadChromInfo(conn);
struct agpGap *gapList = loadAllGaps(conn, db, cInfoList);
struct agpGap *gap;
int start = 0;
int end = 0;
char *prevChr = NULL;
int liftCount = 0;
int chrSize = 0;
static struct hash *chrDone = NULL;

chrDone = newHash(0);

if (isNotEmpty(bedFileName))
    {
    bedFile = mustOpen(bedFileName, "w");
    verbose(2,"#\tbed output requested to %s\n", bedFileName);
    }

for (gap = gapList; gap; gap = gap->next)
    {
    verbose(3,"#\t%s\t%d\t%d\t%s\n", gap->chrom, gap->chromStart,
	gap->chromEnd, gap->bridge);

    if (prevChr && sameWord(prevChr, gap->chrom))
	{	/* continuing same segment, check for gap break,
		 *	or gap at end of chrom */
	if (sameWord("no",gap->bridge) || (gap->chromEnd == chrSize))
	    {
	    end = gap->chromStart;
	    liftCount = liftOutLine(out, gap->chrom, start, end, liftCount, chrSize);
	    start = gap->chromEnd;
	    end = start;
	    }
	else
	    end = gap->chromEnd;
	}
    else	/* new chrom encountered */
	{ /* output last segment of previous chrom when necessary */
	if (prevChr && differentWord(prevChr, gap->chrom))
	    {
	    if (end < chrSize)
		liftCount = liftOutLine(out, prevChr, start, chrSize, liftCount, chrSize);
	    }
	liftCount = 0;
	chrSize = hashIntVal(cInfoHash, gap->chrom);
	hashAddInt(chrDone, gap->chrom, 1);
	if (gap->chromStart > 0)
	    {	/* starting first segment at position 0 */
	    start = 0;
	    end = gap->chromStart;
	    /* does the first gap break it ?  Or gap goes to end of chrom. */
	    if (sameWord("no",gap->bridge) || (gap->chromEnd == chrSize))
		{
		liftCount = liftOutLine(out, gap->chrom, start, end, liftCount, chrSize);
		start = gap->chromEnd;
		end = start;
		}
	    }
	else	/* first gap is actually the beginning of the chrom */
	    {	/* thus, first segment starts after this first gap */
	    start = gap->chromEnd;
	    end = start;
	    }
	}
    prevChr = gap->chrom;	/* remember prev chrom to detect next chrom */
    }
/* potentially a last one */
if (end < chrSize)
    liftCount = liftOutLine(out, prevChr, start, chrSize, liftCount, chrSize);
/* check that all chroms have been used */
struct hashCookie cookie = hashFirst(cInfoHash);
struct hashEl *hel;
while ((hel = hashNext(&cookie)) != NULL)
    {
    if (NULL == hashLookup(chrDone, hel->name))
	{
	chrSize = hashIntVal(cInfoHash, hel->name);
	verbose(2, "#\tno gaps on chrom: %s, size: %d\n", hel->name, chrSize);
	liftCount = liftOutLine(out, hel->name, 0, chrSize, 0, chrSize);
	}
    }
carefulClose(&out);
sqlDisconnect(&conn);
}