NTSTATUS
NfcCxSCPresentAbsentDispatcherSetRequest(
    _In_ PNFCCX_FDO_CONTEXT FdoContext,
    _In_ PNFCCX_SC_PRESENT_ABSENT_DISPATCHER Dispatcher,
    _In_ WDFREQUEST Request
    )
/*++

Routine Description:

    Stores a request in the dispatcher. If a request is already pending in the dispatcher, the new request will
    be completed with STATUS_DEVICE_BUSY.

Arguments:

    FdoContext - Pointer to the FDO Context
    Dispatcher - Pointer to the Dispatcher.
    Request - The request to store in the dispatcher.

Return Value:

    NTSTATUS

--*/
{
    NTSTATUS status;
    bool powerReferenceAcquired = false;
    bool cancelCallbackSet = false;

    TRACE_FUNCTION_ENTRY(LEVEL_VERBOSE);

    WDFFILEOBJECT fileObject = WdfRequestGetFileObject(Request);
    PNFCCX_FILE_CONTEXT fileContext = NfcCxFileGetContext(fileObject);

    // Pre-check if there is a current request.
    if (ReadPointerAcquire((void**)&Dispatcher->CurrentRequest) != nullptr)
    {
        status = STATUS_DEVICE_BUSY;
        TRACE_LINE(LEVEL_ERROR, "An Is Present/Absent request is already pending. %!STATUS!", status);
        goto Done;
    }

    // Allocate and initialize the request context
    PNFCCX_SC_REQUEST_CONTEXT requestContext = nullptr;

    WDF_OBJECT_ATTRIBUTES contextAttributes;
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&contextAttributes, NFCCX_SC_REQUEST_CONTEXT);

    status = WdfObjectAllocateContext(Request, &contextAttributes, (void**)&requestContext);
    if (!NT_SUCCESS(status))
    {
        TRACE_LINE(LEVEL_ERROR, "Failed to set request's context. %!STATUS!", status);
        goto Done;
    }

    requestContext->Dispatcher = Dispatcher;

    // Add a power reference (if required).
    if (Dispatcher->PowerManaged)
    {
        status = NfcCxPowerFileAddReference(FdoContext->Power, fileContext, NfcCxPowerReferenceType_Proximity);
        if (!NT_SUCCESS(status))
        {
            TRACE_LINE(LEVEL_VERBOSE, "Failed to acquire power reference. %!STATUS!", status);
            goto Done;
        }

        powerReferenceAcquired = true;
    }

    // Setup cancel callback.
    status = WdfRequestMarkCancelableEx(Request, NfcCxSCPresentAbsentDispatcherRequestCanceled);
    if (!NT_SUCCESS(status))
    {
        TRACE_LINE(LEVEL_ERROR, "Failed to set request canceled callback. %!STATUS!", status);
        goto Done;
    }

    // Add a ref-count to the request, which is owned by the cancel callback.
    WdfObjectReference(Request);
    cancelCallbackSet = true;

    // Try to set the current request.
    void* previousRequest = InterlockedCompareExchangePointer((void**)&Dispatcher->CurrentRequest, /*exchange*/ Request, /*compare*/ nullptr);

    // Check if we already have a pending request.
    if (previousRequest != nullptr)
    {
        status = STATUS_DEVICE_BUSY;
        TRACE_LINE(LEVEL_ERROR, "An Is Present/Absent request is already pending. %!STATUS!", status);
        goto Done;
    }

Done:
    if (!NT_SUCCESS(status))
    {
        if (cancelCallbackSet)
        {
            NTSTATUS unmarkStatus = WdfRequestUnmarkCancelable(Request);
            if (unmarkStatus != STATUS_CANCELLED)
            {
                // Cancel callback will not be called.
                // So release cancel callback's request ref-count.
                WdfObjectDereference(Request);
            }
        }

        if (powerReferenceAcquired)
        {
            NfcCxPowerFileRemoveReference(FdoContext->Power, fileContext, NfcCxPowerReferenceType_Proximity);
        }
    }

    TRACE_FUNCTION_EXIT_NTSTATUS(LEVEL_VERBOSE, status);
    return status;
}