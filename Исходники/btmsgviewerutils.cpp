void CBtMsgViewerUtils::StoreMessageMimeTypeL(TPtr aMsgPath)
    {
    RFs rfs;
    RFile file;
    
    User::LeaveIfError(rfs.Connect());
    
    User::LeaveIfError(rfs.ShareProtected());
    
    User::LeaveIfError(file.Open(rfs, aMsgPath, EFileShareReadersOrWriters | EFileRead));
    
    TDataRecognitionResult dataType;
    RApaLsSession apaSession;
    
    if(apaSession.Connect() == KErrNone)
        {
        if (apaSession.RecognizeData(file, dataType) == KErrNone)
            {
            if(iMimeType)
                {
                delete iMimeType;
                iMimeType = NULL;
                }
        
            iMimeType = dataType.iDataType.Des8().AllocL();
            
            rfs.Close();
            apaSession.Close();
            }
        }

    rfs.Close();
    }