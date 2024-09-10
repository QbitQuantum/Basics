// ---------------------------------------------------------
// RFavouritesSrvTable::CreateStructureL
// ---------------------------------------------------------
//
void RFavouritesSrvTable::CreateStructureL( RDbNamedDatabase& aDb )
{
    // Create columns.
    CDbColSet* colset = CDbColSet::NewLC();

    TDbCol col( KFavouritesDbUidColName, EDbColInt32 );
    col.iAttributes = TDbCol::EAutoIncrement;
    colset->AddL( col );
    colset->AddL( TDbCol( KFavouritesDbParentColName, EDbColInt32 ) );
    colset->AddL( TDbCol( KFavouritesDbTypeColName, EDbColInt32 ) );
    colset->AddL( TDbCol
                  ( KFavouritesDbNameColName, EDbColText, KFavouritesMaxName ) );
    colset->AddL( TDbCol
                  ( KFavouritesDbUrlColName, EDbColLongText, KFavouritesMaxUrl ) );
    colset->AddL( TDbCol( KFavouritesDbApIdColName, EDbColUint32 ) );
    colset->AddL( TDbCol( KFavouritesDbApValueKindColName, EDbColInt32 ) );
    colset->AddL( TDbCol
                  ( KFavouritesDbUserNameColName, EDbColText, KFavouritesMaxUserName ) );
    colset->AddL( TDbCol
                  ( KFavouritesDbPasswordColName, EDbColText, KFavouritesMaxPassword ) );
    colset->AddL( TDbCol( KFavouritesDbExtraDataColName, EDbColLongBinary ) );
    colset->AddL( TDbCol( KFavouritesDbFactoryItemColName, EDbColBit ) );
    colset->AddL( TDbCol( KFavouritesDbReadOnlyColName, EDbColBit ) );
    colset->AddL( TDbCol( KFavouritesDbContextIdColName, EDbColInt32 ) );
    colset->AddL( TDbCol( KFavouritesDbModifiedColName, EDbColDateTime ) );
    colset->AddL( TDbCol( KFavouritesDbPrefUidColName, EDbColInt32 ) );
    colset->AddL
    ( TDbCol( KFavouritesDbBrowserDataColName, EDbColLongBinary ) );
    colset->AddL( TDbCol( KFavouritesDbHiddenColName, EDbColBit ) );
    User::LeaveIfError
    ( aDb.CreateTable( KFavouritesTableName, *colset ) );
    CleanupStack::PopAndDestroy();  // colset

    // Create index by uid.
    CDbKey* key = CDbKey::NewLC();
    // Create key on Uid column, ascending order.
    key->AddL( TDbKeyCol ( KFavouritesDbUidColName ) );
    User::LeaveIfError( aDb.CreateIndex
                        ( KFavouritesDbUidIdxName, KFavouritesTableName, *key ) );
    CleanupStack::PopAndDestroy();  // key
}