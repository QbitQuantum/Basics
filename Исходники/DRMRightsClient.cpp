// -----------------------------------------------------------------------------
// RDRMRightsClient::DeleteDbEntry
// Delete a single rights object identified by given parameters.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt RDRMRightsClient::DeleteDbEntry( const TDesC8& aContentID,
                                               const TDRMUniqueID& aUniqueID )
    {
    DRMLOG( _L( "RDRMRightsClient::DeleteDbEntry with CID & UID" ) );

    if ( aContentID.Length() )
        {
        // Something to do.
        // Put aUniqueID inside a descriptor.
        // Works even if its typedef is changed.
        TPtrC8 uid( reinterpret_cast< TUint8* >(
                        const_cast< TDRMUniqueID* >( &aUniqueID ) ),
                    sizeof( TDRMUniqueID ) );

        return SendReceive( DRMEngine::EDeleteRO,
                            TIpcArgs( &uid, NULL, NULL, &aContentID ) );
        }

    return KErrArgument;
    }