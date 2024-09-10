/**
@SYMTestCaseID          SYSLIB-BAFL-CT-0439
@SYMTestCaseDesc        Timing Tests
@SYMTestPriority        High
@SYMTestActions         Check for the time loads needed to repeatedly load a resource
@SYMTestExpectedResults Tests must not fail
@SYMREQ                 REQ0000
*/
void TRsReadTester::TimingTestsL()
	{
	test.Next(_L(" @SYMTestCaseID:SYSLIB-BAFL-CT-0439 Timing tests "));
	test.Next(_L("BUTTON and FLPTED"));
	TUint time = User::TickCount();
	for (TInt ii=0; ii<100; ii++)
		{
    	TResourceReader reader;
    	CreateResourceReaderLC(reader,SYS_BUTTON_ONE);
	    CleanupStack::PopAndDestroy();
	    CreateResourceReaderLC(reader,SYS_FLPTED_ONE);
    	CleanupStack::PopAndDestroy();
		}
	time = User::TickCount() - time;
    test.Printf(_L("Time to load 100 times: %d\n"),time);

	test.Next(_L("BUTTON and ARRAY"));
	time = User::TickCount();
	for (TInt jj=0; jj<100; jj++)
		{
    	TResourceReader reader;
    	CreateResourceReaderLC(reader,SYS_BUTTON_ONE);
	    CleanupStack::PopAndDestroy();
	    CreateResourceReaderLC(reader,SYS_ARRAY_ONE);
    	CleanupStack::PopAndDestroy();
		}
	time = User::TickCount() - time;
    test.Printf(_L("Time to load 100 times: %d\n"),time);
	}