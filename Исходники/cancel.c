NTSTATUS
DriverEntry(
    __in PDRIVER_OBJECT  DriverObject,
    __in PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    Installable driver initialization entry point.
    This entry point is called directly by the I/O system.

Arguments:

    DriverObject - pointer to the driver object

    registryPath - pointer to a unicode string representing the path,
                   to driver-specific key in the registry.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise

--*/
{
    NTSTATUS            status = STATUS_SUCCESS;
    UNICODE_STRING      unicodeDeviceName;
    UNICODE_STRING      unicodeDosDeviceName;
    PDEVICE_OBJECT      deviceObject;
    PDEVICE_EXTENSION   devExtension;
    HANDLE              threadHandle;
    UNICODE_STRING      sddlString;

    UNREFERENCED_PARAMETER (RegistryPath);

    CSAMP_KDPRINT(("DriverEntry Enter \n"));


    (void) RtlInitUnicodeString(&unicodeDeviceName, CSAMP_DEVICE_NAME_U);

    (void) RtlInitUnicodeString( &sddlString, L"D:P(A;;GA;;;SY)(A;;GA;;;BA)");

    //
    // We will create a secure deviceobject so that only processes running
    // in admin and local system account can access the device. Refer
    // "Security Descriptor String Format" section in the platform
    // SDK documentation to understand the format of the sddl string.
    // We need to do because this is a legacy driver and there is no INF
    // involved in installing the driver. For PNP drivers, security descriptor
    // is typically specified for the FDO in the INF file.
    //

    status = IoCreateDeviceSecure(
                DriverObject,
                sizeof(DEVICE_EXTENSION),
                &unicodeDeviceName,
                FILE_DEVICE_UNKNOWN,
                FILE_DEVICE_SECURE_OPEN,
                (BOOLEAN) FALSE,
                &sddlString,
                (LPCGUID)&GUID_DEVCLASS_CANCEL_SAMPLE,
                &deviceObject
                );
    if (!NT_SUCCESS(status))
    {
        return status;
    }

    DbgPrint("DeviceObject %p\n", deviceObject);

    //
    // Allocate and initialize a Unicode String containing the Win32 name
    // for our device.
    //

    (void)RtlInitUnicodeString( &unicodeDosDeviceName, CSAMP_DOS_DEVICE_NAME_U );


    status = IoCreateSymbolicLink(
                (PUNICODE_STRING) &unicodeDosDeviceName,
                (PUNICODE_STRING) &unicodeDeviceName
                );

    if (!NT_SUCCESS(status))
    {
        IoDeleteDevice(deviceObject);
        return status;
    }

    devExtension = deviceObject->DeviceExtension;

    DriverObject->MajorFunction[IRP_MJ_CREATE]=
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = CsampCreateClose;
    DriverObject->MajorFunction[IRP_MJ_READ] = CsampRead;
    DriverObject->MajorFunction[IRP_MJ_CLEANUP] = CsampCleanup;

    DriverObject->DriverUnload = CsampUnload;

    //
    // Set the flag signifying that we will do buffered I/O. This causes NT
    // to allocate a buffer on a ReadFile operation which will then be copied
    // back to the calling application by the I/O subsystem
    //

    deviceObject->Flags |= DO_BUFFERED_IO;

    //
    // This is used to serailize access to the queue.
    //

    KeInitializeSpinLock(&devExtension->QueueLock);

    KeInitializeSemaphore(&devExtension->IrpQueueSemaphore, 0, MAXLONG );

    //
    // Initialize the pending Irp devicequeue
    //

    InitializeListHead( &devExtension->PendingIrpQueue );

    //
    // Initialize the cancel safe queue
    //
    IoCsqInitialize( &devExtension->CancelSafeQueue,
                     CsampInsertIrp,
                     CsampRemoveIrp,
                     CsampPeekNextIrp,
                     CsampAcquireLock,
                     CsampReleaseLock,
                     CsampCompleteCanceledIrp );
    //
    // 10 is multiplied because system time is specified in 100ns units
    //

    devExtension->PollingInterval.QuadPart = Int32x32To64(
                                CSAMP_RETRY_INTERVAL, -10);
    //
    // Note down system time
    //

    KeQuerySystemTime (&devExtension->LastPollTime);

    //
    // Start the polling thread.
    //

    devExtension->ThreadShouldStop = FALSE;

    status = PsCreateSystemThread(&threadHandle,
                                (ACCESS_MASK)0,
                                NULL,
                                (HANDLE) 0,
                                NULL,
                                CsampPollingThread,
                                deviceObject );

    if ( !NT_SUCCESS( status ))
    {
        IoDeleteSymbolicLink( &unicodeDosDeviceName );
        IoDeleteDevice( deviceObject );
        return status;
    }

    //
    // Convert the Thread object handle into a pointer to the Thread object
    // itself. Then close the handle.
    //

    ObReferenceObjectByHandle(threadHandle,
                            THREAD_ALL_ACCESS,
                            NULL,
                            KernelMode,
                            &devExtension->ThreadObject,
                            NULL );

    ZwClose(threadHandle);

    CSAMP_KDPRINT(("DriverEntry Exit = %x\n", status));

    ASSERT(NT_SUCCESS(status));

    return status;
}