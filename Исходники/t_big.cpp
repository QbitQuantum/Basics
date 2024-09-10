/**
@SYMTestCaseID          SYSLIB-DBMS-CT-1312
@SYMTestCaseDesc        Create a table in database
@SYMTestPriority        Medium
@SYMTestActions        	Build a table and write records into the table.Test for commiting the transactions.
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
LOCAL_C void BuildTable(TInt aCount)
	{
	test.Next(_L(" @SYMTestCaseID:SYSLIB-DBMS-CT-1312 "));
#ifndef __TOOLS2__
	TheTimer.Start(_L("build"));
#endif
	CreateTable();
	TheDatabase.Begin();
	test(TheTable.Open(TheDatabase,KTableName)==KErrNone);
	WriteRecords(aCount);
	test(TheDatabase.Commit()==KErrNone);
	TheTable.Close();
#ifndef __TOOLS2__
	TheTimer.Stop();
#endif
	}