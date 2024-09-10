NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT   pDriverObject,
    IN PUNICODE_STRING  pRegistryPath
    )
/*++

Routine Description:

    Called on loading. We create a device object to handle user-mode requests
    on, and register ourselves as a protocol with NDIS.

Arguments:

    pDriverObject - Pointer to driver object created by system.

    pRegistryPath - Pointer to the Unicode name of the registry path
        for this driver.

Return Value:

    NT Status code
    
--*/
{
    NDIS_PROTOCOL_CHARACTERISTICS   protocolChar;
    NTSTATUS                        status = STATUS_SUCCESS;
    NDIS_STRING                     protoName = NDIS_STRING_CONST("NdisProt");     
    UNICODE_STRING                  ntDeviceName;
    UNICODE_STRING                  win32DeviceName;
    BOOLEAN                         fSymbolicLink = FALSE;
    PDEVICE_OBJECT                  deviceObject = NULL;

    UNREFERENCED_PARAMETER(pRegistryPath);

    DEBUGP(DL_LOUD, ("DriverEntry\n"));

    Globals.pDriverObject = pDriverObject;
    NPROT_INIT_EVENT(&Globals.BindsComplete);

    do
    {

        //
        // Create our device object using which an application can
        // access NDIS devices.
        //
        RtlInitUnicodeString(&ntDeviceName, NT_DEVICE_NAME);
#ifndef WIN9X
        status = IoCreateDeviceSecure(pDriverObject,
                                 0,
                                 &ntDeviceName,
                                 FILE_DEVICE_NETWORK,
                                 FILE_DEVICE_SECURE_OPEN,
                                 FALSE,
                                 &SDDL_DEVOBJ_SYS_ALL_ADM_ALL,
                                 NULL,
                                 &deviceObject);

#else     
        status = IoCreateDevice(pDriverObject,
                                 0,
                                 &ntDeviceName,
                                 FILE_DEVICE_NETWORK,
                                 FILE_DEVICE_SECURE_OPEN,
                                 FALSE,
                                 &deviceObject);
#endif
        if (!NT_SUCCESS (status))
        {
            //
            // Either not enough memory to create a deviceobject or another
            // deviceobject with the same name exits. This could happen
            // if you install another instance of this device.
            //
            break;
        }

        RtlInitUnicodeString(&win32DeviceName, DOS_DEVICE_NAME);

        status = IoCreateSymbolicLink(&win32DeviceName, &ntDeviceName);

        if (!NT_SUCCESS(status))
        {
            break;
        }

        fSymbolicLink = TRUE;
    
        deviceObject->Flags |= DO_DIRECT_IO;
        Globals.ControlDeviceObject = deviceObject;

        NPROT_INIT_LIST_HEAD(&Globals.OpenList);
        NPROT_INIT_LOCK(&Globals.GlobalLock);

        //
        // Initialize the protocol characterstic structure
        //
    
        NdisZeroMemory(&protocolChar,sizeof(NDIS_PROTOCOL_CHARACTERISTICS));

        protocolChar.MajorNdisVersion            = 5;
        protocolChar.MinorNdisVersion            = 0;
        protocolChar.Name                        = protoName;
        protocolChar.OpenAdapterCompleteHandler  = NdisProtOpenAdapterComplete;
        protocolChar.CloseAdapterCompleteHandler = NdisProtCloseAdapterComplete;
        protocolChar.SendCompleteHandler         = NdisProtSendComplete;
        protocolChar.TransferDataCompleteHandler = NdisProtTransferDataComplete;
        protocolChar.ResetCompleteHandler        = NdisProtResetComplete;
        protocolChar.RequestCompleteHandler      = NdisProtRequestComplete;
        protocolChar.ReceiveHandler              = NdisProtReceive;
        protocolChar.ReceiveCompleteHandler      = NdisProtReceiveComplete;
        protocolChar.StatusHandler               = NdisProtStatus;
        protocolChar.StatusCompleteHandler       = NdisProtStatusComplete;
        protocolChar.BindAdapterHandler          = NdisProtBindAdapter;
        protocolChar.UnbindAdapterHandler        = NdisProtUnbindAdapter;
        protocolChar.UnloadHandler               = NULL;
        protocolChar.ReceivePacketHandler        = NdisProtReceivePacket;
        protocolChar.PnPEventHandler             = NdisProtPnPEventHandler;

        //
        // Register as a protocol driver
        //
    
        NdisRegisterProtocol(
            (PNDIS_STATUS)&status,
            &Globals.NdisProtocolHandle,
            &protocolChar,
            sizeof(NDIS_PROTOCOL_CHARACTERISTICS));

        if (status != NDIS_STATUS_SUCCESS)
        {
            DEBUGP(DL_WARN, ("Failed to register protocol with NDIS\n"));
            status = STATUS_UNSUCCESSFUL;
            break;
        }

#ifdef NDIS51
        Globals.PartialCancelId = NdisGeneratePartialCancelId();
        Globals.PartialCancelId <<= ((sizeof(PVOID) - 1) * 8);
        DEBUGP(DL_LOUD, ("DriverEntry: CancelId %lx\n", Globals.PartialCancelId));
#endif

        //
        // Now set only the dispatch points we would like to handle.
        //
        pDriverObject->MajorFunction[IRP_MJ_CREATE] = NdisProtOpen;
        pDriverObject->MajorFunction[IRP_MJ_CLOSE]  = NdisProtClose;
        pDriverObject->MajorFunction[IRP_MJ_READ]   = NdisProtRead; 
        pDriverObject->MajorFunction[IRP_MJ_WRITE]  = NdisProtWrite;
        pDriverObject->MajorFunction[IRP_MJ_CLEANUP]  = NdisProtCleanup;
        pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]  = NdisProtIoControl;
        pDriverObject->DriverUnload = NdisProtUnload;

        status = STATUS_SUCCESS;
        
    }
    while (FALSE);
       

    if (!NT_SUCCESS(status))
    {
        if (deviceObject)
        {
            #pragma prefast(disable:28107, "within critical section, device object is held")
            KeEnterCriticalRegion();
            IoDeleteDevice(deviceObject);
            Globals.ControlDeviceObject = NULL;
            KeLeaveCriticalRegion();
        }

        if (fSymbolicLink)
        {
            IoDeleteSymbolicLink(&win32DeviceName);
        }
        
    }
    
    return status;

}