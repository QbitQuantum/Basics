// ---------------------------------------------------------------------------
// Find entry ids of given properties.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CCenRepDatabaseUtil::FindEntryIdsFromPropertiesL( 
    const RIpAppPropArray& aPropertyArray, 
    RArray<TInt>& aEntryIds )
    {
    //CENREPDATABASELOG( "CCenRepDatabaseUtil::FindEntryIdsFromPropertiesL - IN" );
    
    TInt err = FindEntryIdsL( aEntryIds );
    if( err == KErrNone )
        {
        TInt count = aEntryIds.Count();
        TInt removed = 0;
        
        for( TInt i = 0; i < count; i++ )
            {
            TBool ok = EFalse;
            TUint32 entryId = aEntryIds[ i - removed ];
            CheckEntryHasPropertiesL( entryId, aPropertyArray, ok );
            
            if( !ok )
                {
                aEntryIds.Remove( i - removed );
                removed++;
                }
            }
        }
        
    //CENREPDATABASELOG( "CCenRepDatabaseUtil::FindEntryIdsFromPropertiesL - OUT" );
        
    return err;
    }