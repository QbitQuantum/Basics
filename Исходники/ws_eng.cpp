void CWebServerEnv::ReadConfigFileL(const TDesC& aConfigFileName)
//Function which reads and parse the confing file
{

	RFs fs;
#if EPOC_SDK >= 0x06000000
	User::LeaveIfError(fs.Connect());
	HBufC *config = NULL;
	// Need to TRAP leaves, because must close the fs (right).
	// Thus, no point in using the CleanupStack for config either.
	//
	TRAPD(err, config = UnicodeLoad::LoadL(fs, aConfigFileName));
	if (err == KErrNone && config != NULL)
		{
		TLineBuffer buffer(config->Des());
		while (!buffer.EOB())
			{
			TPtrC line = buffer.ReadLine();
			if (line.Length() > 0)
				{
				TRAP(err, ParseConfigLineL(fs, line));
				if (err != KErrNone)
					break;
				}
			}
		}
	delete config;
	fs.Close();
	User::LeaveIfError(err);
#else
	RFile cfg;
	TFileText cfgtxt;
	TBuf<256> buffer;

	User::LeaveIfError(fs.Connect());
	User::LeaveIfError(cfg.Open(fs,aConfigFileName,EFileStreamText));
	
	cfgtxt.Set(cfg);
	User::LeaveIfError(cfgtxt.Seek(ESeekStart));
	cfgtxt.Read(buffer);
	while (buffer.Length() > 0)
	{
		ParseConfigLineL(fs,buffer);
		cfgtxt.Read(buffer);
	}
	
	cfg.Close();

	fs.Close();
#endif
	CheckAndSetDefaultL();

}