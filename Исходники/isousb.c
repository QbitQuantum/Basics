NTSTATUS
IsoUsb_CreateDeviceObject(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject,
    IN PDEVICE_OBJECT *DeviceObject
    )
/*++

Routine Description:

    Creates a Functional DeviceObject

Arguments:

    DriverObject - pointer to the driver object for device

    DeviceObject - pointer to DeviceObject pointer to return
		    created device object.

    Instance - instance of the device create.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise

--*/
{
    NTSTATUS ntStatus;
    UNICODE_STRING deviceLinkUnicodeString;
    PDEVICE_EXTENSION deviceExtension;
    USHORT i;
    
    UNICODE_STRING pdoUniCodeName;
    WCHAR	   pdoName[] = L"\\Device\\AVR309USB_0";

    UNICODE_STRING DeviceLinkUniCodeString;
    WCHAR          DeviceLinkName[] = L"\\DosDevices\\AVR309USB_0";
    
    RtlInitUnicodeString (&pdoUniCodeName, pdoName); // Creates Unicode Name    

    ISOUSB_KdPrint( DBGLVL_DEFAULT,("enter IsoUsb_CreateDeviceObject() \n"));

    ntStatus = IsoUsb_SymbolicLink( PhysicalDeviceObject, &deviceLinkUnicodeString );

    ISOUSB_KdPrintCond( DBGLVL_DEFAULT,
	    (NT_SUCCESS(ntStatus)),
	    ("IsoUsb_CreateDeviceObject() SUCCESS Create GUID_CLASS_IsoUsb_ISO-based Device name\n   %ws\n Length decimal %d, MaximumLength decimal %d\n",
	    deviceLinkUnicodeString.Buffer,
	    deviceLinkUnicodeString.Length,
	    deviceLinkUnicodeString.MaximumLength));

    ISOUSB_KdPrintCond( DBGLVL_DEFAULT,
	    (!(NT_SUCCESS(ntStatus))),
	    ("IsoUsb_CreateDeviceObject() FAILED to Create GUID_CLASS_ISO-based Device name\n"));

    if (NT_SUCCESS(ntStatus)) {

	ntStatus = IoCreateDevice (DriverObject,
			   sizeof (DEVICE_EXTENSION),
			   &pdoUniCodeName,
			   FILE_DEVICE_UNKNOWN,
			   0,
			   FALSE,
			   DeviceObject);

	if (NT_SUCCESS(ntStatus))  {
	     deviceExtension = (PDEVICE_EXTENSION) ((*DeviceObject)->DeviceExtension);

	}

	ISOUSB_KdPrintCond( DBGLVL_DEFAULT,
		(!(NT_SUCCESS(ntStatus))),
		("IsoUsb_CreateDeviceObject() IoCreateDevice() FAILED\n"));

	 ISOUSB_KdPrintCond( DBGLVL_DEFAULT,
		((NT_SUCCESS(ntStatus))),
		("IsoUsb_CreateDeviceObject() IoCreateDevice() SUCCESS\n"));


	if (!NT_SUCCESS(ntStatus))  {
	     return ntStatus;
	}

        RtlInitUnicodeString (&DeviceLinkUniCodeString, DeviceLinkName);
        ntStatus = IoCreateSymbolicLink(&DeviceLinkUniCodeString, &pdoUniCodeName);

	//default maximum transfer size per io request
	deviceExtension->MaximumTransferSize =  ISO_MAX_TRANSFER_SIZE ;

#if DBG
        // may be overridden in registry
        IsoUsb_GetRegistryDword( ISOUSB_REGISTRY_PARAMETERS_PATH,
                                         L"MaximumTransferSize",
                                         &(deviceExtension->MaximumTransferSize) );
#endif

	// Name buffer for our named Functional device object link
	// The name is generated based on the driver's class GUID
	RtlCopyMemory(deviceExtension->DeviceLinkNameBuffer,
		      deviceLinkUnicodeString.Buffer,
		      deviceLinkUnicodeString.Length);


	// this event is triggered when there is no pending io of any kind and device is removed
	KeInitializeEvent(&deviceExtension->RemoveEvent, NotificationEvent, FALSE);

	// this event is triggered when self-requested power irps complete
	KeInitializeEvent(&deviceExtension->SelfRequestedPowerIrpEvent, NotificationEvent, FALSE);

	// this event is triggered when there is no pending io  (pending io count == 1 )
	KeInitializeEvent(&deviceExtension->NoPendingIoEvent, NotificationEvent, FALSE);

		//free buffer from unicode string we used to init interface
		RtlFreeUnicodeString( &deviceLinkUnicodeString );
    }

     ISOUSB_KdPrintCond( DBGLVL_DEFAULT,
	    ((NT_SUCCESS(ntStatus))),
	    ("Exit IsoUsb_CreateDeviceObject() IoCreateDevice() SUCCESS\n"));


    return ntStatus;
}