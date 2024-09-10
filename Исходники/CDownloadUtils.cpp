// -----------------------------------------------------------------------------
// CDownloadUtils::FindContentTypeFromFileL
// -----------------------------------------------------------------------------
//
void CDownloadUtils::FindContentTypeFromFileL( RHttpDownload& aDownload, TUint8*& aContentTypeString)
{
    TDataRecognitionResult dataType;
    RApaLsSession apaSession;
    TInt ret;

    User::LeaveIfError(apaSession.Connect());

    // Create a buffer to hold data from the file
	  TInt bufferSize = 0;
    TInt seekPosition = 0;
	  apaSession.GetMaxDataBufSize(bufferSize);
	  HBufC8* buffer = HBufC8::NewLC(bufferSize);
	  TPtr8 buf = buffer->Des();

	  RFile file;
    HBufC* fileName = HBufC::NewLC( KMaxPath );
    TPtr fileNamePtr = fileName->Des();
    User::LeaveIfError
        ( aDownload.GetStringAttribute( EDlAttrDestFilename, fileNamePtr ) );

    RFs fs;
    User::LeaveIfError( fs.Connect() );
    CleanupClosePushL( fs );

    User::LeaveIfError( file.Open( fs, fileNamePtr, 
										EFileShareAny |
										EFileRead ) );


	  // Find current file pointer position
    file.Seek(ESeekStart, seekPosition);
	  // Read from file
	  file.Read(buf);
	  // return file pointer to original position
    file.Seek(ESeekStart, seekPosition);
    // Ask the application architecture to find the file type
    ret = apaSession.RecognizeData(fileNamePtr, buf, dataType);
    apaSession.Close();

	  CleanupStack::PopAndDestroy(3); //fs, fileName, buffer
    
    if (ret == KErrNone &&
        (dataType.iConfidence == CApaDataRecognizerType::ECertain) ||
        (dataType.iConfidence == CApaDataRecognizerType::EProbable))
        {
        // If the file type was found, try to match it to a known file type
        TPtrC8 mimeTypePtr = dataType.iDataType.Des8();
        TInt len = mimeTypePtr.Length() + 1;
        aContentTypeString = new(ELeave) TUint8 [len];

        TPtr8 contentTypeStringPtr(aContentTypeString, len);
        contentTypeStringPtr.Copy(mimeTypePtr);
        contentTypeStringPtr.ZeroTerminate();
        return;
        }
}