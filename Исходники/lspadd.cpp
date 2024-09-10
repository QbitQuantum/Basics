//
// Function: InstallIfsLspProtocolChains
//
// Description:
//      This routine installs the layered protocol chains for an IFS based LSP. It
//      assumes the LSP dummy entry is already installed. This function first enumerates
//      the catalog to find the ID of the dummy entry. It then builds the protocol
//      entries for the IFS layered protocols. Note that an IFS entry must be installed
//      such that no non-IFS providers are layered beneath it. This means if the user
//      chooses to install the IFS LSP over a provider which includes non-IFS layers, it
//      must insert itself into the chain such that it is below all non-IFS providers.
//      This means that existing entries need to be modified in order to reflect this
//      ordering. Also in the event that the IFS LSP is inserted into an existing chain
//      this installer still builds a series of standalone entries (i.e. entries that
//      would have existed of the LSPs layered over the IFS LSP were installed after
//      the IFS LSP was).
//
int
InstallIfsLspProtocolChains(
    WINSOCK_CATALOG eCatalog,
    GUID           *Guid,
    WCHAR          *lpszLspName,
    WCHAR          *lpszLspFullPathAndFile,
    DWORD          *pdwCatalogIdArray,
    DWORD           dwCatalogIdArrayCount
    )
{
    WSAPROTOCOL_INFOW  *pProvider = NULL,
                       *pProviderNew = NULL,
                       *pLayeredEntries = NULL,
                       *pEntry = NULL,
                        TempEntry = {0};
    DWORD              *pProviderOrder = NULL,
                        dwDummyLspId;
    WCHAR               wszLspDll[ MAX_PATH ];
    BOOL                bLayeredOverNonIfs = FALSE,
                        bContainsNonIfs = FALSE;
    HRESULT             hr;
    int                 ProviderPathLen = MAX_PATH-1,
                        iProviderCount,
                        iProviderCountNew,
                        LayerIdx,
                        retval = SOCKET_ERROR,
                        err,
                        idx,
                        rc,
                        i, j, k;

    // Enumerate the catalog
    pProvider = EnumerateProviders( eCatalog, &iProviderCount );
    if ( NULL == pProvider )
    {
        fprintf( stderr, "InstallIfsLspProtocolChains: Unable to enumerate catalog\n" );
        goto cleanup;
    }

    // Find the dummy, hidden entry of our new LSP
    dwDummyLspId = GetCatalogIdForProviderGuid( Guid, pProvider, iProviderCount );

    ASSERT( dwDummyLspId != 0 );

    // Allocate space for the protocol chains of the new LSP
    pLayeredEntries = (WSAPROTOCOL_INFOW *) LspAlloc( sizeof(WSAPROTOCOL_INFOW) *
            dwCatalogIdArrayCount, &err );
    if ( NULL == pLayeredEntries )
    {
        fprintf( stderr, "InstallIfsLspProtocolChains: LspAlloc failed: %d\n", err );
        goto cleanup;
    }

    LayerIdx = 0;

    // Build the layered protocol entries as well as a list of those providers which
    // require modification. Whenever an LSP is installed, a number of protocol entries
    // are installed where the first entry in the chain array is the LSP's dummy entry.
    // Addtionally, if we're installing an IFS LSP over an provider whose protocol chain
    // includes non-IFS LSPs, the IFS LSP must be placed in the chain such that no
    // non-IFS LSPs are positioned after it in the chain.

    // Loop through each ID we're layering over
    for(i=0; i < (int)dwCatalogIdArrayCount ;i++)
    {
        for(j=0; j < iProviderCount ;j++)
        {
            printf("Matching selected ID %d to catalog %d\n",
                    pdwCatalogIdArray[ i ], pProvider[ j ].dwCatalogEntryId );

            if ( pdwCatalogIdArray[ i ] == pProvider[ j ].dwCatalogEntryId )
            {
                // Verify the entry has room enough to be layered over
                if ( pProvider[ j ].ProtocolChain.ChainLen >= ( MAX_PROTOCOL_CHAIN - 1 ) )
                {
                    fprintf( stderr, "InstallIfsLspProtocolChain: Too many LSPs installed!\n");
                    goto cleanup;
                }

                // Save off the entry which we're layering over
                memcpy( &pLayeredEntries[ LayerIdx ], &pProvider[ j ],
                        sizeof( pLayeredEntries[ 0  ] ) );

                memcpy( &TempEntry, &pProvider[ j ], sizeof( TempEntry ) );        

                // Fill in the new LSP entry's name
                hr = StringCchPrintfW( pLayeredEntries[ LayerIdx ].szProtocol, WSAPROTOCOL_LEN,
                        L"%s over [%s]",
                        lpszLspName,
                        pProvider[ j ].szProtocol 
                        );
                if ( FAILED( hr ) )
                {
                    fprintf( stderr, "InstallIfsLspProtocolChains: StringCchPrintfW failed: 0x%x\n", hr );
                    goto cleanup;
                }

                // Check whether the selected entry contains non IFS LSPs in its chain
                if ( pProvider[ j ].ProtocolChain.ChainLen >= 2 )
                {
                    for(k=pProvider[ j ].ProtocolChain.ChainLen-2 ; k >= 0 ;k--)
                    {
                        bContainsNonIfs = IsNonIfsProvider( pProvider, iProviderCount, 
                                pProvider[ j ].ProtocolChain.ChainEntries[ k ] );

                        if ( TRUE == bContainsNonIfs )
                        {
                            // Need to modify the pProvider entry to reference the
                            // added LSP entry within its chain

                            // In the 'modified' array make a space at location after 'k'
                            InsertIdIntoProtocolChain( &pProvider[ j ], k+1, UPDATE_LSP_ENTRY );

                            // Save the index to the layer which corresponds to this entry
                            pProvider[ j ].dwProviderReserved = LayerIdx + 1;

                            // Need to fix the 'pLayeredEntry' as well
                            BuildSubsetLspChain( &pLayeredEntries[ LayerIdx ], k+1, dwDummyLspId );

                            pLayeredEntries[ LayerIdx ].dwServiceFlags1 |= XP1_IFS_HANDLES;

                            bLayeredOverNonIfs = TRUE;

                            // Need to insert the IFS provider in all LSPs that  are layered
                            // above the location where the IFS provider was just inserted
                            InsertIfsLspIntoAllChains( &TempEntry, pProvider, iProviderCount, 
                                    LayerIdx + 1, k );

                            break;
                        }
                    }
                }

                // Need to setup the protocol chain in the pLayeredEntry if we haven't
                // already done so above
                if ( TRUE != bContainsNonIfs )
                {
                    InsertIdIntoProtocolChain( &pLayeredEntries[ LayerIdx ], 0, dwDummyLspId );

                    // The second entry is always the ID of the current pProvider[i]
                    //     In case of multiple LSPs then if we didn't do this the [1] index
                    //     would contain the ID of that LSP's dummy entry and not the entry
                    //     itself.
                    pLayeredEntries[ LayerIdx ].ProtocolChain.ChainEntries[ 1 ] = 
                            TempEntry.dwCatalogEntryId;

                    pLayeredEntries[ LayerIdx ].dwServiceFlags1 |= XP1_IFS_HANDLES;
                }

                LayerIdx++;
            }
        }
    }

    ASSERT( LayerIdx == (int)dwCatalogIdArrayCount );

    // Create a unique GUID for each provider to install and install it
    for(i=0;i < (int)dwCatalogIdArrayCount ;i++)
    {
        if ( RPC_S_OK != UuidCreate( &pLayeredEntries[ i ].ProviderId ) )
        {
            fprintf(stderr, "InstallIfsLspProtocolChains: UuidCreate failed: %d\n", GetLastError());
            goto cleanup;
        }

        rc = InstallProvider( eCatalog, &pLayeredEntries[ i ].ProviderId,
                lpszLspFullPathAndFile, &pLayeredEntries[ i ], 1 );
        if ( NO_ERROR != rc )
        {
            fprintf(stderr, "InstallIfsLspProtocolChains: Unable to install the dummy LSP entry!\n");
            goto cleanup;
        }
    }

    if ( TRUE == bLayeredOverNonIfs )
    {
        // Enumerate the catalog again so we can find the catalog IDs

        pProviderNew = EnumerateProviders( eCatalog, &iProviderCountNew );
        if ( NULL == pProvider )
        {
            fprintf( stderr, "InstallIfsLspProtocolChains: Unable to enumerate catalog\n" );
            goto cleanup;
        }

        for(i=0; i < (int)dwCatalogIdArrayCount ;i++)
        {
            pLayeredEntries[ i ].dwCatalogEntryId = GetCatalogIdForProviderGuid(
                   &pLayeredEntries[ i ].ProviderId,
                    pProviderNew,
                    iProviderCountNew
                    );

            ASSERT( pLayeredEntries[ i ].dwCatalogEntryId != 0 );
        }

        // Update the protocol chains of the modified entries to point to the just
        //    installed providers
        for(i=0; i < iProviderCount ;i++)
        {
            if ( pProvider[ i ].dwProviderReserved == 0 )
                continue;

            for(j=0; j < pProvider[ i ].ProtocolChain.ChainLen ;j++)
            {
                if ( UPDATE_LSP_ENTRY == pProvider[ i ].ProtocolChain.ChainEntries[ j ] )
                {
                    pProvider[ i ].ProtocolChain.ChainEntries[ j ] = 
                        pLayeredEntries[ pProvider[ i ].dwProviderReserved - 1 ].dwCatalogEntryId;

                    pProvider[ i ].dwProviderReserved = 0;
                }
            }

            // Get the DLL path
            ProviderPathLen = MAX_PATH-1;
            rc = WSCGetProviderPath(
                    &pProvider[ i ].ProviderId,
                     wszLspDll,
                    &ProviderPathLen,
                    &err
                     );
            if ( SOCKET_ERROR == rc )
            {
                fprintf( stderr, "InstallIfsLspProtocolChains: WSCGetProviderPath failed: %d\n", err );
                goto cleanup;
            }

            // Update the providers which were modified
            rc = UpdateProvider( eCatalog, &pProvider[ i ].ProviderId,
                    wszLspDll, &pProvider[ i ], 1, &err );
            if ( SOCKET_ERROR == rc )
            {
                fprintf( stderr, "InstallIfsLspProtocolChains: UpdateProvider failed: %d\n", err );
                goto cleanup;
            }

            printf("Updated entry ID: %d: %S (chain len = %d)\n",
                    pProvider[ i ].dwCatalogEntryId,
                    pProvider[ i ].szProtocol,
                    pProvider[ i ].ProtocolChain.ChainLen
                    );
        }

        FreeProviders( pProvider );
        pProvider = NULL;

        FreeProviders( pProviderNew );
        pProviderNew = NULL;

        /*
        {
            WSADATA wsd;

            WSACleanup();

            WSAStartup( MAKEWORD(2,2), &wsd );
        }
        */

        pProvider = EnumerateProviders( eCatalog, &iProviderCount );
        if ( NULL == pProvider )
        {
            fprintf( stderr, "InstallIfsLspProtocolChains: Unable to enumerate catalog\n" );
            goto cleanup;
        }

        // Allocate an array of DWORDs to contain the new catalog ordering
        pProviderOrder = (DWORD *)LspAlloc( iProviderCount * sizeof(DWORD), &err );
        if ( NULL == pProviderOrder )
        {
            fprintf( stderr, "InstallIfsLspProtocolChains: Unable to enumerate catalog\n" );
            goto cleanup;
        }

        // First add the entries we layered over first
        idx = 0;
        for(i=0; i < (int)dwCatalogIdArrayCount ;i++)
        {
            pEntry = FindProviderById( pdwCatalogIdArray[ i ], pProvider, iProviderCount );
            if ( NULL == pEntry )
            {
                fprintf(stderr, "InstallIfsLspProtocolChain: Unable to find entry to reorder catalog!\n");
                goto cleanup;
            }

            pEntry->dwProviderReserved = 1;

            pProviderOrder[ idx++ ] = pEntry->dwCatalogEntryId;
        }

        // Now go through the protocol chain of the entries we layered over and put those
        //    LSP entries next in the new order
        for(i=0; i < (int)dwCatalogIdArrayCount ;i++)
        {
            pEntry = FindProviderById( pdwCatalogIdArray[ i ], pProvider, iProviderCount );
            if ( NULL == pEntry )
            {
                fprintf(stderr, "InstallIfsLspProtocolChain: Unable to find entry to reorder catalog!\n");
                goto cleanup;
            }

            printf("Looping through: %d: %S (chain len = %d)\n", 
                    pEntry->dwCatalogEntryId,
                    pEntry->szProtocol,
                    pEntry->ProtocolChain.ChainLen );

            for(j=1; j < pEntry->ProtocolChain.ChainLen-1 ;j++)
            {
                dwDummyLspId = FindDummyIdFromProtocolChainId(
                        pEntry->ProtocolChain.ChainEntries[ j ],
                        pProvider,
                        iProviderCount
                        );

                printf("   Finding dummy ID for chain entry: %d is %d\n", 
                        pEntry->ProtocolChain.ChainEntries[ j ],
                        dwDummyLspId
                        );

                for(k=0; k < iProviderCount ;k++)
                {
                    if ( ( pProvider[ k ].ProtocolChain.ChainLen >= 2 ) &&
                         ( pProvider[ k ].ProtocolChain.ChainEntries[ 0 ] == dwDummyLspId ) &&
                         ( pProvider[ k ].dwProviderReserved == 0 )
                       )
                    {
                        pProviderOrder[ idx++ ] = pProvider[ k ].dwCatalogEntryId;
                        pProvider[ k ].dwProviderReserved = 1;

                        printf("      Adding: %d\n", pProvider[ k ].dwCatalogEntryId );
                    }
                }
            }
        }

        // Now any catalog entry that wasn't already copied, copy it
        for(i=0; i < iProviderCount ;i++)
        {
            if ( pProvider[ i ].dwProviderReserved == 0 )
                pProviderOrder[ idx++ ] = pProvider[ i ].dwCatalogEntryId;
        }

        ASSERT( idx == iProviderCount );

        // Write the new catalog order
        rc = WriteProviderOrder( eCatalog, pProviderOrder, iProviderCount, &err );
        if ( NO_ERROR != rc )
        {
            fprintf( stderr, "InstallIfsLspProtocolChains: WriteProviderOrder failed: %d\n",
                    err );
            goto cleanup;
        }
    }
    else
    {
        //
        // Reorder the winsock catalog so the layered chain entries appear first.
        // Since we didn't have to modify any existing entries, all we need to do is
        //    move the added entries to the head of the catalog
        // 
        rc = ReorderCatalog( eCatalog, dwDummyLspId );
        if ( NO_ERROR != rc )
        {
            fprintf(stderr, "InstallIfsLspProtocolChains: Unable to reorder Winsock catalog!\n");
            goto cleanup;
        }
    }

    retval = NO_ERROR;

cleanup:
    
    if ( NULL != pProvider )
    {
        FreeProviders( pProvider );
        pProvider = NULL;
    }

    if ( NULL != pProviderNew )
    {
        FreeProviders( pProviderNew );
        pProviderNew = NULL;
    }

    if ( NULL != pProviderOrder )
    {
        LspFree( pProviderOrder );
        pProviderOrder = NULL;
    }

    return retval;
}