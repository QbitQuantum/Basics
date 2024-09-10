/**
@SYMTestCaseID SYSLIB-DBMS-CT-0015
@SYMTestCaseDesc OPen table test.
				 This test app has "PowerMgmt" (TABLE A: READ) capability, which allows it to
				 read data from table A. B and C tables can be read too, because they do
				 not have read security policy. The attempts to open A, B and C tables in
				 insert/update mode must fail.
@SYMTestPriority High
@SYMTestActions  Open table test.
@SYMTestExpectedResults The test must not fail.
@SYMREQ REQ2429
                 DBMS shall provide an API to apply security policies to database tables.
*/
static void TblOpenL()
	{
	TheTest.Printf(_L("An attempt to open table A\n"));
	//The test must fail, because the test app cannot satisfy table A, policy W.
	TInt err = TheTbl.Open(TheDb, KTblNameA);
	TEST2(err, KErrPermissionDenied);
	//The test must pass, because the test app can satisfy table A, policy R.
	err = TheTbl.Open(TheDb, KTblNameA, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();

	TheTest.Printf(_L("An attempt to open table B\n"));
	//The test must fail, because the test app cannot satisfy table B, policy W.
	err = TheTbl.Open(TheDb, KTblNameB);
	TEST2(err, KErrPermissionDenied);
	//The test must pass, because table B has no R policy.
	err = TheTbl.Open(TheDb, KTblNameB, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();

	TheTest.Printf(_L("An attempt to open table C\n"));
	//The test must fail, because the test app cannot satisfy table C, policy W.
	err = TheTbl.Open(TheDb, KTblNameC);
	TEST2(err, KErrPermissionDenied);
	//The test must pass, because table C has no R policy.
	err = TheTbl.Open(TheDb, KTblNameC, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();
	}