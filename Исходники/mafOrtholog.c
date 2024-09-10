struct genePred *getOverlappingGeneDb(struct genePred **list, char *table, char *chrom, int cStart, int cEnd, char *name, int *retOverlap, char *db)
{
/* read all genes from a table find the gene with the biggest overlap. 
   Cache the list of genes to so we only read it once */

struct genePred *el = NULL, *bestMatch = NULL, *gp = NULL;
int overlap = 0 , bestOverlap = 0, i;
int *eFrames;

if (list == NULL)
    return NULL;

if (*list == NULL)
    {
    struct genePred *gpList = NULL;
    struct sqlConnection *conn = sqlConnect(db);
    struct genePredReader *gpr = NULL;
    if (!hTableExistsDb(db,table))
        table = altTable;
    if (!hTableExistsDb(db,table))
        {
        verbose(2,"no table %s in %s\n",table, db);
        return NULL;
        }
    gpr = genePredReaderQuery(conn, table, NULL);
    verbose(1,"Loading Predictions from %s in %s\n",table, db);
    gpList = genePredReaderAll(gpr);
    if (gpList != NULL)
        {
        hashAdd(geneListHash, db, gpList);
        *list = gpList;
        }
    sqlDisconnect(&conn);
    }
for (el = *list; el != NULL; el = el->next)
    {
    if (chrom != NULL && el->chrom != NULL)
        {
        overlap = 0;
        if ( sameString(chrom, el->chrom))
            {
            for (i = 0 ; i<(el->exonCount); i++)
                {
                overlap += positiveRangeIntersection(cStart,cEnd, el->exonStarts[i], el->exonEnds[i]) ;
                }
            if (overlap > 20 && sameString(name, el->name))
                {
                bestMatch = el;
                bestOverlap = overlap;
                *retOverlap = bestOverlap;
                }
            if (overlap > bestOverlap)
                {
                bestMatch = el;
                bestOverlap = overlap;
                *retOverlap = bestOverlap;
                }
            }
        }
    }
if (bestMatch != NULL)
    {
    /* Allocate genePred and fill in values. */
    AllocVar(gp);
    gp->name = cloneString(bestMatch->name);
    gp->chrom = cloneString(bestMatch->chrom);
    gp->strand[1] = bestMatch->strand[1];
    gp->strand[0] = bestMatch->strand[0];
    gp->txStart = bestMatch->txStart;
    gp->txEnd = bestMatch->txEnd;
    gp->cdsStart = bestMatch->cdsStart;
    gp->cdsEnd = bestMatch->cdsEnd;
    gp->exonCount = bestMatch->exonCount;
    AllocArray(gp->exonStarts, bestMatch->exonCount);
    AllocArray(gp->exonEnds, bestMatch->exonCount);
    for (i=0; i<bestMatch->exonCount; ++i)
        {
        gp->exonStarts[i] = bestMatch->exonStarts[i] ;
        gp->exonEnds[i] = bestMatch->exonEnds[i] ;
        }
    gp->optFields = bestMatch->optFields;
    gp->id = bestMatch->id;

    if (bestMatch->optFields & genePredName2Fld)
        gp->name2 = cloneString(bestMatch->name2);
    else
        gp->name2 = NULL;
    if (bestMatch->optFields & genePredCdsStatFld)
        {
        gp->cdsStartStat = bestMatch->cdsStartStat;
        gp->cdsEndStat = bestMatch->cdsEndStat;
        }
    if (bestMatch->optFields & genePredExonFramesFld)
        {
        gp->exonFrames = AllocArray(eFrames, bestMatch->exonCount);
        for (i = 0; i < bestMatch->exonCount; i++)
            gp->exonFrames[i] = bestMatch->exonFrames[i];
        }
    eFrames = gp->exonFrames;
    }

return gp;
}