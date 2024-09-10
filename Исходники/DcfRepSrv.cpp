// -----------------------------------------------------------------------------
// CreateTablesL
// Create table through database session
// -----------------------------------------------------------------------------
//
LOCAL_C void CreateTablesL(RDbDatabase& aDatabase)
{
#ifdef _DRM_TESTING
    WriteL(_L8("CreateTablesL"));
#endif

    CDbColSet* columns = CDbColSet::NewLC();

    //filename columns
    TDbCol filename(KColFilename,EDbColLongText16);
    filename.iAttributes = TDbCol::ENotNull;
    columns->AddL(filename);

    //position columns
    TDbCol position(KColPosition,EDbColUint16);
    position.iAttributes = TDbCol::ENotNull;
    columns->AddL(position);

    //content id columns
    TDbCol cid(KColCid,EDbColLongText16);
    cid.iAttributes = TDbCol::ENotNull;
    columns->AddL(cid);

    //content group id columns
    TDbCol group(KColGroupId,EDbColLongText16);
    columns->AddL(group);

    //transaction id columns
    TDbCol ttid(KColTtid,EDbColText16,KTtidLen);
    columns->AddL(ttid);

    aDatabase.CreateTable( KTable,*columns);
    CleanupStack::PopAndDestroy(columns); //columns

}