bool CDataStorage::Upsert(CToken& t)
{
    OCI_Statement *st;
    char sSQL[1000];
    int rows;
    string token = t.getToken();
//    char *token = replace(orig_token.begin(), orig_token.end(), '.', ' ');
    replace(token.begin(), token.end(), '\'', ' ');

    sprintf(sSQL, "update Concepts set Tokens = '%s', Frequency = %ld, DocFrequency = %ld, Perm = %d where ID = %ld", token.c_str(), t.Freq(), t.DocFreq(), 0, t.DBID());

    st = OCI_StatementCreate(connection);
    if (!st) { return false; }

    if (!OCI_Prepare(st, sSQL) || !OCI_Execute(st)) {
printf("@@@ A\n");
        return false;
    }

    rows = OCI_GetAffectedRows(st);
    if (rows == 0) {
        OCI_StatementFree(st);
        st = OCI_StatementCreate(connection);
        if (!st) { return false; }
        sprintf(sSQL, "insert into Concepts (Tokens, Frequency, DocFrequency, Perm, TokenCount, ID) values ('%s', %ld, %ld, %d, %d, %ld)", token.c_str(), t.Freq(), t.DocFreq(), 0, 1, t.DBID());
        if (!OCI_Prepare(st, sSQL) || !OCI_Execute(st)) {
printf("@@@ B\n");
            return false;
        }
    }

    if (!OCI_Commit(connection)) {
printf("@@@ C\n");
        return false;
    }

    OCI_StatementFree(st);

    return true;
}