NTSTATUS
CsrIdentifyAlertableThread( VOID )
{
    NTSTATUS Status;
    CSR_API_MSG m;
    PCSR_IDENTIFY_ALERTABLE_MSG a = &m.u.IndentifyAlertable;

    a->ClientId = NtCurrentTeb()->ClientId;

    Status = CsrClientCallServer(
                &m,
                NULL,
                CSR_MAKE_API_NUMBER( CSRSRV_SERVERDLL_INDEX,
                                     CsrpIdentifyAlertable
                                   ),
                sizeof( *a )
                );

    return Status;
}