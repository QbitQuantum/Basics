// AddDevice, called when an instance of our supported hardware is found
// Returning anything other than NT_SUCCESS here causes the device to fail
// to initialise
NTSTATUS NTAPI FreeBT_AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
    NTSTATUS			ntStatus;
    PDEVICE_OBJECT		deviceObject;
    PDEVICE_EXTENSION	deviceExtension;
    POWER_STATE			state;
    KIRQL				oldIrql;
	UNICODE_STRING		uniDeviceName;
	WCHAR				wszDeviceName[255]={0};
	UNICODE_STRING		uniDosDeviceName;
	LONG				instanceNumber=0;

    FreeBT_DbgPrint(3, ("FBTUSB: FreeBT_AddDevice: Entered\n"));

    deviceObject = NULL;

	swprintf(wszDeviceName, L"\\Device\\FbtUsb%02d", instanceNumber);
	RtlInitUnicodeString(&uniDeviceName, wszDeviceName);
	ntStatus=STATUS_OBJECT_NAME_COLLISION;
	while (instanceNumber<99 && !NT_SUCCESS(ntStatus))
	{
		swprintf(wszDeviceName, L"\\Device\\FbtUsb%02d", instanceNumber);
		uniDeviceName.Length = wcslen(wszDeviceName) * sizeof(WCHAR);
		FreeBT_DbgPrint(1, ("FBTUSB: Attempting to create device %ws\n", wszDeviceName));
		ntStatus = IoCreateDevice(
						DriverObject,                   // our driver object
						sizeof(DEVICE_EXTENSION),       // extension size for us
						&uniDeviceName,					// name for this device
						FILE_DEVICE_UNKNOWN,
						0,								// device characteristics
						FALSE,                          // Not exclusive
						&deviceObject);                 // Our device object

		if (!NT_SUCCESS(ntStatus))
			instanceNumber++;

	}

    if (!NT_SUCCESS(ntStatus))
	{
        FreeBT_DbgPrint(1, ("FBTUSB: Failed to create device object\n"));
        return ntStatus;

    }

	FreeBT_DbgPrint(1, ("FBTUSB: Created device %ws\n", wszDeviceName));

    deviceExtension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension;
    deviceExtension->FunctionalDeviceObject = deviceObject;
    deviceExtension->PhysicalDeviceObject = PhysicalDeviceObject;
    deviceObject->Flags |= DO_DIRECT_IO;

	swprintf(deviceExtension->wszDosDeviceName, L"\\DosDevices\\FbtUsb%02d", instanceNumber);
	RtlInitUnicodeString(&uniDosDeviceName, deviceExtension->wszDosDeviceName);
	ntStatus=IoCreateSymbolicLink(&uniDosDeviceName, &uniDeviceName);
	if (!NT_SUCCESS(ntStatus))
	{
		FreeBT_DbgPrint(1, ("FBTUSB: Failed to create symbolic link %ws to %ws, status=0x%08x\n", deviceExtension->wszDosDeviceName, wszDeviceName, ntStatus));
		IoDeleteDevice(deviceObject);
		return ntStatus;

	}

	FreeBT_DbgPrint(1, ("FBTUSB: Created symbolic link %ws\n", deviceExtension->wszDosDeviceName));

    KeInitializeSpinLock(&deviceExtension->DevStateLock);

    INITIALIZE_PNP_STATE(deviceExtension);

    deviceExtension->OpenHandleCount = 0;

    // Initialize the selective suspend variables
    KeInitializeSpinLock(&deviceExtension->IdleReqStateLock);
    deviceExtension->IdleReqPend = 0;
    deviceExtension->PendingIdleIrp = NULL;

    // Hold requests until the device is started
    deviceExtension->QueueState = HoldRequests;

    // Initialize the queue and the queue spin lock
    InitializeListHead(&deviceExtension->NewRequestsQueue);
    KeInitializeSpinLock(&deviceExtension->QueueLock);

    // Initialize the remove event to not-signaled.
    KeInitializeEvent(&deviceExtension->RemoveEvent, SynchronizationEvent, FALSE);

    // Initialize the stop event to signaled.
    // This event is signaled when the OutstandingIO becomes 1
    KeInitializeEvent(&deviceExtension->StopEvent, SynchronizationEvent, TRUE);

    // OutstandingIo count biased to 1.
    // Transition to 0 during remove device means IO is finished.
    // Transition to 1 means the device can be stopped
    deviceExtension->OutStandingIO = 1;
    KeInitializeSpinLock(&deviceExtension->IOCountLock);

#ifdef ENABLE_WMI 
    // Delegating to WMILIB
    ntStatus = FreeBT_WmiRegistration(deviceExtension);
    if (!NT_SUCCESS(ntStatus))
	{
        FreeBT_DbgPrint(1, ("FBTUSB: FreeBT_WmiRegistration failed with %X\n", ntStatus));
        IoDeleteDevice(deviceObject);
		IoDeleteSymbolicLink(&uniDosDeviceName);
        return ntStatus;

    }
