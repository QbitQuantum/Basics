//Creates a test table
static void CreateTestTableL(RDbNamedDatabase& aDb)
	{
	CDbColSet* colSet = CDbColSet::NewLC();
	for(const TColDef* colDef=KColDefs;colDef->iName;++colDef)
		{
		TDbCol col(TPtrC(colDef->iName), colDef->iType);
		col.iAttributes = colDef->iAttributes;
		colSet->AddL(col);
		}
	TEST2(aDb.CreateTable(KTestTableName, *colSet), KErrNone);
	CleanupStack::PopAndDestroy(colSet);
	}