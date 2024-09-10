NTSTATUS
kmdf1394_SetAddressData (
                         IN WDFDEVICE Device,
                         IN WDFREQUEST Request,
                         IN PSET_ADDRESS_DATA SetAddrData)
/*++

Routine Description:

    Set Address Range routine.

Arguments:

    Device - the current WDFDEVICE Object.

    Request - the current request.

    SetAddrData - the Data buffer from usermode to be worked on.

Return Value:

    VOID
--*/
{
    NTSTATUS ntStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION  deviceExtension = GetDeviceContext(Device);
    PASYNC_ADDRESS_DATA AsyncAddressData = NULL;
    PLIST_ENTRY listHead, thisEntry;

    UNREFERENCED_PARAMETER(Request);

    ENTER("kmdf1394_SetAddressData");

    //
    // have to find our struct...
    //
    WdfSpinLockAcquire(deviceExtension->AsyncSpinLock);

    listHead = &deviceExtension->AsyncAddressData;

    for(thisEntry = listHead->Flink; thisEntry != listHead;
        AsyncAddressData = NULL, thisEntry = thisEntry->Flink)
    {
        AsyncAddressData = CONTAINING_RECORD(
            thisEntry, 
            ASYNC_ADDRESS_DATA,
            AsyncAddressList);
        if (AsyncAddressData->hAddressRange == SetAddrData->hAddressRange) 
        {
            PULONG  pBuffer;

            // 
            // found it, let's copy over the contents from data...
            //
            pBuffer = \
                (PULONG)((ULONG_PTR)AsyncAddressData->Buffer + \
                SetAddrData->ulOffset);

            TRACE(TL_TRACE, ("pBuffer = 0x%x\n", pBuffer));
            TRACE(TL_TRACE, ("Data = 0x%x\n", SetAddrData->Data));

            if(pBuffer && SetAddrData->Data) 
            {
                RtlCopyMemory(pBuffer, SetAddrData->Data, SetAddrData->nLength);
            }
            break;
        }
    }

    WdfSpinLockRelease(deviceExtension->AsyncSpinLock);

    // 
    // never found an entry...
    //
    if (!AsyncAddressData) 
    {
        ntStatus = STATUS_INVALID_PARAMETER;
    }

    EXIT("kmdf1394_SetAddressData", ntStatus);
    return ntStatus;
} // kmdf1394_SetAddressData