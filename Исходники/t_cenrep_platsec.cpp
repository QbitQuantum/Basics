LOCAL_C void CreateSetIntTransactionL()
	{
	CRepository* repository;
	User::LeaveIfNull(repository = CRepository::NewLC(KUidTransactionTestRepository));

	// Remember that this repository need to be reset
	::AddRepositoryToReset(KUidTransactionTestRepository);

	//
	// Integer get/set
	//
	TInt r;
	TInt i = 0;
	const TInt imax = 0x0ff;
	TUint32 errorId;

	r = repository->StartTransaction(CRepository::EReadWriteTransaction);
	repository->CleanupRollbackTransactionPushL();
	TEST2(r, KErrNone);

	// create
	TInt KIntStartValue = 100;
	const TUint32 KNewIntBase = 1;
	for(i=0;i<imax;i++)
		{
		r = repository->Create(KNewIntBase+i, KIntStartValue+i);
		if(OomTesting && (r==KErrNoMemory))
			User::Leave(KErrNoMemory);
		else
			TEST2(r, KErrNone);
		}

	r = repository->CommitTransaction(errorId);
	CleanupStack::Pop();
	if(OomTesting && r!=KErrNone)
		{
		// in OOM test we may have alredy created settings
		TEST2(r, KErrAlreadyExists);
		}
	else
		TEST2(r, KErrNone);

	TInt integer;
	if(!(OomTesting && r==KErrAlreadyExists))
	{
		// during OOM tests we have values from Sets rather then Create...
		for(i=0;i<imax;i++)
			{
			r = repository->Get(KNewIntBase+i,integer );
			TEST2(r, KErrNone);
			TEST(KIntStartValue+i==integer);
			}
	}
	r = repository->StartTransaction(CRepository::EReadWriteTransaction);
	TEST2(r, KErrNone);

    repository->CleanupRollbackTransactionPushL();

	// set
	KIntStartValue = 200;
	for(i=0;i<imax;i++)
		{
		r = repository->Set(KNewIntBase+i, KIntStartValue+i);
		if(OomTesting && (r==KErrNoMemory))
			User::Leave(KErrNoMemory);
		else
			TEST2(r, KErrNone);
		}

	r = repository->CommitTransaction(errorId);
	CleanupStack::Pop();
	TEST2(r, KErrNone);
	for(i=0;i<imax;i++)
		{
		r = repository->Get(KNewIntBase+i,integer );
		TEST2(r, KErrNone);
		TEST(KIntStartValue+i==integer);
		}

	// lets check set where some are going to fail
	// set
	r = repository->StartTransaction(CRepository::EReadWriteTransaction);
	repository->CleanupRollbackTransactionPushL();
	TEST2(r, KErrNone);
	KIntStartValue = 400;
	TInt base = KNewIntBase + 0x7f; // half the range ok other half should fail
	for(i=0;i<imax;i++)
		{
		r = repository->Set(base+i, KIntStartValue+i);
		if(OomTesting && (r==KErrNoMemory))
			User::Leave(KErrNoMemory);
		else
		    {
		    if (base + i < 0x100)
		        {
			    TEST2(r, KErrNone);
		        }
		    else if (base + i == 0x100)
		        {
			    TEST2(r, KErrNone);
		        // this causes transaction to fail
                const TReal KRealValue = 1.234;
		        r = repository->Set(base+i, KRealValue);
			    TEST2(r, KErrArgument);
		        }
		    else
		        {
		        // after transaction has failed, repository returns KErrAbort for every request
			    TEST2(r, KErrAbort);
		        }
		    }
		}

	r = repository->CommitTransaction(errorId);
	TEST2(r, KErrArgument);
	TEST2(errorId, 0x100);
	CleanupStack::Pop();
	// should be able to open again
	r = repository->StartTransaction(CRepository::EReadWriteTransaction);
	TEST2(r, KErrNone);
	repository->RollbackTransaction();

	// and after the failed transaction it should be in previous state!!
	KIntStartValue = 200;
	for(i=0;i<imax;i++)
		{
		r = repository->Get(KNewIntBase+i,integer );
		TEST2(r, KErrNone);
		TEST(KIntStartValue+i==integer);
		}

	// lets clear after ourselves
	for(i=0;i<imax;i++)
		{
		r = repository->Delete(KNewIntBase+i);
		TEST2(r, KErrNone);
		}

	CleanupStack::PopAndDestroy(repository);
	}