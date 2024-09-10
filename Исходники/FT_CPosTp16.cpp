// ---------------------------------------------------------
// CPosTp16::UseContactDbL
// 
// (other items were commented in a header).
// ---------------------------------------------------------
//
CPosLandmarkDatabase* CPosTp16::UseContactDbL()
    {
    RemoveDefaultDbL();
    
    #ifdef __WINS__
        _LIT(KCorruptDbFile, "z:\\system\\test\\testdata\\SRVeposcontact.ldb");
    #else
        _LIT(KCorruptDbFile, "c:\\system\\test\\testdata\\SRVeposcontact.ldb");
    #endif
    
    _LIT(KCorruptDbFileOld, "c:\\system\\data\\SRVeposcontact.ldb");

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);
    
    CFileMan* fileMan = CFileMan::NewL(fs);
    CleanupStack::PushL(fileMan);
    
    User::LeaveIfError(fileMan->Copy(KCorruptDbFile, KDefaultDbPath, CFileMan::EOverWrite));
    User::LeaveIfError(fileMan->Rename(KCorruptDbFileOld, KDefaultDb, CFileMan::EOverWrite));
    
    CleanupStack::PopAndDestroy(2, &fs);
    
    return CPosLandmarkDatabase::OpenL();
    }