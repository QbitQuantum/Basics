static void DeleteTestDirL()
	{
	RFs fsSession;
	TInt err = fsSession.Connect();
	if(err == KErrNone)
		{
		CleanupClosePushL(fsSession);
		RDebug::Print(_L("Deleting \"%S\" directory.\n"), &KOpaqueDirectory);
		CFileMan* fileMan = CFileMan::NewL(fsSession);
		CleanupStack::PushL(fileMan);
		TInt err = fileMan->RmDir(KOpaqueDirectory);
		if(err == KErrPathNotFound)
			{
			err = KErrNone;
			}
		User::LeaveIfError(err);
		CleanupStack::PopAndDestroy(fileMan);
		CleanupStack::PopAndDestroy(&fsSession);
		}
	else
		{
		RDebug::Print(_L("Error %d connecting file session. Directory: %S.\n"), err, &KOpaqueDirectory);
		}
	}