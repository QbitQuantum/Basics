void CPolicyImporter::ParseIkeDataL()
    {
    LOG_("-> CPolicyImporter::ParseIkeDataL()");

    HBufC* polFile = iFileUtil.MakeFileNameLC(iImportDir, iCurrPolicyId, KPolFileExt);

    if (!iFileUtil.FileExists(*polFile))
        {
        LOG_("<- CPolicyImporter::ParseIkeDataL() LEAVE (KVpnErrNoPolicyFile)");
        User::Leave(KVpnErrNoPolicyFile);
        }

    HBufC8* fileData = iFileUtil.LoadFileDataL(*polFile);
    CleanupStack::PushL(fileData);

    HBufC* fileData16 = HBufC::NewLC(fileData->Length());

    fileData16->Des().Copy(*fileData);

    delete iCurrIkeDataArray;
    iCurrIkeDataArray = NULL;
    iCurrIkeDataArray = CIkeDataArray::NewL(1);

    TIkeParser* ikeParser = new (ELeave) TIkeParser(*fileData16);
    CleanupStack::PushL(ikeParser);
    ikeParser->ParseIKESectionsL(iCurrIkeDataArray);

    CleanupStack::PopAndDestroy(4); // ikeParser, fileData16, fileData, polFile
    LOG_("<- CPolicyImporter::ParseIkeDataL()");
    }