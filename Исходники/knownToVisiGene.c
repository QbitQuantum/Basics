void knownToVisiGene(char *database)
/* knownToVisiGene - Create knownToVisiGene table by riffling through various other knownTo tables. */
{
char *tempDir = ".";
FILE *f = hgCreateTabFile(tempDir, outTable);
struct sqlConnection *hConn = sqlConnect(database);
struct sqlConnection *iConn = sqlConnect(visiDb);
struct sqlResult *sr;
char **row;
struct hash *geneImageHash = newHash(18);
struct hash *locusLinkImageHash = newHash(18);
struct hash *refSeqImageHash = newHash(18);
struct hash *genbankImageHash = newHash(18);
struct hash *probeImageHash = newHash(18);
struct hash *knownToLocusLinkHash = newHash(18);
struct hash *knownToRefSeqHash = newHash(18);
struct hash *knownToGeneHash = newHash(18);
struct hash *favorHugoHash = newHash(18);
struct hash *knownToProbeHash = newHash(18);
struct hash *knownToAllProbeHash = newHash(18);
struct genePred *knownList = NULL, *known;
struct hash *dupeHash = newHash(17);


probesDb  = optionVal("probesDb", database);
struct sqlConnection *probesConn = sqlConnect(probesDb);
vgProbes = sqlTableExists(probesConn,"vgProbes");
vgAllProbes = sqlTableExists(probesConn,"vgAllProbes");

/* Go through and make up hashes of images keyed by various fields. */
sr = sqlGetResult(iConn,
        NOSQLINJ "select image.id,imageFile.priority,gene.name,gene.locusLink,gene.refSeq,gene.genbank"
	",probe.id,submissionSet.privateUser,vgPrbMap.vgPrb,gene.id"
	" from image,imageFile,imageProbe,probe,gene,submissionSet,vgPrbMap"
	" where image.imageFile = imageFile.id"
	" and image.id = imageProbe.image"
	" and imageProbe.probe = probe.id"
	" and probe.gene = gene.id"
	" and image.submissionSet=submissionSet.id"
	" and vgPrbMap.probe = probe.id");

while ((row = sqlNextRow(sr)) != NULL)
    {
    int id = sqlUnsigned(row[0]);
    float priority = atof(row[1]);
    int privateUser = sqlSigned(row[7]);
    char vgPrb_Id[256];
    safef(vgPrb_Id, sizeof(vgPrb_Id), "vgPrb_%s",row[8]);
    int geneId = sqlUnsigned(row[9]);
    if (privateUser == 0)
	{
	addPrioritizedImage(probeImageHash, id, priority, geneId, vgPrb_Id);
	addPrioritizedImage(geneImageHash, id, priority, geneId, row[2]);
	addPrioritizedImage(locusLinkImageHash, id, priority, geneId, row[3]);
	addPrioritizedImage(refSeqImageHash, id, priority, geneId, row[4]);
	addPrioritizedImage(genbankImageHash, id, priority, geneId, row[5]);
	}
    }
verbose(2, "Made hashes of image: geneImageHash %d, locusLinkImageHash %d, refSeqImageHash %d"
           ", genbankImageHash %d probeImageHash %d\n", 
            geneImageHash->elCount, locusLinkImageHash->elCount, refSeqImageHash->elCount, 
	    genbankImageHash->elCount, probeImageHash->elCount);
sqlFreeResult(&sr);

/* Build up list of known genes. */
sr = sqlGetResult(hConn, NOSQLINJ "select * from knownGene");
while ((row = sqlNextRow(sr)) != NULL)
    {
    struct genePred *known = genePredLoad(row);
    if (!hashLookup(dupeHash, known->name))
        {
	hashAdd(dupeHash, known->name, NULL);
	slAddHead(&knownList, known);
	}
    }
slReverse(&knownList);
sqlFreeResult(&sr);
verbose(2, "Got %d known genes\n", slCount(knownList));

/* Build up hashes from knownGene to other things. */
if (vgProbes)
    bestProbeOverlap(probesConn, "vgProbes", knownList, knownToProbeHash);
if (vgAllProbes)
    bestProbeOverlap(probesConn, "vgAllProbes", knownList, knownToAllProbeHash);

foldIntoHash(hConn, "knownToLocusLink", "name", "value", knownToLocusLinkHash, NULL, FALSE);
foldIntoHash(hConn, "knownToRefSeq", "name", "value", knownToRefSeqHash, NULL, FALSE);
foldIntoHash(hConn, "kgXref", "kgID", "geneSymbol", knownToGeneHash, favorHugoHash, FALSE);
foldIntoHash(hConn, "kgAlias", "kgID", "alias", knownToGeneHash, favorHugoHash, TRUE);
foldIntoHash(hConn, "kgProtAlias", "kgID", "alias", knownToGeneHash, favorHugoHash, TRUE);

verbose(2, "knownToLocusLink %d, knownToRefSeq %d, knownToGene %d knownToProbe %d knownToAllProbe %d\n", 
   knownToLocusLinkHash->elCount, knownToRefSeqHash->elCount, knownToGeneHash->elCount,
   knownToProbeHash->elCount, knownToAllProbeHash->elCount);

/* Try and find an image for each gene. */
for (known = knownList; known != NULL; known = known->next)
    {
    char *name = known->name;
    struct prioritizedImage *best = NULL;
    {
    best = bestImage(name, knownToLocusLinkHash, locusLinkImageHash);
    if (!best)
	best = bestImage(name, knownToRefSeqHash, refSeqImageHash);
    if (!best)
	{
	best = hashFindVal(genbankImageHash, name);
	}
    if (!best)
	best = bestImage(name, knownToGeneHash, geneImageHash);
    if (vgProbes && !best)
	best = bestImage(name, knownToProbeHash, probeImageHash);
    if (vgAllProbes && !best)
	best = bestImage(name, knownToAllProbeHash, probeImageHash);
    }	    
    if (best)
        {
	fprintf(f, "%s\t%d\t%d\n", name, best->imageId, best->geneId);
	}
    }

createTable(hConn, outTable);
hgLoadTabFile(hConn, tempDir, outTable, &f);
hgRemoveTabFile(tempDir, outTable);
}