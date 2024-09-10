//
// Function: BuildLspMap
//
// Description:
//    This routine builds a map of all LSPs installed according to what order
//    they are in the catalog. That is, the information returned will be ordered
//    in the way the LSPs need to be installed. For example if LSP1 is installed
//    over the base TCP and UDP providers and LSP2 is installed over LSP1, then 
//    this routine will return two LSP_ENTRY structures with LSP1 first followed
//    by LSP2. The algorithm for determining the order is to first sort by where
//    a base provider ID occurs in an LSP chain with lower numbered ones first.
//    For example, LSP1 layered directly over TCP will have a base ID (TCP) in
//    chain position 1 while LSP (layered over LSP1) will have the base ID in
//    chain index 2. This is the ChainOrder field (and it is the minimum value
//    for all layered providers). After this first sort, it is possible to have
//    several LSPs with the same ChainOrder value. Within these groupings the
//    entries are sorted by the maximum LSP chain length. Each LSP has a number
//    of layered providers each with its own chain (and the chains could be
//    different lengths). The MaxChainLength value is the longest chain length
//    of all providers belonging to a given LSP. Each grouping of LspOrder is then
//    sorted by MaxChainLengthin ascending order.
//
LSP_ENTRY *
BuildLspMap(
    WSAPROTOCOL_INFOW *pProviders,
    int                iProviderCount,
    int               *pLspCount
    )
{
    LSP_ENTRY *pLsps = NULL,
               lsptmp;
    DWORD     *pBaseList = NULL;
    int        iLspCount = 0,
               iSortLspCount = 0,
               iOrphanCount = 0,
               iBaseCount = 0,
               iProviderPathLen,
               ErrorCode,
               LspOrder,
               start,
               end,
               idx,
               rc,
               i, j, k;

    // Retrieve how many orphaned chain entries are present
    iOrphanCount = CountOrphanedChainEntries( pProviders, iProviderCount );

    // Retrieve the LSP count
    iSortLspCount = iLspCount = GetProviderCount( pProviders, iProviderCount, LAYERED_PROTOCOL );

    if ( ( 0 == iOrphanCount ) && ( 0 == iLspCount ) )
    {
        fprintf( stderr, "BuildLspMap: No LSP installed on the system!\n");
        goto cleanup;
    }

    // If orphaned entries are present, create another LSP_ENTRY and put all orphaned
    //      entries there.
    if ( iOrphanCount > 0 )
        iLspCount++;

    // Allocate space for our structure which represents the LSPs installed
    pLsps = (LSP_ENTRY *) LspAlloc(
            sizeof( LSP_ENTRY ) * iLspCount,
           &ErrorCode
            );
    if ( NULL == pLsps )
    {
        fprintf( stderr, "BuildLspMap: LspAlloc failed: %d\n", ErrorCode );
        goto cleanup;
    }

    // If orphaned entries are present, allocate space to hold them
    if ( iOrphanCount > 0 )
    {
        pLsps[ iLspCount-1 ].LayeredEntries = (WSAPROTOCOL_INFOW *)LspAlloc(
                sizeof(WSAPROTOCOL_INFOW) * iOrphanCount, &ErrorCode );
        if ( NULL == pLsps[ iLspCount-1 ].LayeredEntries )
        {
            fprintf( stderr, "BuildLspMap: LspAlloc failed: %d\n", ErrorCode );
            goto cleanup;
        }

        pLsps[ iLspCount-1 ].OrphanedEntries = TRUE;
        pLsps[ iLspCount-1 ].Count = iOrphanCount;

        //
        // Find the orphaned entries and save them off
        //
        idx = 0;
        for(i=0; i < iProviderCount ;i++)
        {
            // Only investigate protocol chain entries (i.e. chainlen > 1)
            if ( pProviders[ i ].ProtocolChain.ChainLen > 1 )
            {
                // Walk the catalog and look for the dummy entry (i.e. the ID in 
                //    chain entry 0)
                for(j=0; j < iProviderCount ;j++) 
                {
                    if ( i == j )
                        continue;

                    if ( pProviders[ i ].ProtocolChain.ChainEntries[ 0 ] ==
                         pProviders[ j ].dwCatalogEntryId )
                    {
                        break;
                    }
                }
                if ( j >= iProviderCount )
                {
                    // If j is past iProviderCount, no match was found so this is
                    //    an orphaned entry...save it off
                    memcpy( &pLsps[ iLspCount-1 ].LayeredEntries[ idx ],
                            &pProviders[ i ],
                             sizeof( WSAPROTOCOL_INFOW )
                          );
                    rc = AddGuidToLspEntry( &pLsps[ iLspCount-1 ], &pProviders[ i ].ProviderId,
                            &ErrorCode );
                    if ( SOCKET_ERROR == rc )
                    {
                        fprintf( stderr, "BuildLspMap: AddGuidToLspEntry failed: %d\n", ErrorCode );
                        goto cleanup;
                    }
                        
                    idx++;
                }
            }
        }
    }

    //
    // Build a list of the valid LSPs installed on the system
    //
    idx = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        if ( LAYERED_PROTOCOL == pProviders[ i ].ProtocolChain.ChainLen )
        {
            // Copy the dummy entry
            memcpy( &pLsps[ idx ].DummyEntry, &pProviders[ i ], sizeof( WSAPROTOCOL_INFOW ) );

            // Get the DLL path
            iProviderPathLen = MAX_PATH-1;
            rc = WSCGetProviderPath(
                    &pLsps[ idx ].DummyEntry.ProviderId,
                     pLsps[ idx ].wszLspDll,
                    &iProviderPathLen,
                    &ErrorCode
                     );
            if ( SOCKET_ERROR == rc )
            {
                fprintf( stderr, "BuildLspMap: WSCGetProviderPath failed: %d\n", ErrorCode );
                goto cleanup;
            }

            //
            // Now go find all the layered entries associated with the dummy provider
            //

            // First get the count
            for(j=0; j < iProviderCount ;j++)
            {
                //
                // Compare only the first entry against the dummy ID. Otherwise, 
                //    we may pick up more than the provider's owned by this LSP 
                //    (it may pick up other providers layered over this LSP.
                //
                if ( ( pProviders[ j ].ProtocolChain.ChainLen > 1 ) &&
                     ( pProviders[ j ].ProtocolChain.ChainEntries[ 0 ] ==
                       pLsps[ idx ].DummyEntry.dwCatalogEntryId ) 
                   )
                // if ( IsIdInChain( &pProviders[ j ], pLsps[ idx ].DummyEntry.dwCatalogEntryId ) )
                {
                    pLsps[idx].Count++;
                }
            }

            // Allocate space
            pLsps[ idx ].LayeredEntries = (WSAPROTOCOL_INFOW *) LspAlloc(
                    sizeof( WSAPROTOCOL_INFOW ) * pLsps[ idx ].Count,
                   &ErrorCode
                    );
            if ( NULL == pLsps[ idx ].LayeredEntries )
            {
                fprintf( stderr, "BuildLspMap: LspAlloc failed: %d\n", ErrorCode );
                goto cleanup;
            }

            pLsps[ idx ].LayerChanged = (int *) LspAlloc(
                    sizeof( int ) * pLsps[ idx ].Count,
                   &ErrorCode
                    );
            if ( NULL == pLsps[ idx ].LayerChanged )
            {
                fprintf( stderr, "BuildLspMap: LspAlloc failed: %d\n", ErrorCode );
                goto cleanup;
            }

            // Now go find the entries
            pLsps[idx].Count = 0;
            for(j=0; j < iProviderCount ;j++)
            {
                if ( ( pProviders[ j ].ProtocolChain.ChainLen > 1 ) &&
                     ( pProviders[ j ].ProtocolChain.ChainEntries[ 0 ] ==
                       pLsps[ idx ].DummyEntry.dwCatalogEntryId ) 
                   )
                {
                    memcpy( 
                           &pLsps[ idx ].LayeredEntries[pLsps[ idx ].Count],
                           &pProviders[ j ],
                            sizeof( WSAPROTOCOL_INFOW )
                            );

                    pLsps[idx].MaxChainLength = MAX( 
                            pLsps[ idx ].MaxChainLength,
                            pLsps[ idx ].LayeredEntries[ pLsps[idx].Count ].ProtocolChain.ChainLen 
                            );

                    // Mark this entry as visited
                    pProviders[ j ].dwProviderReserved = 1;

                    // Keep track of how many GUIDs are used to install the layered entries
                    rc = AddGuidToLspEntry( &pLsps[ idx ], &pProviders[ j ].ProviderId, &ErrorCode );
                    if ( SOCKET_ERROR == rc )
                    {
                        fprintf( stderr, "BuildLspMap: AddGuidToLspEntry failed: %d\n", ErrorCode );
                        goto cleanup;
                    }

                    pLsps[ idx ].Count++;
                }
            }

            pLsps[ idx ].LspOrder = MAX_PROTOCOL_CHAIN;

            idx++;      // Increment index into the map
        }
    }

    //
    // We now have an array of "LSPs" -- now order them
    //

    // First get a list of base provider IDs
    iBaseCount = GetProviderCount( pProviders, iProviderCount, BASE_PROTOCOL );
    if ( 0 == iBaseCount )
    {
        fprintf( stderr, "BuildLspMap: GetProviderCount(BASE_PROTOCOL) returned zero!\n" );
        goto cleanup;
    }

    // Allocate space for the array of base provider ID's
    pBaseList = (DWORD *) LspAlloc(
            sizeof( DWORD ) * iBaseCount,
           &ErrorCode
            );
    if ( NULL == pBaseList )
    {
        fprintf( stderr, "BuildLspMap: HeapAlloc failed: %d\n", ErrorCode );
        goto cleanup;
    }

    //
    // Copy the base provider ID's to our array -- this array contains the catalog
    // IDs of only base providers which will be used next to determine the order
    // in which LSPs were installed.
    //
    idx = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        if ( BASE_PROTOCOL == pProviders[ i ].ProtocolChain.ChainLen )
        {
            pBaseList[ idx++ ] = pProviders[ i ].dwCatalogEntryId;
        }
    }

    //
    // For each layered protocol entry of an LSP find the lowest index in the protocol
    // chain where a base provider resides. A protocol chain should always terminate
    // in a base provider.
    //
    for(LspOrder = 1; LspOrder < MAX_PROTOCOL_CHAIN ;LspOrder++)
    {
        for(i=0; i < iSortLspCount ;i++)
        {
            for(j=0; j < pLsps[ i ].Count ;j++)
            {
                for(k=0; k < iBaseCount ;k++)
                {
                    if ( pLsps[ i ].LayeredEntries[ j ].ProtocolChain.ChainEntries[ LspOrder ] ==
                         pBaseList[ k ] )
                    {
                        pLsps[ i ].LspOrder = MIN( pLsps[ i ].LspOrder, LspOrder );
                        break;
                    }
                }
            }
        }
    }

    //
    // Sort the entries according to the LspOrder field
    //
    for(i=0; i < iSortLspCount ;i++)
    {
        for(j=i; j < iSortLspCount ;j++)
        {
            if ( pLsps[ i ].LspOrder > pLsps[ j ].LspOrder )
            {
                // Exchange positions
                memcpy( &lsptmp,     &pLsps[ i ], sizeof( LSP_ENTRY ) );
                memcpy( &pLsps[ i ], &pLsps[ j ], sizeof( LSP_ENTRY ) );
                memcpy( &pLsps[ j ], &lsptmp,     sizeof( LSP_ENTRY ) );
            }
        }
    }

    //
    // Now need to sort by MaxChainLength withing the LspOrder groupings
    //
    for(LspOrder=1; LspOrder < MAX_PROTOCOL_CHAIN ;LspOrder++)
    {
        // Find the start and end positions within the array for the given
        // LspOrder value
        start = -1;
        end   = -1;

        for(i=0; i < iSortLspCount ;i++)
        {
            if ( pLsps[ i ].LspOrder == LspOrder )
            {
                start = i;
                break;
            }
        }

        //
        // Find the end position which is the LSP Map entry whose LspOrder
        // value doesn't match the current one. This will give us the range
        // of LSP entries whose LspOrder value is identical -- we need to
        // sort the LSPs of the same LspOrder according to the MaxChainLength
        //
        if ( -1 != start )
        {
            for(j=start; j < iSortLspCount ;j++)
            {
                if ( pLsps[ j ].LspOrder != LspOrder )
                {
                    end = j - 1;
                    break;
                }
            }
        }
        
        //
        // If the following is true then all entries have the same order
        // value. We still need to sort by MaxChainLength so set the end
        // to the last LSP 
        //
        if ( ( -1 != start ) && ( -1 == end ) )
        {
            end = iSortLspCount - 1;
        }

        if ( ( -1 != start ) && ( -1 != end ) )
        {
            for(i=start; i < end ;i++)
            {
                for(j=i; j < end ;j++)
                {
                    if ( pLsps[ i ].MaxChainLength > pLsps[ j ].MaxChainLength )
                    {
                        memcpy( &lsptmp,     &pLsps[ i ], sizeof( LSP_ENTRY ) );
                        memcpy( &pLsps[ i ], &pLsps[ j ], sizeof( LSP_ENTRY ) );
                        memcpy( &pLsps[ j ], &lsptmp,     sizeof( LSP_ENTRY ) );
                    }
                }
            }
        }
    }

    // Add the LSP dependency info to the map
    rc = LspDependencyCheck( pLsps, iSortLspCount );
    if ( SOCKET_ERROR == rc )
    {
        FreeLspMap( pLsps, iLspCount );
        pLsps = NULL;
        iLspCount = 0;
        goto cleanup;
    }

cleanup:
    
    if ( NULL != pLspCount )
        *pLspCount = iLspCount;

    if ( NULL != pBaseList )
        LspFree( pBaseList );

    return pLsps;
}