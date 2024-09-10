// --------------------------------------------------------------------------
// CImageCapture::GetNextFileNameLC
// Get the file name
// --------------------------------------------------------------------------
HBufC* CImageCapture::GetNextFileNameLC(const TDesC& aName) const
{
    const TInt KNumberLength = 4; // this is to indicate the file numbering,
                                  // e.g. 0001, 0002, etc.
    const TInt KMaxIndex = 10000;
    const TInt KTimeRecordSize = 512;
    
    TPtrC filePathPtr;
    _LIT(KExtensionpng, ".png");
    _LIT(KSlash,"\\");
    
    // Gets the file extension.
    TPtrC fileExtension;
    fileExtension.Set(KExtensionpng);
   
    filePathPtr.Set(iSettings.iLogPath);
    TInt result = filePathPtr.LocateReverse('\\');
    TPtrC string;
    if(result!=KErrNotFound)
    	string.Set(filePathPtr.Left(result+1));
    
    TBuf8<KTimeRecordSize> fileName;
    fileName.Copy(string);
    
    if(iXmlFileName.Length()>0)
    {
    	TInt pos=iXmlFileName.LocateReverse('.');
    	TPtrC8 ptr;
    	if(pos!=KErrNotFound)
    	{
    		ptr.Set(iXmlFileName.Left(pos));
    		fileName.Append(ptr);
    	}
    	
		fileName.Append(KSlash);
    }
    
    fileName.Append(aName);
    HBufC* newFileName = HBufC::NewLC(fileName.Length()+ KNumberLength + fileExtension.Length() + 1);
    TPtr newFileNamePtr(newFileName->Des());
    newFileNamePtr.Copy(fileName);

    
    // Checks whether aNamexxxx.png already exists on the phone or not.
    // This is to prevent over-riding of any existing images with the same name
    TBool IsFileExist = ETrue;
    TInt index = 1;
    HBufC* buffer = HBufC::NewL(newFileNamePtr.MaxLength());
    TPtr bufferPtr(buffer->Des());
    while ((index < KMaxIndex) && (IsFileExist))
    {
        bufferPtr.Copy(newFileNamePtr);
        bufferPtr.AppendNumFixedWidth(index, EDecimal, KNumberLength);
        bufferPtr.Append(fileExtension);
        if (BaflUtils::FileExists(CCoeEnv::Static()->FsSession(), *buffer))
        {
        	index++;
        }
        else
        {
        	IsFileExist = EFalse;
        }
    }
    delete buffer;

    // If the index exceeds KMaxIndex, then we don't need to format the file name.
    if (index >= KMaxIndex)
    {
    	newFileNamePtr.AppendNum(index);
    }
    else
    {
    	newFileNamePtr.AppendNumFixedWidth(index, EDecimal, KNumberLength);
    }
    newFileNamePtr.Append(fileExtension);

    // If the index greated then KMaxIndex, then rollback to 1
    
    if (index >= KMaxIndex)
    {
    	index = 1;
    }
    
    return newFileName;
}