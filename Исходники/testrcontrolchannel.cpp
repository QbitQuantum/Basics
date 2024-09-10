void CTestRControlChannel::SavePreviousLogFileL()
	{
	_LIT(KInfoLogFile, "Saving Previous logs If any.... \n");
	INFO_PRINTF1(KInfoLogFile);
	RFs fileserv;
	TInt error = fileserv.Connect();
	if(!error)
		{
		_LIT(KlogFile, "C:\\logs\\log.txt");
		_LIT(KPrefixLog, "C:\\logs\\");
		_LIT(KSuffix, "_UDEB");
		_LIT(KExtn, ".txt");
		
		CFileMan* fMan = NULL;
		TRAP_IGNORE(fMan = CFileMan::NewL(fileserv));
		if(fMan != NULL)
			{
			CleanupStack::PushL(fMan);
			RBuf newFileName;
			const TInt KTwenty = 20;
			newFileName.Create(ConfigSection().Length() + KTwenty );
			newFileName.Copy(KPrefixLog);
			//Script file name
			iScriptName.Copy(ConfigSection());
			newFileName.Append(iScriptName);
			newFileName.Append(KSuffix);
			newFileName.Append(KExtn);
			
			TInt error = fMan->Rename(KlogFile, newFileName);
			if (error != KErrNone)
				{
				_LIT(KErrInfo, "Unable to Save Previous logs...May be NO Previous logs exist \n");
				ERR_PRINTF1(KErrInfo);
				}
			else
				{
				_LIT(KSavingInfo, "Saved Previous logs with File Name: %S \n");
				INFO_PRINTF2(KSavingInfo, &newFileName);
				}
			CleanupStack::PopAndDestroy(fMan);
			newFileName.Close();
			}
		}
	fileserv.Close();
	_LIT(KInfoLogFile1, "Saving Previous logs End.... \n");
	INFO_PRINTF1(KInfoLogFile1);
	}