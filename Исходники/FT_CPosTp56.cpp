// ---------------------------------------------------------
// CPosTp56::CreateDatabasesL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CPosTp56::CreateDatabasesL()
    {
    // Paths will need to be changed to the secure dbms path when security is implemented
   
    _LIT(KDefaultDbPath, "c:\\system\\data\\eposlm.ldb");

    _LIT(KDb1Path, "c:\\system\\data\\eposlm1.ldb");
    _LIT(KDb2Path, "c:\\system\\data\\eposlm2.ldb");
    _LIT(KDb3Path, "c:\\system\\data\\eposlm3.ldb");

    CPosLandmarkDatabase* lmd = CPosLandmarkDatabase::OpenL();
    CleanupStack::PushL(lmd);

    if (lmd->IsInitializingNeeded())
        {
        ExecuteAndDeleteLD(lmd->InitializeL()); 
        }
    
    CleanupStack::PopAndDestroy(lmd);  

    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);
   
    fs.Delete(KExportFile);

    CFileMan* fileMan = CFileMan::NewL(fs);
    CleanupStack::PushL(fileMan);

    User::LeaveIfError(fileMan->Copy(KDefaultDbPath, KDb1Path, CFileMan::EOverWrite));    
    User::LeaveIfError(fileMan->Copy(KDefaultDbPath, KDb2Path, CFileMan::EOverWrite));    
    User::LeaveIfError(fileMan->Copy(KDefaultDbPath, KDb3Path, CFileMan::EOverWrite));  


    CleanupStack::PopAndDestroy(2, &fs);  
    }