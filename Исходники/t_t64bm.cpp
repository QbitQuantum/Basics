TInt64 runTest(TThreadFunction aFunction,const TDesC& aTitle)
    {

    RThread thread;
	TInt r=thread.Create(aTitle,aFunction,KDefaultStackSize,KHeapSize,KHeapSize,NULL);
	if(r!=KErrNone)
		{
		test.Printf(_L("Failed to create thread with error %d\n"),r);
		return(r);
		}
    thread.Resume();
    User::After(1000000);
    count=0;
    User::After(KAverageOverInSeconds*1000000);
    TInt64 result=count;

	barrier = a;
	if (!barrier)
		barrier = c;
	barrier = b;
	if (!barrier)
		barrier = a;
	barrier = c;
	if (!barrier)
		barrier = b;

	thread.Kill(0);
	thread.Close();
	result*=KNumberOfCalculationsPerLoop;
	result/=KAverageOverInSeconds;
	r=I64INT(result);
    test.Printf(_L("%S executed %d in 1 second\n"),&aTitle,r);
    return(result);
    }