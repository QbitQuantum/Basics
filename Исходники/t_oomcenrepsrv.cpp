void CenrepSrvOOMTest::DeleteL()
	{
	TInt ret=KErrNone;
	//--------------Delete-----------------------------------
	//Find the settings 0x10A-0x10C to ensure it is still there
	RSettingPointerArray matchingArray;
	TUint32 partialId=0x100;
	TUint32 idMask=0xFFFFFFF0;
	ret=iServerRepo->FindSettings(partialId,idMask,matchingArray);
	if (ret==KErrNoMemory)
		{
		matchingArray.Close();
		User::LeaveNoMemory();
		}

	TESTKErrNoneL(ret);
	TESTL(matchingArray.Count()==3);
	matchingArray.Close();

	//Deleting settings 0x10A to 0x10C
	for (TInt i=0x10A;i<=0x10C;i++)
		{
		RepositorySingleDeleteL(*iServerRepo, i);
		TESTKErrNoneL(ret);
		}
	//After deleting try to find the persistent settings again
	ret=iServerRepo->FindSettings(partialId,idMask,matchingArray);
	if (ret==KErrNoMemory)
		{
		matchingArray.Close();
		User::LeaveNoMemory();
		}
	TESTKErrNoneL(ret);
	TESTL(matchingArray.Count()==0);
	matchingArray.Close();

	//-------------DeleteRange---------------------------------
	//Deleting settings 0x1 to 0xF
	TClientRequest dummyrequest;
	TUint32 errId=0;
	partialId=0;
	idMask=0xFFFFFFF0;
	ret=iServerRepo->FindSettings(partialId,idMask,matchingArray);
	if (ret==KErrNoMemory)
		{
		matchingArray.Close();
		User::LeaveNoMemory();
		}
	TESTKErrNoneL(ret)	;
	TESTL(matchingArray.Count()==15);
	matchingArray.Close();

	//Deleting settings using the DeleteRange
	dummyrequest.SetParam(0,partialId);
	dummyrequest.SetParam(1,idMask);
	dummyrequest.SetPolicyCheck(ETrue);

	// write operation must take place in a transaction
	iServerRepo->StartTransaction(EConcurrentReadWriteTransaction);
	iServerRepo->CleanupCancelTransactionPushL();
	iServerRepo->TransactionDeleteRangeL(dummyrequest,errId);
	CleanupStack::Pop();
	TUint32 keyInfo;
	User::LeaveIfError(iServerRepo->CommitTransaction(keyInfo));

	//Now try to find the key being deleted
	ret=iServerRepo->FindSettings(partialId,idMask,matchingArray);
	if (ret==KErrNoMemory)
		{
		matchingArray.Close();
		User::LeaveNoMemory();
		}
	TESTKErrNoneL(ret);
	TESTL(matchingArray.Count()==0);
	matchingArray.Close();
	}