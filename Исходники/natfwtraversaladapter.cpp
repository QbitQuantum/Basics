// ---------------------------------------------------------------------------
// CNATFWTraversalAdapter::DeleteL
//
// ---------------------------------------------------------------------------
//
void CNATFWTraversalAdapter::DeleteL( const TDesC8& aSaveData )
    {
    DBG_PRINT( "CNATFWTraversalAdapter::DeleteL - begin" );
    // Central Repository for NAT-FW Traversal settings.
    CRepository* rep = CRepository::NewLC( KCRUidUNSAFProtocols );
    TInt step( 0 );

    // Delete all keys that are stored.
    while ( step < aSaveData.Length() )
        {
        TUint32 key = DesToTUint( aSaveData.Mid( step, KMaxCharsInTUint32 ) );
        key &= KUNSAFProtocolsTableMask;
        TUint32 errorKey;
        rep->Delete( key, KUNSAFProtocolsTableMask, errorKey );
        step += KMaxCharsInTUint32;
        }
    
    CleanupStack::PopAndDestroy( rep );
    DBG_PRINT( "CNATFWTraversalAdapter::DeleteL - end" );
    }