NTSTATUS DriverEntry( IN PDRIVER_OBJECT DriverObject,
                      IN PUNICODE_STRING RegistryPath )
{
    /* IRQL == PASSIVE_LEVEL */

    UNREFERENCED_PARAMETER( DriverObject );
    UNREFERENCED_PARAMETER( RegistryPath );

    NTSTATUS status;

    DbgPrint( "file system protection filter start" );

    /* initialize IRP */

    InitializeIrpDispatchers( DriverObject );

    /* create device */

    UNICODE_STRING deviceObjectName;
    RtlInitUnicodeString( &deviceObjectName, L"\\device\\disklocker_fsprotdrv" );

    PDEVICE_OBJECT DeviceObject;
    status = CreateIoDevice( deviceObjectName, DriverObject, &DeviceObject );

    if (!NT_SUCCESS( status ))
    {
        DbgPrint( "CreateIoDevice() failed with code = %08x\n", status );
        return status;
    }

    SetDeviceExt( DeviceObject->DeviceExtension );

    /* initialize device extension */

    GetDeviceExt()->DeviceObject = DeviceObject;
    GetDeviceExt()->DriverObject = DriverObject;
    GetDeviceExt()->UnloadRoutine = OnUnload;
    GetDeviceExt()->FileListHead = NULL;
    GetDeviceExt()->LastUniqueKey = 1;

    KeInitializeSpinLock( &(GetDeviceExt()->FileListAccessSpinLock) );

    /* create symlink */

    RtlInitUnicodeString( &SymbolicLinkName, L"\\DosDevices\\disklocker_fsprotdrv" );

    status = IoCreateSymbolicLink( &SymbolicLinkName, &deviceObjectName );

    if (!NT_SUCCESS( status ))
    {
        /* delete registered device */
        IoDeleteDevice( GetDeviceExt()->DeviceObject );

        DbgPrint( "IoCreateSymbolicLink() failed with code = %08x\n", status );
        return status;
    }

    /* register filter */

    status = FltRegisterFilter( DriverObject, &FilterRegistration, &(GetDeviceExt()->FltFilter) );

    if (!NT_SUCCESS( status ))
    {
        /* delete registered symbolic link */
        IoDeleteSymbolicLink( &SymbolicLinkName );

        /* delete registered device */
        IoDeleteDevice( GetDeviceExt()->DeviceObject );

        DbgPrint( "FltRegisterFilter() failed with code = %08x\n", status );
        return status;
    }

    /* start filtering */

    status = FltStartFiltering( GetDeviceExt()->FltFilter );
    if (!NT_SUCCESS( status ))
    {
        /* delete registered symbolic link */
        IoDeleteSymbolicLink( &SymbolicLinkName );

        /* delete registered device */
        IoDeleteDevice( GetDeviceExt()->DeviceObject );

        /* unregister filter */
        FltUnregisterFilter( GetDeviceExt()->FltFilter );

        DbgPrint( "FltStartFiltering() failed with code = %08x\n", status );
        return status;
    }

    /* initialization done */

    DbgPrint( "file system filter initialization done..." );
    return STATUS_SUCCESS;
}