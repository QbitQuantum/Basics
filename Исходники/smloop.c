NTSTATUS
NTAPI
SmpHandleConnectionRequest(IN HANDLE SmApiPort,
                           IN PSB_API_MSG SbApiMsg)
{
    BOOLEAN Accept = TRUE;
    HANDLE PortHandle, ProcessHandle;
    ULONG SessionId;
    UNICODE_STRING SubsystemPort;
    SMP_CLIENT_CONTEXT *ClientContext;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    REMOTE_PORT_VIEW PortView;
    SECURITY_QUALITY_OF_SERVICE SecurityQos;
    PSMP_SUBSYSTEM CidSubsystem, TypeSubsystem;

    /* Initialize QoS data */
    SecurityQos.ImpersonationLevel = SecurityIdentification;
    SecurityQos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
    SecurityQos.EffectiveOnly = TRUE;

    /* Check if this is SM connecting to itself */
    if (SbApiMsg->h.ClientId.UniqueProcess == SmUniqueProcessId)
    {
        /* No need to get any handle -- assume session 0 */
        ProcessHandle = NULL;
        SessionId = 0;
    }
    else
    {
        /* Reference the foreign process */
        InitializeObjectAttributes(&ObjectAttributes, NULL, 0, NULL, NULL);
        Status = NtOpenProcess(&ProcessHandle,
                               PROCESS_QUERY_INFORMATION,
                               &ObjectAttributes,
                               &SbApiMsg->h.ClientId);
        if (!NT_SUCCESS(Status)) Accept = FALSE;

        /* Get its session ID */
        SmpGetProcessMuSessionId(ProcessHandle, &SessionId);
    }

    /* See if we already know about the caller's subsystem */
    CidSubsystem = SmpLocateKnownSubSysByCid(&SbApiMsg->h.ClientId);
    if ((CidSubsystem) && (Accept))
    {
        /* Check if we already have a subsystem for this kind of image */
        TypeSubsystem = SmpLocateKnownSubSysByType(SessionId,
                                                   SbApiMsg->ConnectionInfo.SubsystemType);
        if (TypeSubsystem == CidSubsystem)
        {
            /* Someone is trying to take control of an existing subsystem, fail */
            Accept = FALSE;
            DPRINT1("SMSS: Connection from SubSystem rejected\n");
            DPRINT1("SMSS: Image type already being served\n");
        }
        else
        {
            /* Set this image type as the type for this subsystem */
            CidSubsystem->ImageType = SbApiMsg->ConnectionInfo.SubsystemType;
        }

        /* Drop the reference we had acquired */
        if (TypeSubsystem) SmpDereferenceSubsystem(TypeSubsystem);
    }

    /* Check if we'll be accepting the connection */
    if (Accept)
    {
        /* We will, so create a client context for it */
        ClientContext = RtlAllocateHeap(SmpHeap, 0, sizeof(SMP_CLIENT_CONTEXT));
        if (ClientContext)
        {
            ClientContext->ProcessHandle = ProcessHandle;
            ClientContext->Subsystem = CidSubsystem;
            ClientContext->dword10 = 0;
            ClientContext->PortHandle = NULL;
        }
        else
        {
            /* Failed to allocate a client context, so reject the connection */
            DPRINT1("Rejecting connectiond due to lack of memory\n");
            Accept = FALSE;
        }
    }
    else
    {
        /* Use a bogus context since we're going to reject the message */
        ClientContext = (PSMP_CLIENT_CONTEXT)SbApiMsg;
    }

    /* Now send the actual accept reply (which could be a rejection) */
    PortView.Length = sizeof(PortView);
    Status = NtAcceptConnectPort(&PortHandle,
                                 ClientContext,
                                 &SbApiMsg->h,
                                 Accept,
                                 NULL,
                                 &PortView);
    if (!(Accept) || !(NT_SUCCESS(Status)))
    {
        /* Close the process handle, reference the subsystem, and exit */
        DPRINT1("Accept failed or rejected: %lx\n", Status);
        if (ClientContext != (PVOID)SbApiMsg) RtlFreeHeap(SmpHeap, 0, ClientContext);
        if (ProcessHandle) NtClose(ProcessHandle);
        if (CidSubsystem) SmpDereferenceSubsystem(CidSubsystem);
        return Status;
    }

    /* Save the port handle now that we've accepted it */
    if (ClientContext) ClientContext->PortHandle = PortHandle;
    if (CidSubsystem) CidSubsystem->PortHandle = PortHandle;

    /* Complete the port connection */
    Status = NtCompleteConnectPort(PortHandle);
    if ((NT_SUCCESS(Status)) && (CidSubsystem))
    {
        /* This was an actual subsystem, so connect back to it */
        SbApiMsg->ConnectionInfo.SbApiPortName[119] = UNICODE_NULL;
        RtlCreateUnicodeString(&SubsystemPort,
                               SbApiMsg->ConnectionInfo.SbApiPortName);
        Status = NtConnectPort(&CidSubsystem->SbApiPort,
                               &SubsystemPort,
                               &SecurityQos,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               NULL);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("SMSS: Connect back to Sb %wZ failed %lx\n", &SubsystemPort, Status);
        }
        RtlFreeUnicodeString(&SubsystemPort);

        /* Now that we're connected, signal the event handle */
        NtSetEvent(CidSubsystem->Event, NULL);
    }
    else if (CidSubsystem)
    {
        /* We failed to complete the connection, so clear the port handle */
        DPRINT1("Completing the connection failed: %lx\n", Status);
        CidSubsystem->PortHandle = NULL;
    }

    /* Dereference the subsystem and return the result */
    if (CidSubsystem) SmpDereferenceSubsystem(CidSubsystem);
    return Status;
}