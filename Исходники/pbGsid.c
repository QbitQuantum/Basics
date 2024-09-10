void makeActiveImagePB(char *psOutput, char *psOutput2)
/* Make image and image map. */
{
char *mapName = "map";
int pixWidth, pixHeight;

struct sqlConnection *conn;
char query[256];
struct sqlResult *sr;
char **row;

int  iypos;
char *spDisplayId;
char *oldDisplayId;
conn  = sqlConnect(UNIPROT_DB_NAME);
printf("<BR>");
hPrintf("<BR><font size=4><B>Protein: ");
hPrintf("%s</B>", proteinID);

/* Please note the hiv database name is hard wired here.*/
safef(query, sizeof(query), 
"select subjId from hivVax003Vax004.gsIdXref where aaSeqId = '%s'", proteinID);
sr = sqlMustGetResult(conn, query);
row = sqlNextRow(sr);
if (row != NULL)
    {
    printf("<BR>");
    hPrintf("<font size=4><B>Subject: ");
    hPrintf("<A HREF=\"../cgi-bin/gsidSubj?hgs_subj=%s&submit=Go!\">", row[0]);
    hPrintf("%s</A></B><BR>", row[0]);
    }
sqlFreeResult(&sr);

spDisplayId = spAccToId(conn, spFindAcc(conn, proteinID));
if (strstr(spDisplayId, spFindAcc(conn, proteinID)) == NULL)
	{
	hPrintf(" (aka %s", spDisplayId);
	/* show once if the new and old displayId are the same */
 	oldDisplayId = oldSpDisplayId(spDisplayId);
	if (oldDisplayId != NULL)
 	    {
            if (!sameWord(spDisplayId, oldDisplayId))
	    	{
	    	hPrintf(" or %s", oldSpDisplayId(spDisplayId));
	    	}
	    }
	hPrintf(")\n");
	}
hPrintf("</font><br>");

protSeq = getAA(proteinID);
if (protSeq == NULL)
    {
    errAbort("%s is not a current valid entry in UniProt(SWISS-PROT/TrEMBL)\n", proteinID);
    }
protSeqLen = strlen(protSeq);

fflush(stdout);

iypos = 15; 
doTracks(proteinID, mrnaID, protSeq, &iypos, psOutput);
if (!hTableExists(database, "pbStamp")) goto histDone; 

pbScale = 3;
pixWidth = 520;
insideWidth = pixWidth-gfxBorder;

pixHeight = 350;

if (psOutput2)
    {
    vg2 = vgOpenPostScript(pixWidth, pixHeight, psOutput2);
    }
else
    {
    trashDirFile(&gifTn2, "pbt", "pbt", ".gif");
    vg2 = vgOpenGif(pixWidth, pixHeight, gifTn2.forCgi, FALSE);
    }

g_vg = vg2;

pbRed    = vgFindColorIx(vg2, 0xf9, 0x51, 0x59);
pbBlue   = vgFindColorIx(g_vg, 0x00, 0x00, 0xd0);

normalColor   = pbBlue;
abnormalColor = pbRed;

bkgColor = vgFindColorIx(vg2, 255, 254, 232);
vgBox(vg2, 0, 0, insideWidth, pixHeight, bkgColor);

/* Start up client side map. */
mapName=cloneString("pbStamps");
hPrintf("\n<MAP Name=%s>\n", mapName);

vgSetClip(vg2, 0, gfxBorder, insideWidth, pixHeight - 2*gfxBorder);
iypos = 15;

/* Draw stamps. */

doStamps(proteinID, mrnaID, protSeq, vg2, &iypos);

/* Finish map. */
hPrintf("</MAP>\n");

/* Save out picture and tell html file about it. */
vgClose(&vg2);
hPrintf("<P>");

hPrintf("\n<IMG SRC=\"%s\" BORDER=1 WIDTH=%d HEIGHT=%d USEMAP=#%s><BR>",
            gifTn2.forCgi, pixWidth, pixHeight, mapName);
if (proteinInSupportedGenome)
    {
    hPrintf("\n<A HREF=\"../goldenPath/help/pbTracksHelpFiles/pbTracksHelp.shtml#histograms\" TARGET=_blank>");
    }
else
    {
    hPrintf("\n<A HREF=\"../goldenPath/help/pbTracksHelpFiles/pbGsid/pbTracksHelp.shtml#histograms\" TARGET=_blank>");
    }

hPrintf("Explanation of Protein Property Histograms</A><BR>");

hPrintf("<P>");

histDone:

hPrintf("<P>");
fflush(stdout);

printFASTA(proteinID, protSeq);
}