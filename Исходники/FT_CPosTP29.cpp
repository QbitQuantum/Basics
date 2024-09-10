// ---------------------------------------------------------
// CPosTp29::CopyResourceFileL
// 
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CPosTp29::CopyResourceFileL(const TDesC& aResourceFile)
    {
    // Release all landmark references to make DLLs be unloaded.
    delete iLandmarksDb;
    iLandmarksDb = NULL;

    CFileMan* fileMan = CFileMan::NewL(iFileServer);
    CleanupStack::PushL(fileMan);
    
    // Check if landmark is flashed
     if (!BaflUtils::FileExists(iFileServer, KInternalServicesResFileRom))
        {
         iLog->Put(_L("Landmark is NOT flashed, backing up eposlmintservices.rsc by renaming it bofore copying rsc-file."));
        // Landmark FW is not flashed. Rename the file before copying an own defiend file.
        // Since landmark FW is not flashed the file should exist hence leaving if it is not found!
         User::LeaveIfError(fileMan->Rename(KInternalServicesResFileCdrive, KInternalServicesResFileBackup, CFileMan::EOverWrite));
        }
     else
        {
        iLog->Put(_L("Landmark framework is flashed, copying global categories to c:"));
        }

    User::LeaveIfError(fileMan->Copy(aResourceFile, KInternalServicesResFileCdrive, CFileMan::EOverWrite));
 
    CleanupStack::PopAndDestroy(fileMan);
    }