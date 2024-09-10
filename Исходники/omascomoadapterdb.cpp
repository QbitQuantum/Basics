// -----------------------------------------------------------------------------
// CWPInternetAPDB::CreateTableL
// -----------------------------------------------------------------------------
//  
void CSCOMOAdapterDb::CreateTableL(RDbDatabase& aDatabase)
    {

    // Create a table definition
    CDbColSet* columns=CDbColSet::NewLC();

    // Add Columns
    TDbCol id(NCol1, EDbColInt32);

    // automatic indexing for items,it is our key field.
    id.iAttributes=id.EAutoIncrement;
    columns->AddL(id);
    columns->AddL(TDbCol(NCol2, EDbColInt32));
    columns->AddL(TDbCol(NCol3, EDbColInt32));
    columns->AddL(TDbCol(NCol4, EDbColText8, 255));
    columns->AddL(TDbCol(NCol5, EDbColText8, 255));
    columns->AddL(TDbCol(NCol6, EDbColText8, 255));
    columns->AddL(TDbCol(NCol7, EDbColInt32));

    //possibility of Panic 

    // Create a table
    TRAPD(err, aDatabase.CreateTable(KTableAMMgmtObject, *columns) );

    if(err!=KErrNone)
    User::Leave(err);

    // cleanup the column set
    CleanupStack::PopAndDestroy(columns);

    }