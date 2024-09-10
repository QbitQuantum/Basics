LOCAL_C void BuildTable(TInt aCount,TBool aTransactions,TUint& aTime,TUint& aSize)
	{
	TUint size=FileSize();
	TUint time=User::TickCount();
	CreateTable();
	if (aTransactions)
		TheDatabase.Begin();
	test(TheTable.Open(TheDatabase,KTableName)==KErrNone);
	WriteRecords(aCount);
	if (aTransactions)
		test(TheDatabase.Commit()==KErrNone);
	TheTable.Close();
	aTime=User::TickCount()-time;
	aSize=FileSize()-size;
	}