NTSTATUS
NTAPI
INIT_FUNCTION
IopInitializePlugPlayServices(VOID)
{
    NTSTATUS Status;
    ULONG Disposition;
    HANDLE KeyHandle, EnumHandle, ParentHandle, TreeHandle, ControlHandle;
    UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\REGISTRY\\MACHINE\\SYSTEM\\CURRENTCONTROLSET");
    UNICODE_STRING PnpManagerDriverName = RTL_CONSTANT_STRING(DRIVER_ROOT_NAME L"PnpManager");
    PDEVICE_OBJECT Pdo;

    /* Initialize locks and such */
    KeInitializeSpinLock(&IopDeviceTreeLock);
    KeInitializeSpinLock(&IopDeviceRelationsSpinLock);
    InitializeListHead(&IopDeviceRelationsRequestList);

    /* Get the default interface */
    PnpDefaultInterfaceType = IopDetermineDefaultInterfaceType();

    /* Initialize arbiters */
    Status = IopInitializeArbiters();
    if (!NT_SUCCESS(Status)) return Status;

    /* Setup the group cache */
    Status = PiInitCacheGroupInformation();
    if (!NT_SUCCESS(Status)) return Status;

    /* Open the current control set */
    Status = IopOpenRegistryKeyEx(&KeyHandle,
                                  NULL,
                                  &KeyName,
                                  KEY_ALL_ACCESS);
    if (!NT_SUCCESS(Status)) return Status;

    /* Create the control key */
    RtlInitUnicodeString(&KeyName, L"Control");
    Status = IopCreateRegistryKeyEx(&ControlHandle,
                                    KeyHandle,
                                    &KeyName,
                                    KEY_ALL_ACCESS,
                                    REG_OPTION_NON_VOLATILE,
                                    &Disposition);
    if (!NT_SUCCESS(Status)) return Status;

    /* Check if it's a new key */
    if (Disposition == REG_CREATED_NEW_KEY)
    {
        HANDLE DeviceClassesHandle;

        /* Create the device classes key */
        RtlInitUnicodeString(&KeyName, L"DeviceClasses");
        Status = IopCreateRegistryKeyEx(&DeviceClassesHandle,
                                        ControlHandle,
                                        &KeyName,
                                        KEY_ALL_ACCESS,
                                        REG_OPTION_NON_VOLATILE,
                                        &Disposition);
        if (!NT_SUCCESS(Status)) return Status;

        ZwClose(DeviceClassesHandle);
    }

    ZwClose(ControlHandle);

    /* Create the enum key */
    RtlInitUnicodeString(&KeyName, REGSTR_KEY_ENUM);
    Status = IopCreateRegistryKeyEx(&EnumHandle,
                                    KeyHandle,
                                    &KeyName,
                                    KEY_ALL_ACCESS,
                                    REG_OPTION_NON_VOLATILE,
                                    &Disposition);
    if (!NT_SUCCESS(Status)) return Status;

    /* Check if it's a new key */
    if (Disposition == REG_CREATED_NEW_KEY)
    {
        /* FIXME: DACLs */
        DPRINT1("Need to build DACL\n");
    }

    /* Create the root key */
    ParentHandle = EnumHandle;
    RtlInitUnicodeString(&KeyName, REGSTR_KEY_ROOTENUM);
    Status = IopCreateRegistryKeyEx(&EnumHandle,
                                    ParentHandle,
                                    &KeyName,
                                    KEY_ALL_ACCESS,
                                    REG_OPTION_NON_VOLATILE,
                                    &Disposition);
    NtClose(ParentHandle);
    if (!NT_SUCCESS(Status)) return Status;
    NtClose(EnumHandle);

    /* Open the root key now */
    RtlInitUnicodeString(&KeyName, L"\\REGISTRY\\MACHINE\\SYSTEM\\CURRENTCONTROLSET\\ENUM");
    Status = IopOpenRegistryKeyEx(&EnumHandle,
                                  NULL,
                                  &KeyName,
                                  KEY_ALL_ACCESS);
    if (NT_SUCCESS(Status))
    {
        /* Create the root dev node */
        RtlInitUnicodeString(&KeyName, REGSTR_VAL_ROOT_DEVNODE);
        Status = IopCreateRegistryKeyEx(&TreeHandle,
                                        EnumHandle,
                                        &KeyName,
                                        KEY_ALL_ACCESS,
                                        REG_OPTION_NON_VOLATILE,
                                        NULL);
        NtClose(EnumHandle);
        if (NT_SUCCESS(Status)) NtClose(TreeHandle);
    }

    /* Create the root driver */
    Status = IoCreateDriver(&PnpManagerDriverName, PnpRootDriverEntry);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("IoCreateDriverObject() failed\n");
        KeBugCheckEx(PHASE1_INITIALIZATION_FAILED, Status, 0, 0, 0);
    }

    /* Create the root PDO */
    Status = IoCreateDevice(IopRootDriverObject,
                            sizeof(IOPNP_DEVICE_EXTENSION),
                            NULL,
                            FILE_DEVICE_CONTROLLER,
                            0,
                            FALSE,
                            &Pdo);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("IoCreateDevice() failed\n");
        KeBugCheckEx(PHASE1_INITIALIZATION_FAILED, Status, 0, 0, 0);
    }

    /* This is a bus enumerated device */
    Pdo->Flags |= DO_BUS_ENUMERATED_DEVICE;

    /* Create the root device node */
    IopRootDeviceNode = PipAllocateDeviceNode(Pdo);

    /* Set flags */
    IopRootDeviceNode->Flags |= DNF_STARTED + DNF_PROCESSED + DNF_ENUMERATED +
                                DNF_MADEUP + DNF_NO_RESOURCE_REQUIRED +
                                DNF_ADDED;

    /* Create instance path */
    RtlCreateUnicodeString(&IopRootDeviceNode->InstancePath,
                           REGSTR_VAL_ROOT_DEVNODE);

    /* Call the add device routine */
    IopRootDriverObject->DriverExtension->AddDevice(IopRootDriverObject,
                                                    IopRootDeviceNode->PhysicalDeviceObject);

    /* Initialize PnP-Event notification support */
    Status = IopInitPlugPlayEvents();
    if (!NT_SUCCESS(Status)) return Status;

    /* Report the device to the user-mode pnp manager */
    IopQueueTargetDeviceEvent(&GUID_DEVICE_ARRIVAL,
                              &IopRootDeviceNode->InstancePath);

    /* Initialize the Bus Type GUID List */
    PnpBusTypeGuidList = ExAllocatePool(PagedPool, sizeof(IO_BUS_TYPE_GUID_LIST));
    RtlZeroMemory(PnpBusTypeGuidList, sizeof(IO_BUS_TYPE_GUID_LIST));
    ExInitializeFastMutex(&PnpBusTypeGuidList->Lock);

    /* Launch the firmware mapper */
    Status = IopUpdateRootKey();
    if (!NT_SUCCESS(Status)) return Status;

    /* Close the handle to the control set */
    NtClose(KeyHandle);

    /* We made it */
    return STATUS_SUCCESS;
}