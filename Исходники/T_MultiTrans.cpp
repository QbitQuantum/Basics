void CTextModeTestMultiTrans::ValidateBodyL(RHTTPTransaction aTransaction)
{
    // In this test, the test URLs point to resources that contain just characters from the test number
    // i.e. http:/xxx/1.txt will contain only the char 1, CR or LF.
    // These numbers should also align with the transaction ID, since they were created in order
    RHTTPResponse resp = aTransaction.Response();
    MHTTPDataSupplier* body = resp.Body();
    TPtrC8 data;
    body->GetNextDataPart(data);
    TChar reqdCh = (TChar)(aTransaction.Id() + 48);
    for (TInt ii = 0; ii < data.Length(); ii++)
    {
        TChar ch = data[ii];
        if ((ch != reqdCh) && (ch != (TChar)0x0d) && (ch != (TChar)0x0a))
            User::Leave(KMultiTransFailed);
    }

    // OK - release the block
    body->ReleaseData();
}