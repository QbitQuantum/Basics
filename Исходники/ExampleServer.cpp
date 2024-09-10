/*
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
*/
void CExPolicy_Server::CreateTableL(RDbDatabase& aDatabase,TBool aImsi) 
	{
	// Create a table definition
	CDbColSet* columns=CDbColSet::NewLC();
	
	// Add Columns
	TDbCol id(NCol0,EDbColInt32);
	id.iAttributes=id.EAutoIncrement;// automatic indexing for items,it is our key field.
	columns->AddL(id);				 
	
	columns->AddL(TDbCol(NCol1, EDbColText,100));
	columns->AddL(TDbCol(NCol2, EDbColText,100));
	
	// Create a table
	if(aImsi)
		User::LeaveIfError(aDatabase.CreateTable(KtxtImsilist,*columns));
	else
		User::LeaveIfError(aDatabase.CreateTable(KtxtNumberlist,*columns));
				
	// cleanup the column set
	CleanupStack::PopAndDestroy();
}