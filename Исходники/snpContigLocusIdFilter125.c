int main(int argc, char *argv[])
/* Read ContigInfo into hash. */
/* Filter ContigLocusId and write to ContigLocusIdFilter. */
{

if (argc != 3)
    usage();

snpDb = argv[1];
contigGroup = argv[2];
hSetDb(snpDb);

/* check for needed tables */
if(!hTableExistsDb(snpDb, "ContigLocusId"))
    errAbort("no ContigLocusId table in %s\n", snpDb);
if(!hTableExistsDb(snpDb, "ContigInfo"))
    errAbort("no ContigInfo table in %s\n", snpDb);


contigHash = loadContigs(contigGroup);
if (contigHash == NULL) 
    {
    verbose(1, "couldn't get ContigInfo hash\n");
    return 1;
    }

filterSNPs();
createTable();
loadDatabase();

return 0;
}