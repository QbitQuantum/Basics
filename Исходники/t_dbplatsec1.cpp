/**
@SYMTestCaseID SYSLIB-DBMS-CT-0009
@SYMTestCaseDesc Opening table test. The caller has a set of capabilities which satisfy database's
                 schema security policy only. The test checks that the capapbility checking
				 on the DBMS server side works properly. Some of the initiated open table
				 operations won't executed and the returned error will be KErrPermisssionDenied.
@SYMTestPriority High
@SYMTestActions  Attempts to execute RDbTable::Open() on different tables from the test database.
@SYMTestExpectedResults The test must not fail.
@SYMREQ REQ2429
                 DBMS shall provide an API to apply security policies to database tables.
*/
static void TblOpenL()
	{
	TheTest.Printf(_L("Create tables\n"));
	//The test must pass, because the test app has "SCHEMA" capability
	CDbColSet* colset = TDBSCUtils::CreateColSetLC(KColumns);
	TInt err = TheDb.CreateTable(KTblNameA, *colset);//R: PowerMgmt, W: WriteUserData
	TEST2(err, KErrNone);
	err = TheDb.CreateTable(KTblNameB, *colset);//R: None, W: WriteUserData WriteDeviceData
	TEST2(err, KErrNone);
	err = TheDb.CreateTable(KTblNameC, *colset);//R: None, W: WriteUserData
	TEST2(err, KErrNone);
	CleanupStack::PopAndDestroy(colset);

	TheTest.Printf(_L("An attempt to open table A\n"));
	//The test must fail, because the test app has no capabilities to satisfy
	//R/W policies of table A
	err = TheTbl.Open(TheDb, KTblNameA);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameA, RDbRowSet::EUpdatable);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameA, RDbRowSet::EReadOnly);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameA, RDbRowSet::EInsertOnly);
	TEST2(err, KErrPermissionDenied);

	TheTest.Printf(_L("An attempt to open table B\n"));
	//Open table B in insert/update mode - the test must fail, because the test app has no
	//capabilities to satisfy table B, policy W.
	//Open table B in read-only mode - the test must pass, because table B has no R policy.
	err = TheTbl.Open(TheDb, KTblNameB);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameB, RDbRowSet::EUpdatable);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameB, RDbRowSet::EInsertOnly);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameB, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();

	TheTest.Printf(_L("An attempt to open table C\n"));
	//Open table C in insert/update mode - the test must fail, because the test app has no
	//capabilities to satisfy table C, policy W.
	//Open table C in read-only mode - the test must pass, because table C has no R policy.
	err = TheTbl.Open(TheDb, KTblNameC);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameC, RDbRowSet::EUpdatable);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameC, RDbRowSet::EInsertOnly);
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameC, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();
	}