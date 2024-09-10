NOT PAGEABLE -- WalkConnectionTable
#endif


VOID
SrvAllocateEndpoint (
    OUT PENDPOINT *Endpoint,
    IN PUNICODE_STRING NetworkName,
    IN PUNICODE_STRING TransportName,
    IN PANSI_STRING TransportAddress,
    IN PUNICODE_STRING DomainName
    )

/*++

Routine Description:

    This function allocates an Endpoint Block from the system nonpaged
    pool.

Arguments:

    Endpoint - Returns a pointer to the endpoint block, or NULL if no
        pool was available.

    NetworkName - Supplies a pointer to the network name (e.g., NET1).

    TransportName - The fully qualified name of the transport device.
        For example, "\Device\Nbf".

    TransportAddress - The fully qualified address (or name ) of the
        server's endpoint.  This name is used exactly as specified.  For
        NETBIOS-compatible networks, the caller must upcase and
        blank-fill the name.  E.g., "\Device\Nbf\NTSERVERbbbbbbbb".

    DomainName - the domain being serviced by this endpoint

Return Value:

    None.

--*/

{
    CLONG length;
    PENDPOINT endpoint;
    NTSTATUS status;

    PAGED_CODE( );

    //
    // Attempt to allocate from nonpaged pool.
    //

    length = sizeof(ENDPOINT) +
                NetworkName->Length + sizeof(*NetworkName->Buffer) +
                TransportName->Length + sizeof(*TransportName->Buffer) +
                TransportAddress->Length + sizeof(*TransportAddress->Buffer) +
                DomainName->Length + sizeof(*DomainName->Buffer) +
                RtlUnicodeStringToOemSize( DomainName ) + sizeof(CHAR);

    endpoint = ALLOCATE_NONPAGED_POOL( length, BlockTypeEndpoint );
    *Endpoint = endpoint;

    if ( endpoint == NULL ) {

        INTERNAL_ERROR (
            ERROR_LEVEL_EXPECTED,
            "SrvAllocateEndpoint: Unable to allocate %d bytes from nonpaged "
                "pool.",
            length,
            NULL
            );

        return;
    }

    IF_DEBUG(HEAP) {
        SrvPrint1( "SrvAllocateEndpoint: Allocated endpoint at %lx\n",
                    endpoint );
    }

    //
    // Initialize the endpoint block.  Zero it first.
    //

    RtlZeroMemory( endpoint, length );

    SET_BLOCK_TYPE_STATE_SIZE( endpoint, BlockTypeEndpoint, BlockStateActive, length );
    endpoint->BlockHeader.ReferenceCount = 2;       // allow for Active status
                                                    //  and caller's pointer

    //
    // Allocate connection table.
    //

    SrvAllocateTable(
        &endpoint->ConnectionTable,
        6, // !!!
        TRUE
        );
    if ( endpoint->ConnectionTable.Table == NULL ) {
        DEALLOCATE_NONPAGED_POOL( endpoint );
        *Endpoint = NULL;
        return;
    }

    InitializeListHead( &endpoint->FreeConnectionList );
#if SRVDBG29
    UpdateConnectionHistory( "INIT", endpoint, NULL );
#endif

    //
    // Copy the network name, transport name, and server address, and domain
    // name into the block.
    //

    endpoint->NetworkName.Length = NetworkName->Length;
    endpoint->NetworkName.MaximumLength =
            (SHORT)(NetworkName->Length + sizeof(*NetworkName->Buffer));
    endpoint->NetworkName.Buffer = (PWCH)(endpoint + 1);
    RtlCopyMemory(
        endpoint->NetworkName.Buffer,
        NetworkName->Buffer,
        NetworkName->Length
        );

    endpoint->TransportName.Length = TransportName->Length;
    endpoint->TransportName.MaximumLength =
            (SHORT)(TransportName->Length + sizeof(*TransportName->Buffer));
    endpoint->TransportName.Buffer =
                            (PWCH)((PCHAR)endpoint->NetworkName.Buffer +
                                    endpoint->NetworkName.MaximumLength);
    RtlCopyMemory(
        endpoint->TransportName.Buffer,
        TransportName->Buffer,
        TransportName->Length
        );

    endpoint->TransportAddress.Length = TransportAddress->Length;
    endpoint->TransportAddress.MaximumLength =
                                (SHORT)(TransportAddress->Length + 1);
    endpoint->TransportAddress.Buffer =
                            (PCHAR)endpoint->TransportName.Buffer +
                                    endpoint->TransportName.MaximumLength;
    RtlCopyMemory(
        endpoint->TransportAddress.Buffer,
        TransportAddress->Buffer,
        TransportAddress->Length
        );


    endpoint->DomainName.Length = DomainName->Length;
    endpoint->DomainName.MaximumLength = 
            (SHORT)(DomainName->Length + sizeof(*DomainName->Buffer));
    endpoint->DomainName.Buffer = (PWCH)((PCHAR)endpoint->TransportAddress.Buffer +
                                         TransportAddress->MaximumLength);
    RtlCopyMemory(
        endpoint->DomainName.Buffer,
        DomainName->Buffer,
        DomainName->Length
    );


    endpoint->OemDomainName.Length = (SHORT)RtlUnicodeStringToOemSize( DomainName );
    endpoint->OemDomainName.MaximumLength =
            endpoint->OemDomainName.Length + sizeof( CHAR );
    endpoint->OemDomainName.Buffer = (PCHAR)endpoint->DomainName.Buffer +
                                     DomainName->MaximumLength;
    status = RtlUnicodeStringToOemString(
                &endpoint->OemDomainName,
                &endpoint->DomainName,
                FALSE     // Do not allocate the OEM string
                );
    ASSERT( NT_SUCCESS(status) );
            

    //
    // Initialize the network address field.
    //

    endpoint->NetworkAddress.Buffer = endpoint->NetworkAddressData;
    endpoint->NetworkAddress.Length = sizeof( endpoint->NetworkAddressData ) -
                                      sizeof(endpoint->NetworkAddressData[0]);
    endpoint->NetworkAddress.MaximumLength = sizeof( endpoint->NetworkAddressData );

    //
    // Increment the count of endpoints in the server.
    //

    ACQUIRE_LOCK( &SrvEndpointLock );
    SrvEndpointCount++;
    RELEASE_LOCK( &SrvEndpointLock );

    INITIALIZE_REFERENCE_HISTORY( endpoint );

    INCREMENT_DEBUG_STAT( SrvDbgStatistics.EndpointInfo.Allocations );

    return;

} // SrvAllocateEndpoint