#endif

    // Set the flags as underlying PDO
    if (PhysicalDeviceObject->Flags & DO_POWER_PAGABLE)
	{
        deviceObject->Flags |= DO_POWER_PAGABLE;

    }

    // Typically, the function driver for a device is its
    // power policy owner, although for some devices another
    // driver or system component may assume this role.
    // Set the initial power state of the device, if known, by calling
    // PoSetPowerState.
    deviceExtension->DevPower = PowerDeviceD0;
    deviceExtension->SysPower = PowerSystemWorking;

    state.DeviceState = PowerDeviceD0;
    PoSetPowerState(deviceObject, DevicePowerState, state);

    // attach our driver to device stack
    // The return value of IoAttachDeviceToDeviceStack is the top of the
    // attachment chain.  This is where all the IRPs should be routed.
    deviceExtension->TopOfStackDeviceObject = IoAttachDeviceToDeviceStack(deviceObject, PhysicalDeviceObject);
    if (NULL == deviceExtension->TopOfStackDeviceObject)
	{
#ifdef ENABLE_WMI
        FreeBT_WmiDeRegistration(deviceExtension);
#endif
        IoDeleteDevice(deviceObject);
		IoDeleteSymbolicLink(&uniDosDeviceName);
        return STATUS_NO_SUCH_DEVICE;

    }

    // Register device interfaces
    ntStatus = IoRegisterDeviceInterface(deviceExtension->PhysicalDeviceObject,
                                         &GUID_CLASS_FREEBT_USB,
                                         NULL,
                                         &deviceExtension->InterfaceName);
    if (!NT_SUCCESS(ntStatus))
	{
#ifdef ENABLE_WMI
        FreeBT_WmiDeRegistration(deviceExtension);
#endif
        IoDetachDevice(deviceExtension->TopOfStackDeviceObject);
        IoDeleteDevice(deviceObject);
		IoDeleteSymbolicLink(&uniDosDeviceName);
        return ntStatus;

    }

    if (IoIsWdmVersionAvailable(1, 0x20))
	{
        deviceExtension->WdmVersion = WinXpOrBetter;

    }

    else if (IoIsWdmVersionAvailable(1, 0x10))
	{
        deviceExtension->WdmVersion = Win2kOrBetter;

    }

    else if (IoIsWdmVersionAvailable(1, 0x5))
	{
        deviceExtension->WdmVersion = WinMeOrBetter;

    }

    else if (IoIsWdmVersionAvailable(1, 0x0))
	{
        deviceExtension->WdmVersion = Win98OrBetter;

    }

    deviceExtension->SSRegistryEnable = 0;
    deviceExtension->SSEnable = 0;

    // WinXP only: check the registry flag indicating whether
	// the device should selectively suspend when idle
    if (WinXpOrBetter == deviceExtension->WdmVersion)
	{
        FreeBT_GetRegistryDword(FREEBT_REGISTRY_PARAMETERS_PATH,
                                 L"BulkUsbEnable",
                                 (PULONG)(&deviceExtension->SSRegistryEnable));
        if (deviceExtension->SSRegistryEnable)
		{
            // initialize DPC
            KeInitializeDpc(&deviceExtension->DeferredProcCall, DpcRoutine, deviceObject);

            // initialize the timer.
            // the DPC and the timer in conjunction,
            // monitor the state of the device to
            // selectively suspend the device.
            KeInitializeTimerEx(&deviceExtension->Timer, NotificationTimer);

            // Initialize the NoDpcWorkItemPendingEvent to signaled state.
            // This event is cleared when a Dpc is fired and signaled
            // on completion of the work-item.
            KeInitializeEvent(&deviceExtension->NoDpcWorkItemPendingEvent, NotificationEvent, TRUE);

            // Initialize the NoIdleReqPendEvent to ensure that the idle request
            // is indeed complete before we unload the drivers.
            KeInitializeEvent(&deviceExtension->NoIdleReqPendEvent, NotificationEvent, TRUE);

        }

    }

    // Initialize the NoIdleReqPendEvent to ensure that the idle request
    // is indeed complete before we unload the drivers.
    KeInitializeEvent(&deviceExtension->DelayEvent, NotificationEvent, FALSE);

    // Clear the DO_DEVICE_INITIALIZING flag.
    // Note: Do not clear this flag until the driver has set the
    // device power state and the power DO flags.
    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
    InterlockedIncrement(&instanceNumber);

    FreeBT_DbgPrint(3, ("FBTUSB: FreeBT_AddDevice: Leaving\n"));

    return ntStatus;

}