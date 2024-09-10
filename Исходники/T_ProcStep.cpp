/**
 @SYMTestCaseID APPFWK-APPARC-0022

 @SYMPREQ PREQ1123

 @SYMTestCaseDesc The Test determines that the child doesn't receive its parent process ID correctly, when not set during its creation.

 @SYMTestPriority Medium

 @SYMTestStatus Implemented

 @SYMTestActions. Creates and launches a process (parent). Creates another process (child) without setting any parent.
 Parent Process Id is passed to child through SetParameter API. Launches the child process. Child obtains the parent process Id from within.
 Child compares both the Id's. The Id's should not match each other.
 API Calls:\n
 RProcess::Create(const TDesC &aFileName, const TDesC &aCommand, TOwnerType aType=EOwnerProcess);\n
 RProcess::Resume();
 RProcess::ExitType() const;
 RProcess::ExitReason() const;
 RProcess::Id() const;
 RProcess::SetParameter(TInt aSlot, TInt aData);
 CApaCommandLine::SetProcessEnvironmentL(RProcess &aProcess) const;
 CApaCommandLine::NewLC();
 RFile::Open(RFs &aFs, const TDesC &aName, TUint aFileMode);
 RFile::Read(TInt aPos, TDes8 &aDes) const;
 RFile::Close();
 RFs::Connect(TInt aMessageSlots=KFileServerDefaultMessageSlots);
 RFs::Delete(const TDesC &aName);
 RFs::Close();
 @SYMTestExpectedResults Id received by child process should not match its parent process Id.\n

 */
void CT_ProcStep::testIdNotAvailableToChildL(void)
	{
	TInt ret(0);
	TInt exitReason(0);
	
	//commandline for parent process
	CApaCommandLine* parentProcCmdln=CApaCommandLine::NewLC();
	INFO_PRINTF1(_L("	CommandLine for Parent Process created "));

	//parent process
	RProcess parentProc;
	ret = parentProc.Create(KParentExe,KNullDesC);
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	CleanupClosePushL(parentProc);
	INFO_PRINTF2(_L("	Create Parent Process returned : %d"),ret);

	//attach commandline to parent process
	TRAP(ret,parentProcCmdln->SetProcessEnvironmentL(parentProc));
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	INFO_PRINTF1(_L("	Attach CommandLine to Process "));

	INFO_PRINTF1(_L("	Run Parent Process "));
	parentProc.Resume();
	//Time for the parent process to launch itself
	User::After(500000);

	//commandline for child process
	//Get parent process ID here
	TUint64 parentProcId = parentProc.Id();
	INFO_PRINTF2(_L("	Parent Process Id = 0x%lx "),parentProcId);

	CApaCommandLine* childProcCmdln=CApaCommandLine::NewLC();
	INFO_PRINTF1(_L("	CommandLine for Child Process created "));
	
	//child process
	RProcess childProc;
	ret = childProc.Create(KChildThreeExe,KNullDesC);
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	CleanupClosePushL(childProc);
	
	INFO_PRINTF2(_L("	Create Child Process returned : %d"),ret);

	//attach commandline to child process
	TRAP(ret,childProcCmdln->SetProcessEnvironmentL(childProc));
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	INFO_PRINTF1(_L("	Attach CommandLine to Process "));

	//Setting the parent process Id in an environment slot for the child to receive.
	ret = childProc.SetParameter(12,parentProcId);
	TEST(ret == KErrNone);
	INFO_PRINTF2(_L("	Set the Parent Process Id - 0x%lx to Child through SetParameter API in Slot 12 "),parentProcId);

	INFO_PRINTF1(_L("	Run Child Process "));
	TRequestStatus status;
	childProc.Rendezvous(status);
	childProc.Resume();
	//Wait for the child process to launch itself
	User::WaitForRequest(status);

	RFs fs;
	RFile file;
	ret = fs.Connect();
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	INFO_PRINTF1(_L("	Create File server session "));

	ret = file.Open(fs,KFilePath,EFileWrite | EFileShareAny);
	TEST(ret == KErrNone);
	if(ret == KErrNone)
		{
		INFO_PRINTF1(_L("	File opened successfully "));
		TBuf8<5> readData;
		file.Read(0,readData);
		TBuf8<5> result(KTResultFail); 
		TEST(result==readData);
		if(result==readData)
			{
			INFO_PRINTF1(_L("	Child did not receive the parent process ID as intended..."));
			}
		else
			{
			INFO_PRINTF1(_L("	Child received the Wrong parent process ID ..."));
			}
		file.Close();
		fs.Delete(KFilePath);
		fs.Close();
		INFO_PRINTF1(_L("	File Close & Delete and Session Close "));
		}

	TExitType exitType = parentProc.ExitType();
	TEST(exitType == EExitPending);
	if(exitType == EExitPending)
		{
		INFO_PRINTF1(_L("	Parent is still running "));
		INFO_PRINTF1(_L("	So Terminating it manually ... "));
		parentProc.Terminate(KTProcTerminatingParent);
		exitType = parentProc.ExitType();
		TEST(exitType==EExitTerminate);
		exitReason = parentProc.ExitReason();
		TEST(exitReason == KTProcTerminatingParent);
		}

	exitType = childProc.ExitType();
	TEST(exitType == EExitPending);
	if(exitType == EExitPending)
		{
		INFO_PRINTF1(_L("	Child is still running "));
		INFO_PRINTF1(_L("	So Terminating it manually ... "));
		childProc.Terminate(KTProcTerminatingChildIII);
		exitType = childProc.ExitType();
		TEST(exitType==EExitTerminate);
		exitReason = childProc.ExitReason();
		TEST(exitReason == KTProcTerminatingChildIII);
		}

	CleanupStack::PopAndDestroy(&childProc);
	CleanupStack::PopAndDestroy(childProcCmdln);
	CleanupStack::PopAndDestroy(&parentProc);
	CleanupStack::PopAndDestroy(parentProcCmdln);
	}