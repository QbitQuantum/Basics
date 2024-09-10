// -----------------------------------------------------------------------------
// CWPInternetAPDB::CreateTableL
// -----------------------------------------------------------------------------
//  
void CWPInternetAPDB::CreateTableL(RDbDatabase& aDatabase)
    {
    FLOG( _L( "[Provisioning] CWPInternetAPDB::CreateTableL" ) );

    // Create a table definition
    CDbColSet* columns=CDbColSet::NewLC();

    // Add Columns
    TDbCol id(NCol1, EDbColInt32);

    // automatic indexing for items,it is our key field.
    id.iAttributes=id.EAutoIncrement;
    columns->AddL(id);

    columns->AddL(TDbCol(NCol2, EDbColInt32));
    columns->AddL(TDbCol(NCol3, EDbColInt32));
    columns->AddL(TDbCol(NCol4, EDbColText, KOriginatorMaxLength));

    // Create a table
    User::LeaveIfError(aDatabase.CreateTable(KtxtItemlist, *columns) );

    // cleanup the column set
    CleanupStack::PopAndDestroy(columns);
    FLOG( _L( "[Provisioning] CWPInternetAPDB::CreateTableL: done" ) );
    }