void refPepList(char *db,
                FILE* outFh)
/* list of sequences needing repair */
{
struct sqlConnection *conn = sqlConnect(db);
struct brokenRefPepTbl *brpTbl;
struct hashCookie cookie;
struct hashEl *hel;
struct extFileTbl* extFileTbl = NULL;

if (!checkForRefLink(conn))
    {
    sqlDisconnect(&conn);
    return;
    }

extFileTbl = extFileTblLoad(conn);
brpTbl = brokenRefPepTblNew(conn, NULL);
brokenRefPepGetSeqScan(conn, extFileTbl, brpTbl);
brokenRefPepGetMrnas(conn, brpTbl);
extFileTblFree(&extFileTbl);

cookie = hashFirst(brpTbl->protAccHash);
while ((hel = hashNext(&cookie)) != NULL)
    {
    struct brokenRefPep *brp = hel->val;
    fprintf(outFh, "%s\t%s\t%s\n", sqlGetDatabase(conn), brp->protAcc, (brp->mrnaAcc != NULL)? "repair" : "drop");
    }
gbVerbMsg(1, "%s: need to repair %d refseq protein gbExtFile entries",
          sqlGetDatabase(conn), brpTbl->numToRepair);
gbVerbMsg(1, "%s: need to drop %d refseq protein gbExtFile entries",
          sqlGetDatabase(conn), brpTbl->numToDrop);
}