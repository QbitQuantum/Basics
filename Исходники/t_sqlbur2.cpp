/**
@SYMTestCaseID			PDS-SQL-UT-4235
@SYMTestCaseDesc		CSqlBurEventMonitor::RunL() - OOM test
						The test sets the backup & restore property status and then checks
						how the backup & restore property monitor (CSqlBurEventMonitor) reacts to the event.
						The test is performed in an OOM loop.
@SYMTestActions			CSqlBurEventMonitor::RunL() - OOM test
@SYMTestExpectedResults Test must not fail
@SYMTestPriority		High
*/
void SqlBurEventMonitorRunOomTest()
	{
	CSqlBurEventMonitor* monitor = NULL;
	TRAPD(err, monitor = CSqlBurEventMonitor::NewL(*TheSqlSrvTestBurInterface));
	
	err = KErrNoMemory;
	TInt failingAllocationNo = 0;
	TheTest.Printf(_L("Iteration:\r\n"));
	while(err == KErrNoMemory)
		{
		TheTest.Printf(_L(" %d"), ++failingAllocationNo);
		
		TInt startProcessHandleCount;
		TInt startThreadHandleCount;
		RThread().HandleCount(startProcessHandleCount, startThreadHandleCount);
		__UHEAP_MARK;
		__UHEAP_SETBURSTFAIL(RAllocator::EBurstFailNext, failingAllocationNo, KBurstRate);

		TEST(!monitor->ActiveBackupClient());
		TEST(!monitor->SqlBurCallback());
		//Set the property, start the scheduler. CSqlBurEventMonitor::RunL() gets called and CSqlBurCallback
		//interface gets created.
		err = RProperty::Set(KSqlBurPropertyCategoryUid, KSqlBurBackupRestoreKey, conn::EBURBackupFull);
		if(err == KErrNone)
			{
			TestModeSqlBurError = KErrNone;
			CActiveScheduler::Start();
			err = TestModeSqlBurError;
			if(err == KErrNone)
				{
				TEST(monitor->ActiveBackupClient() != NULL);
				TEST(monitor->SqlBurCallback() != NULL);
				//Destroy the SQL backup & restore callback
				err = RProperty::Set(KSqlBurPropertyCategoryUid, KSqlBurBackupRestoreKey, conn::EBURNormal);
				TestModeSqlBurError = KErrNone;
				CActiveScheduler::Start();
				err = TestModeSqlBurError;
				if(err == KErrNone)
					{
					TEST(!monitor->ActiveBackupClient());
					TEST(!monitor->SqlBurCallback());
					}
				}
			}
		
		__UHEAP_RESET;
		__UHEAP_MARKEND;
		TInt endProcessHandleCount;
		TInt endThreadHandleCount;
		RThread().HandleCount(endProcessHandleCount, endThreadHandleCount);
		
		TEST2(startProcessHandleCount, endProcessHandleCount);
		TEST2(startThreadHandleCount, endThreadHandleCount);
		}
	TEST2(err, KErrNone);
	TheTest.Printf(_L("\r\n=== OOM Test succeeded at heap failure rate of %d ===\r\n"), failingAllocationNo);
	delete monitor;
	}