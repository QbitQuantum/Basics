/*
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
*/ 
void CScheduleDB::CreateMsgTableL(RDbDatabase& aDatabase) 
	{
	// Create a table definition
	CDbColSet* columns=CDbColSet::NewLC();
	
	// Add Columns
	TDbCol id(NCol0,EDbColInt32);
	id.iAttributes=id.EAutoIncrement;// automatic indexing for items,it is our key field.
	columns->AddL(id);				 
	columns->AddL(TDbCol(NCol3, EDbColText16,255));
	
	// Create a table
	User::LeaveIfError(aDatabase.CreateTable(KtxtItemlist2,*columns));
				
	// cleanup the column set
	CleanupStack::PopAndDestroy();
}