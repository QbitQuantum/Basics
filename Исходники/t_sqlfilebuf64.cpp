/**
@SYMTestCaseID			PDS-SQL-UT-4207
@SYMTestCaseDesc		RFileBuf64::Write() OOM test.
						The test calls RFileBuf64:Write() in an OOM
						simulation loop and verifies that no memory is leaked.
						The test also check that RFileBuf::DoSetCapacity() correctly operates in
						"out of memory" situation.
@SYMTestActions			RFileBuf64::Write() OOM test.
@SYMTestExpectedResults Test must not fail
@SYMTestPriority		High
@SYMDEF					380056
*/
void WriteOomTest()
	{
	HBufC8* databuf = HBufC8::New(KPageSize);
	TEST(databuf != NULL);
	TPtr8 dataptr = databuf->Des();
	dataptr.SetLength(KPageSize);
	dataptr.Fill(TChar(KChar));
	
	TInt err = KErrNoMemory;
	TInt failingAllocationNo = 0;
	TheTest.Printf(_L("Iteration:\r\n"));
	while(err == KErrNoMemory)
		{
		TheTest.Printf(_L(" %d"), ++failingAllocationNo);

		(void)TheFs.Delete(KTestFile);
		
		MarkHandles();
		MarkAllocatedCells();
		
		__UHEAP_MARK;
		__UHEAP_SETBURSTFAIL(RAllocator::EBurstFailNext, failingAllocationNo, KBurstRate);

		const TInt KDefaultBufCapacity = 1024;
		RFileBuf64 fbuf(KDefaultBufCapacity);
		err = fbuf.Create(TheFs, KTestFile, EFileWrite | EFileRead);
		if(err == KErrNone)
			{
			err = fbuf.Write(0LL, dataptr);
			}
		fbuf.Close();
		
		__UHEAP_RESET;
		__UHEAP_MARKEND;

		CheckAllocatedCells();
		CheckHandles();
		}
	TEST2(err, KErrNone);
	RFile64 file;
	err = file.Open(TheFs, KTestFile, EFileRead);
	TEST2(err, KErrNone);
	dataptr.Zero();
	err = file.Read(dataptr);
	TEST2(err, KErrNone);
	file.Close();
	TEST2(dataptr.Length(), KPageSize);
	for(TInt i=0;i<KPageSize;++i)
		{
		TEST(dataptr[i] == KChar);
		}
	TheTest.Printf(_L("\r\n=== OOM Test succeeded at heap failure rate of %d ===\r\n"), failingAllocationNo);
	
	//The file is left undeleted - to be used in ReadOomTest().
	delete databuf;
	}