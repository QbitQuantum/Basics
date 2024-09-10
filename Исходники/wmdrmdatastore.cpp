void CWmDrmDataStore::UpdateDummyDbFileL( TInt aSize, TBool aConfiguredDrive )
    {
    LOGFN( "CWmDrmDataStore::UpdateDummyDbFileL" );
    LOG2( "aSize: %d", aSize );
    if ( aSize > 0 )
        {
        TInt dummyDbSize( DummyDBSizeL( aConfiguredDrive ) );
        LOG2( "dummyDbSize: %d", dummyDbSize );
        if ( aSize <= dummyDbSize )
            {
            if ( aConfiguredDrive )
                {
                User::LeaveIfError( iDummyDb2.SetSize( dummyDbSize - aSize ) );
                }
            else
                {
                User::LeaveIfError( iDummyDb.SetSize( dummyDbSize - aSize ) );
                }
            }
        else
            {
            if ( aConfiguredDrive )
                {
                User::LeaveIfError( iDummyDb2.SetSize( 0 ) );
                }
            else
                {
                User::LeaveIfError( iDummyDb.SetSize( 0 ) );
                }
            }
        }
    else
        {
        TInt dataStoreSize( DataStoreSizeL( aConfiguredDrive ) );
        LOG2( "dataStoreSize: %d", dataStoreSize );
        if ( aConfiguredDrive )
            {
            if ( dataStoreSize <= iDummyDbInitialSize2 )
                {
                User::LeaveIfError(
                    iDummyDb2.SetSize( iDummyDbInitialSize2 - dataStoreSize ) );
                }
            else
                {
                User::LeaveIfError( iDummyDb2.SetSize( 0 ) );
                }
            }
        else
            {
            if ( dataStoreSize <= iDummyDbInitialSize )
                {
                User::LeaveIfError(
                    iDummyDb.SetSize( iDummyDbInitialSize - dataStoreSize ) );
                }
            else
                {
                User::LeaveIfError( iDummyDb.SetSize( 0 ) );
                }
            }
        }
    }