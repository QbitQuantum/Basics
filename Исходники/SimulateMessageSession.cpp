TInt CSimulateMessageServerSession::ReadDataFromFile(RSimMsgDataArray& aArray)
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KDataFile);

	RFile file;
	TInt err = file.Open(rfs, filename, EFileRead);

	if (KErrNone != err)
		{
		return err;
		}
	CleanupClosePushL(file);

	//꾸鱗
	TInt size;
	file.Size(size);

	HBufC8* buffer = HBufC8::NewL(size);
	TPtr8 ptr = buffer->Des();
	file.Read(ptr);

	ParseDataBuffer(buffer,aArray);
	
	delete buffer;

	CleanupStack::PopAndDestroy();
	rfs.Close();

	return KErrNone;
	}