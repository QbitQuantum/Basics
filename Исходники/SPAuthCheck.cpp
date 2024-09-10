void SPAuthCheckPrv::ReadCheckFile()
{
	// Read check prevention file
	mGameSecondsBeforeNextCheck = 1; // default -> check

	try
	{
		FileReader aReader;
		if(!aReader.Open(gSPAuthCheck_FileName))
			return;

		unsigned short aNumBytes = aReader.ReadShort();
		if(aNumBytes==0 || aReader.Available()<aNumBytes)
			return;

		char *aBuf = new char[aNumBytes];
		std::auto_ptr<char> aDelBuf(aBuf);

		aReader.ReadBytes(aBuf,aNumBytes);
		aReader.Close();

		ByteBufferPtr aDecrypt = mEncryptKey.Decrypt(aBuf,aNumBytes);
		if(aDecrypt.get()==NULL)
			return;

		WONFile aFile(gSPAuthCheck_FileName);

		ReadBuffer aReadBuf(aDecrypt->data(),aDecrypt->length());		
		std::string aSig;
		aReadBuf.ReadString(aSig);
		if(aSig!="magic")
			return;

		time_t aCreateTime = aFile.GetCreateTime();
		time_t aCompareCreateTime = aReadBuf.ReadLong();
		if(aCompareCreateTime != aCreateTime)
			return;

		mGameSecondsBeforeNextCheck = aReadBuf.ReadLong();
		if(mGameSecondsBeforeNextCheck==0) // don't remove file in this case
			return;
		
		aFile.Remove();

	}
	catch(FileReaderException&)
	{
	}
	catch(ReadBufferException&)
	{
	}
}