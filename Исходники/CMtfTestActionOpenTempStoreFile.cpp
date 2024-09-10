void CMtfTestActionOpenTempStoreFile::ExecuteActionL()
	{
	TestCase().INFO_PRINTF2(_L("Test Action %S start..."), &KTestActionOpenTempStoreFile);
	// Obtain the input parameters
	TMsvId paramEntryId  = ObtainValueParameterL<TMsvId>(TestCase(),ActionParameters().Parameter(0));

	RFs fs;
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);
	
	RMsvServerSession serverSession;
	serverSession.Connect(fs);
	CleanupClosePushL(serverSession);

	RFile file;	
	serverSession.OpenTempStoreFileL(paramEntryId,file);
	CleanupClosePushL(file);
	
	_LIT8(KOpenTempStoreFileTestData,"This is a test data for temporary store file"); 
	TInt error = file.Write(0,KOpenTempStoreFileTestData);
	if(error)
		{
		TestCase().ERR_PRINTF2(_L("Error writing to temporary store file , Error = %d"), error);
		TestCase().SetTestStepResult(EFail);
		}
	else
		{
		TestCase().INFO_PRINTF1(_L("Test data successfully written to temporary store file"));	
		}

	// Close the handles 
	CleanupStack::PopAndDestroy(3,&fs);

	TestCase().INFO_PRINTF2(_L("Test Action %S completed."), &KTestActionOpenTempStoreFile);
	TestCase().ActionCompletedL(*this);
	}