NTSTATUS
LpxTdiReceive(
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine performs the TdiReceive request for the transport provider.

Arguments:

    Irp - I/O Request Packet for this request.

Return Value:

    NTSTATUS - status of operation.

--*/

{
	PTP_CONNECTION connection;
	PIO_STACK_LOCATION irpSp;

    //
    // verify that the operation is taking place on a connection. At the same
    // time we do this, we reference the connection. This ensures it does not
    // get removed out from under us. Note also that we do the connection
    // lookup within a try/except clause, thus protecting ourselves against
    // really bogus handles
    //

    irpSp = IoGetCurrentIrpStackLocation (Irp);
    connection = irpSp->FileObject->FsContext;

    IF_LPXDBG (LPX_DEBUG_RCVENG) {
        LpxPrint2 ("LpxTdiReceive: Received IRP %p on connection %p\n", 
                        Irp, connection);
    }

    //
    // Check that this is really a connection.
    //

    if ((irpSp->FileObject->FsContext2 == UlongToPtr(LPX_FILE_TYPE_CONTROL)) ||
        (connection->Size != sizeof (TP_CONNECTION)) ||
        (connection->Type != LPX_CONNECTION_SIGNATURE)) {
#if DBG
        LpxPrint2 ("TdiReceive: Invalid Connection %p Irp %p\n", connection, Irp);
#endif
        return STATUS_INVALID_CONNECTION;
    }

#if __LPX__

	return LpxRecv( connection, Irp );

#endif

} /* TdiReceive */