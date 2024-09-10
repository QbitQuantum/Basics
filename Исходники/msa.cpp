int CreateCallContextTable(Ndb* pNdb, const char* szTableName, bool bStored)
{
    int iRes = -1;
    NdbError err;
    memset(&err, 0, sizeof(err));

    NdbSchemaCon* pNdbSchemaCon = NdbSchemaCon::startSchemaTrans(pNdb);
    if(pNdbSchemaCon)
    {
        NdbSchemaOp* pNdbSchemaOp = pNdbSchemaCon->getNdbSchemaOp();
        if(pNdbSchemaOp)
        {
            if(!pNdbSchemaOp->createTable(szTableName, 8, TupleKey, 2, 
                All, 6, 78, 80, 1, bStored)
                && !pNdbSchemaOp->createAttribute(c_szContextId, TupleKey, 32, 1, Signed)
                && !pNdbSchemaOp->createAttribute(c_szVersion, NoKey, 32, 1, Signed)
                && !pNdbSchemaOp->createAttribute(c_szLockFlag, NoKey, 32, 1, Signed)
                && !pNdbSchemaOp->createAttribute(c_szLockTime, NoKey, 32, 1, Signed)
                && !pNdbSchemaOp->createAttribute(c_szLockTimeUSec, NoKey, 32, 1, Signed)
                && !pNdbSchemaOp->createAttribute(c_szContextData, NoKey, 8, g_nStatusDataSize, String)) 
            {
                if(!pNdbSchemaCon->execute()) 
                    iRes = 0;
                else 
                    err = pNdbSchemaCon->getNdbError();
            } 
            else 
                err = pNdbSchemaOp->getNdbError();
        } 
        else 
            err = pNdbSchemaCon->getNdbError();

        NdbSchemaCon::closeSchemaTrans(pNdbSchemaCon);
    }
    else 
        err = pNdb->getNdbError();

    if(iRes)
    {
        ReportNdbError("create call context table failed", err);
    }
    return iRes;
}