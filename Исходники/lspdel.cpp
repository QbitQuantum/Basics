//
// Function: DeinstallProvider
//
// Description:
//    This is a wrapper for the WSCDeinstallProvider* functions. Depending on
//    which Winsock catalog is specified, this routine calls the right uninstall
//    function.
//
int
DeinstallProvider(
    WINSOCK_CATALOG Catalog,            // Which Winsock catalog to operate on
    GUID           *Guid                // GUID of provider to remove
)
{
    INT     ErrorCode,
            rc;

#ifdef _WIN64
    if ( LspCatalogBoth == Catalog )
    {
        // Remove from 64-bit catalog
        rc = WSCDeinstallProvider( Guid, &ErrorCode );
        if ( SOCKET_ERROR == rc )
        {
            fprintf( stderr, "DeinstallProvider: WSCDeinstallProvider failed: %d\n",
                     ErrorCode
                   );
        }

        // Remove from the 32-bit catalog
        rc = WSCDeinstallProvider32( Guid, &ErrorCode );
        if ( SOCKET_ERROR == rc )
        {
            fprintf( stderr, "DeinstallProvider: WSCDeinstallProvider32 failed: %d\n",
                     ErrorCode
                   );
        }
    }
    else if ( LspCatalog64Only == Catalog )
    {
        // Remove from 64-bit catalog
        rc = WSCDeinstallProvider( Guid, &ErrorCode );
        if ( SOCKET_ERROR == rc )
        {
            fprintf( stderr, "DeinstallProvider: WSCDeinstallProvider failed: %d\n",
                     ErrorCode
                   );
        }
    }
    else
    {
        // Remove from the 32-bit catalog
        rc = WSCDeinstallProvider32( Guid, &ErrorCode );
        if ( SOCKET_ERROR == rc )
        {
            fprintf( stderr, "DeinstallProvider: WSCDeinstallProvider32 failed: %d\n",
                     ErrorCode
                   );
        }
    }
#else
    if ( LspCatalog32Only == Catalog )
    {
        // Remove from the 32-bit catalog
        rc = WSCDeinstallProvider( Guid, &ErrorCode );
        if ( SOCKET_ERROR == rc )
        {
            fprintf( stderr, "DeinstallProvider: WSCDeinstallProvider failed: %d\n",
                     ErrorCode
                   );
        }
    }
    else
    {
        fprintf( stderr, "Unable to remove providers in 64-bit catalog from 32-bit process!\n" );
        return SOCKET_ERROR;
    }
#endif

    return NO_ERROR;
}