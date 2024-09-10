void hgKnownMore(char *database, char *loc2ref, char *mim2loc, char *omimIds, char *nomeIds)
/* hgKnownMore - Create the knownMore table from a variety of sources.. */
{
struct hash *pgiHash = NULL;	/* Hash of rsInfo indexed by gi. */
struct hash *locHash = NULL;	/* Hash of rsInfo indexed by locusLink IDs. */
struct rsInfo *rs;
struct hash *hmOmimHash = NULL, *hmSymbolHash = NULL;
struct hash *mimHash = NULL;
struct hugoMulti *hmList = NULL, *hm;
struct hash *nameOmimHash = NULL, *omimNameHash = NULL;
struct nameOmim *nameOmimList = NULL, *nameOmim;
struct knownInfo *kiList = NULL, *ki;
struct knownMore km;
struct sqlConnection *conn;
char *tabName = "knownMore.tab";
FILE *f = NULL;
char *omimIdString = NULL;
char query[256];


readLoc2ref(loc2ref, &pgiHash, &locHash);
readMim(mim2loc, &mimHash);
readHugoMultiTable(nomeIds, &hmList, &hmOmimHash, &hmSymbolHash);
printf("Read %d elements in %s\n", slCount(hmList), nomeIds);
readNameOmim(omimIds, &nameOmimList, &nameOmimHash, &omimNameHash);
printf("Read %d elements in %s\n", slCount(nameOmimList), omimIds);

conn = sqlConnect(database);
kiList = loadKnownInfo(conn);
printf("Read %d elements from knownInfo table in %s\n", 
	slCount(kiList), database);

printf("Writing %s\n", tabName);
f = mustOpen(tabName, "w");
for (ki = kiList; ki != NULL; ki = ki->next)
    {
    /* Fill out a knownMore data structure.  Start with all zero
     * just to avoid garbage. */
    zeroBytes(&km, sizeof(km));

    /* First fields come from knownInfo generally. */
    km.name = ki->name;	/* The name displayed in the browser: OMIM, gbGeneName, or transId */
    km.transId = ki->transId;	/* Transcript id. Genie generated ID. */
    km.geneId = ki->geneId;	/* Gene (not transcript) Genie ID */
    km.gbGeneName = ki->geneName;	/* Connect to geneName table. Genbank gene name */
    km.gbProductName = ki->productName;	/* Connects to productName table. Genbank product name */
    km.gbProteinAcc = ki->proteinId;	/* Genbank accession of protein */
    km.gbNgi = ki->ngi;	/* Genbank gi of nucleotide seq. */
    km.gbPgi = ki->pgi;	/* Genbank gi of protein seq. */

    /* Fill in rest with acceptable values for no-data-present. */
    km.omimId = 0;	/* OMIM ID or 0 if none */
    km.omimName = "";	/* OMIM primary name */
    km.hugoId = 0;	/* HUGO Nomeclature Committee ID or 0 if none */
    km.hugoSymbol = "";	/* HUGO short name */
    km.hugoName = "";	/* HUGO descriptive name */
    km.hugoMap = "";	/* HUGO Map position */
    km.pmId1 = 0;	/* I have no idea - grabbed from a HUGO nomeids.txt */
    km.pmId2 = 0;	/* Likewise, I have no idea */
    km.refSeqAcc = "";	/* Accession of RefSeq mRNA */
    km.aliases = "";	/* Aliases if any.  Comma and space separated list */
    km.locusLinkId = 0;	/* Locus link ID */
    km.gdbId = "";	/* NCBI GDB database ID */

    /* See if it's a disease gene with extra info. */
    omimIdString = NULL;
    rs = hashFindVal(pgiHash, km.gbPgi);
    if (rs != NULL && rs->locusLinkId != NULL)
	{
	km.locusLinkId = atoi(rs->locusLinkId);
	omimIdString = hashFindVal(mimHash, rs->locusLinkId);
	}
    if (rs != NULL && rs->mrnaAcc != NULL)
	km.refSeqAcc = rs->mrnaAcc;
    if (omimIdString != NULL)
	{
	km.omimId = atoi(omimIdString);	/* OMIM ID or 0 if none */
	nameOmim = hashFindVal(omimNameHash, omimIdString);
	if (nameOmim != NULL)
	    {
	    km.name = km.omimName = nameOmim->name;
	    }
	hm = hashFindVal(hmOmimHash, omimIdString);
	if (hm != NULL)
	    {
	    km.hugoId = hm->hgnc;	/* HUGO Nomeclature Committee ID or 0 if none */
	    km.name = km.hugoSymbol = hm->symbol;	/* HUGO short name */
	    km.hugoName = hm->name;	/* HUGO descriptive name */
	    km.hugoMap = hm->map;	/* HUGO Map position */
	    km.pmId1 = hm->pmId1;	/* I have no idea - grabbed from a HUGO nomeids.txt */
	    km.pmId2 = hm->pmId2;	/* Likewise, I have no idea */
	    km.refSeqAcc = hm->refSeqAcc;	/* Accession of RefSeq mRNA */
	    km.aliases = hm->aliases;	/* Aliases if any.  Comma and space separated list */
	    km.locusLinkId = hm->locusLinkId;	/* Locus link ID */
	    km.gdbId = hm->gdbId;	/* NCBI GDB database ID */
	    }
	}
    knownMoreTabOut(&km, f);
    }
carefulClose(&f);

printf("Loading database %s\n", database);
sqlUpdate(conn, "NOSQLINJ delete from knownMore");
sqlSafef(query, sizeof query, "load data local infile '%s' into table knownMore", tabName);
sqlUpdate(conn, query);

sqlDisconnect(&conn);
}