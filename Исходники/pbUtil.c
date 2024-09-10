int searchProteinsInSwissProtByGene(char *queryGeneID)
/* search Swiss-Prot database to see if it contains the protein
   Input: queryGeneID
   return: number of proteins found in Swiss-Prot
*/
{
int  proteinCnt;
struct sqlConnection *conn;
char query[256];
struct sqlResult *sr;
char **row;

conn = sqlConnect(UNIPROT_DB_NAME);
sqlSafef(query, sizeof(query),
            "select count(*) from gene, displayId, accToTaxon,taxon "
            "where gene.val='%s' and gene.acc=displayId.acc and accToTaxon.taxon=taxon.id "
            "and accToTaxon.acc=gene.acc order by taxon.id",
            queryGeneID);

sr  = sqlMustGetResult(conn, query);
row = sqlNextRow(sr);

if (row == NULL)
    {
    errAbort("Error occured during mySQL query: %s\n", query);
    }

proteinCnt = atoi(row[0]);

sqlFreeResult(&sr);
sqlDisconnect(&conn);
return(proteinCnt);
}