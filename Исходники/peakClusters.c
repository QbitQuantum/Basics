void doPeakClusters(struct trackDb *tdb, char *item)
/* Display detailed info about a cluster of DNase peaks from other tracks. */
{
int start = cartInt(cart, "o");
char *table = tdb->table;
int rowOffset = hOffsetPastBin(database, seqName, table);
char query[256];
struct sqlResult *sr;
char **row;
struct bed *cluster = NULL;
struct sqlConnection *conn = hAllocConn(database);

cartWebStart(cart, database, "%s item details", tdb->shortLabel);
sqlSafef(query, sizeof(query),
	"select * from %s where  name = '%s' and chrom = '%s' and chromStart = %d",
	table, item, seqName, start);
sr = sqlGetResult(conn, query);
row = sqlNextRow(sr);
if (row != NULL)
    cluster = bedLoadN(row+rowOffset, 5);
sqlFreeResult(&sr);

if (cluster != NULL)
    {
    /* Get list of subgroups to display */
    char *inputTableFieldDisplay = trackDbSetting(tdb, "inputTableFieldDisplay");
    if (inputTableFieldDisplay != NULL)
        {
	struct slName *fieldList = stringToSlNames(inputTableFieldDisplay);
	char *inputTrackTable = trackDbRequiredSetting(tdb, "inputTrackTable");

	/* Print out some information about the cluster overall. */
	printf("<B>Items in Cluster:</B> %s of %d<BR>\n", cluster->name, 
	    sqlRowCount(conn, sqlCheckIdentifier(inputTrackTable)));
	printf("<B>Cluster Score (out of 1000):</B> %d<BR>\n", cluster->score);
	printPos(cluster->chrom, cluster->chromStart, cluster->chromEnd, NULL, TRUE, NULL);

	/* In a new section put up list of hits. */
	webNewSection("List of Items in Cluster");
	webPrintLinkTableStart();
	printClusterTableHeader(fieldList, FALSE, FALSE, TRUE);
	printPeakClusterInfo(tdb, cart, conn, inputTrackTable, fieldList, cluster);
	}
    else
	errAbort("Missing required trackDb setting %s for track %s",
	    "inputTableFieldDisplay", tdb->track);
    webPrintLinkTableEnd();
    }
printf("<A HREF=\"%s&g=htcListItemsAssayed&table=%s\" TARGET_blank>", hgcPathAndSettings(),
	tdb->track);
printf("List all items assayed");
printf("</A><BR>\n");
webNewSection("Track Description");
printTrackHtml(tdb);
hFreeConn(&conn);
}