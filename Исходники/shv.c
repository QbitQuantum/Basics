INT32
ShvLoad (
    VOID
    )
{
    SHV_CALLBACK_CONTEXT callbackContext;

    //
    // Attempt to enter VMX root mode on all logical processors. This will
    // broadcast a DPC interrupt which will execute the callback routine in
    // parallel on the LPs. Send the callback routine the physical address of
    // the PML4 of the system process, which is what this driver entrypoint
    // should be executing in.
    //
    callbackContext.Cr3 = __readcr3();
    callbackContext.FailureStatus = SHV_STATUS_SUCCESS;
    callbackContext.FailedCpu = -1;
    callbackContext.InitCount = 0;
    ShvOsRunCallbackOnProcessors(ShvVpLoadCallback, &callbackContext);

    //
    // Check if all LPs are now hypervised. Return the failure code of at least
    // one of them. 
    //
    // Note that each VP is responsible for freeing its VP data on failure.
    //
    if (callbackContext.InitCount != ShvOsGetActiveProcessorCount())
    {
        ShvOsDebugPrint("The SHV failed to initialize (0x%lX) Failed CPU: %d\n",
                        callbackContext.FailureStatus, callbackContext.FailedCpu);
        return callbackContext.FailureStatus;
    }

    //
    // Indicate success.
    //
    ShvOsDebugPrint("The SHV has been installed.\n");
    return SHV_STATUS_SUCCESS;
}