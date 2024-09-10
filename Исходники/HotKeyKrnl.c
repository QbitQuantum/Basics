NTSTATUS 
HotKeyKrnlAttachDevices( 
    IN PDRIVER_OBJECT   DriverObject, 
    IN PUNICODE_STRING  RegistryPath 
    ) 
{ 
    NTSTATUS status = 0; 
    UNICODE_STRING uniNtNameString; 
    PDEVICE_EXTENSION   devExt; 
    PDEVICE_OBJECT pFilterDeviceObject = NULL; 
    PDEVICE_OBJECT pTargetDeviceObject = NULL; 
    PDEVICE_OBJECT pLowerDeviceObject  = NULL; 
    PDRIVER_OBJECT KbdDriverObject     = NULL;
    extern POBJECT_TYPE *IoDriverObjectType;    // Exported by ntoskrnl.exe, shit !

    // ref kbdclass driver object
    RtlInitUnicodeString(&uniNtNameString, KBD_DRIVER_NAME); 
    status = ObReferenceObjectByName(&uniNtNameString, OBJ_CASE_INSENSITIVE, NULL, 0, *IoDriverObjectType, KernelMode, NULL, &KbdDriverObject);
    if(!NT_SUCCESS(status))
    {
        KdPrint(("[shadow] ObReferenceObjectByName failed,cann't access Kbdclass.\n"));
        return status; 
    }
    else
    {
        ObDereferenceObject(KbdDriverObject);
    }

    // 绑定该驱动对象中的所有设备对象
    pTargetDeviceObject = KbdDriverObject->DeviceObject;
    while (pTargetDeviceObject) 
    {
        // 创建过滤设备
        status = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), NULL, pTargetDeviceObject->DeviceType, pTargetDeviceObject->Characteristics, FALSE, &pFilterDeviceObject);
        if (!NT_SUCCESS(status)) 
        { 
            KdPrint(("[shadow] IoCreateDevice(filter device) failed.\n")); 
            return status; 
        } 
        // 绑定
        if(!(pLowerDeviceObject = IoAttachDeviceToDeviceStack(pFilterDeviceObject, pTargetDeviceObject)))
        { 
            KdPrint(("[shadow] IoAttachDeviceToDeviceStack failed.\n")); 
            IoDeleteDevice(pFilterDeviceObject);
            pFilterDeviceObject = NULL; 
            return status; 
        }

        devExt = (PDEVICE_EXTENSION)(pFilterDeviceObject->DeviceExtension); 
        RtlZeroMemory(devExt, sizeof(DEVICE_EXTENSION)); 
        devExt->NodeSize = sizeof(DEVICE_EXTENSION); 
        devExt->pFilterDeviceObject = pFilterDeviceObject;
        devExt->TargetDeviceObject = pTargetDeviceObject; 
        devExt->LowerDeviceObject = pLowerDeviceObject; 

        pFilterDeviceObject->DeviceType = pLowerDeviceObject->DeviceType; 
        pFilterDeviceObject->Characteristics = pLowerDeviceObject->Characteristics; 
        pFilterDeviceObject->StackSize = pLowerDeviceObject->StackSize+1; 
        pFilterDeviceObject->Flags |= pLowerDeviceObject->Flags & (DO_BUFFERED_IO | DO_DIRECT_IO | DO_POWER_PAGABLE); 

        pTargetDeviceObject = pTargetDeviceObject->NextDevice;
    }
    return status; 
} 