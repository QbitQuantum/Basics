void CSocketsWriter::IssueWriteL(const TDesC8& aData)
    {
    if (((iWriteStatus != EWaiting) && (iWriteStatus != ESending)) || (!fileBuffer))
	{   
		iAppUi->LogInfo(_L("Write Exit"));
		if (!fileBuffer)
			iAppUi->LogInfo(_L("NULL File pointer"));
		User::Leave(KErrNotReady);
	}
    //iGlobalEngine->LogInfo(_L("fileBuffer->Write:%d"),aData.Length());
    TRAPD(iErr, fileBuffer->Write(m_iSizeFile+1, aData));
	if (iErr==KErrNone){
	    m_iSizeFile+=aData.Length();
	    if (!IsActive())
	        SendNextPacket();
	    
		}
	else
		iAppUi->LogInfo(_L("ERROR fileBuffer->Write"));
    }