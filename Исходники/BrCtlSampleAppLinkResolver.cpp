// ---------------------------------------------------------
// CBrCtlSampleAppLinkResolver::RecognizeL
// ---------------------------------------------------------
//
HBufC* 
CBrCtlSampleAppLinkResolver::RecognizeLC(const TDesC& aFileName, const TDesC8& aData)
    {
    TDataRecognitionResult dataType;
    RApaLsSession apaSession;
    TInt ret;
    HBufC* contentTypeString = NULL;

    User::LeaveIfError(apaSession.Connect());
    // Ask the application architecture to find the file type
    ret = apaSession.RecognizeData(aFileName, aData, dataType);
    apaSession.Close();

    if (ret == KErrNone &&
        (dataType.iConfidence == CApaDataRecognizerType::ECertain) ||
        (dataType.iConfidence == CApaDataRecognizerType::EProbable))
        {
        // If the file type was found, try to match it to a known file type
        TPtrC8 mimeTypePtr = dataType.iDataType.Des8();
        TInt len = mimeTypePtr.Length() + 1;
        contentTypeString = HBufC::NewL(len); 
        contentTypeString->Des().Copy(mimeTypePtr);
        contentTypeString->Des().ZeroTerminate();
        }
    CleanupStack::PushL(contentTypeString);
    return contentTypeString;
    }