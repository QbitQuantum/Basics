/**
 * Load and initialise an audio file.
 */
TVerdict CTestMmfVclntOpenFile0522::DoTestStepL()
	{
	TVerdict ret = EFail;

	INFO_PRINTF1(_L("Test : Video Recorder - OpenFileL(RFile&)"));

	RFs		fs;
	RFile	file;

	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);
	User::LeaveIfError(fs.ShareProtected());

	iError = KErrTimedOut;

	TPtrC filename;
	if(!GetStringFromConfig(iSectName,iKeyName,filename))
		{
		return EInconclusive;
		}

	User::LeaveIfError(file.Open(fs,filename,EFileWrite));
	CleanupClosePushL(file);
	CVideoRecorderUtility* rec = CVideoRecorderUtility::NewL(*this);
	CleanupStack::PushL(rec);

	const TUid KVidTstControllerUid = {KMmfVideoTestControllerUid};
	TRAP(iError,rec->OpenFileL(file, NULL, KVidTstControllerUid, KUidMdaBmpClipFormat));

	if(iError == KErrNone)
		{
		INFO_PRINTF1(_L("CVideoRecorderUtility: Open file"));
		// Wait for initialisation callback
		CActiveScheduler::Start();
		}

	if(iError == KErrNotSupported)
		{
		ret = EPass;
		}

	// Check for errors.
	if ((iError == KErrNone) && (rec != NULL))
		{
		rec->Prepare();
		CActiveScheduler::Start();
		if(iError != KErrNone)
			{
			INFO_PRINTF2(_L("Prepare callback : error %d"), iError);
			return EInconclusive;
			}

		if(iRec)
			{
			iError = KErrTimedOut;
			rec->Record();
			INFO_PRINTF1(_L("CVideoRecorderUtility: Record"));
			// Wait for init callback
			CActiveScheduler::Start();
			if(iError == KErrNone)
				{
				ret = EPass;
				}
			User::After(1000000);
			rec->Stop();
			}
		else
			{
			ret = EPass;
			}
		}

	rec->Close();
	
	INFO_PRINTF1(_L("CVideoRecorderUtility: Destroy"));
	CleanupStack::PopAndDestroy(rec);
	User::After(KOneSecond); // wait for deletion to shut down devsound
	if(iError != KErrNone)
		{
		ERR_PRINTF2( _L("CVideoRecorderUtility failed with error %d"),iError );
		}

	CleanupStack::PopAndDestroy(2,&fs);
	
	return	ret;
	}