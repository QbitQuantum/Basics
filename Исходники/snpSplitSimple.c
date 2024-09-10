void writeSplitTables()
/* sequentially read ContigLocFilter, writing to appropriate chrom file */
/* we are storing chromName in the table just as a sanity check */
/* It is dropped in the next step of the pipeline */
{
char query[512];
struct sqlConnection *conn = hAllocConn();
struct sqlResult *sr;
char **row;
struct hashEl *hel;
char *chromName;

verbose(1, "reading ContigLocFilter...\n");

sqlSafef(query, sizeof(query), 
    "select snp_id, ctg_id, chromName, loc_type, phys_pos_from, phys_pos, orientation, allele from ContigLocFilter");

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    hel = hashLookup(chromHash,row[2]);
    if (hel == NULL)
        {
	verbose(1, "%s not found\n", row[2]);
	continue;
	}
    fprintf(hel->val, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
    }
sqlFreeResult(&sr);
sqlDisconnect(&conn);
}