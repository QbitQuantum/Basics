NTSTATUS
NTAPI
PcRegisterSubdevice(
    IN  PDEVICE_OBJECT DeviceObject,
    IN  PWCHAR Name,
    IN  PUNKNOWN Unknown)
{
    PPCLASS_DEVICE_EXTENSION DeviceExt;
    NTSTATUS Status;
    ISubdevice *SubDevice;
    UNICODE_STRING SymbolicLinkName;
    PSUBDEVICE_DESCRIPTOR SubDeviceDescriptor;
    ULONG Index;
    UNICODE_STRING RefName;
    PSYMBOLICLINK_ENTRY SymEntry;

    DPRINT("PcRegisterSubdevice DeviceObject %p Name %S Unknown %p\n", DeviceObject, Name, Unknown);

    PC_ASSERT_IRQL_EQUAL(PASSIVE_LEVEL);

    // check if all parameters are valid
    if (!DeviceObject || !Name || !Unknown)
    {
        DPRINT("PcRegisterSubdevice invalid parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    // get device extension
    DeviceExt = (PPCLASS_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

    if (!DeviceExt)
    {
        // should not happen
        DbgBreakPoint();
        return STATUS_UNSUCCESSFUL;
    }

    // look up our undocumented interface
    Status = Unknown->QueryInterface(IID_ISubdevice, (LPVOID*)&SubDevice);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("No ISubdevice interface\n");
        // the provided port driver doesnt support ISubdevice
        return STATUS_INVALID_PARAMETER;
    }

    // get the subdevice descriptor
    Status = SubDevice->GetDescriptor(&SubDeviceDescriptor);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Failed to get subdevice descriptor %x\n", Status);
        SubDevice->Release();
        return STATUS_UNSUCCESSFUL;
    }

    // add an create item to the device header
    Status = KsAddObjectCreateItemToDeviceHeader(DeviceExt->KsDeviceHeader, PcCreateItemDispatch, (PVOID)SubDevice, Name, NULL);
    if (!NT_SUCCESS(Status))
    {
        // failed to attach
        SubDevice->Release();
        DPRINT("KsAddObjectCreateItemToDeviceHeader failed with %x\n", Status);
        return Status;
    }

    // initialize reference string
    RtlInitUnicodeString(&RefName, Name);
    RtlInitUnicodeString(&SubDeviceDescriptor->RefString, Name);

    for(Index = 0; Index < SubDeviceDescriptor->InterfaceCount; Index++)
    {
        // FIXME
        // check if reference string with that name already exists
        
        Status = IoRegisterDeviceInterface(DeviceExt->PhysicalDeviceObject,
                                           &SubDeviceDescriptor->Interfaces[Index],
                                           &RefName,
                                           &SymbolicLinkName);

        if (NT_SUCCESS(Status))
        {
            // activate device interface
            IoSetDeviceInterfaceState(&SymbolicLinkName, TRUE);
            // allocate symbolic link entry
            SymEntry = (PSYMBOLICLINK_ENTRY)AllocateItem(NonPagedPool, sizeof(SYMBOLICLINK_ENTRY), TAG_PORTCLASS);
            if (SymEntry)
            {
                // initialize symbolic link item
                RtlInitUnicodeString(&SymEntry->SymbolicLink, SymbolicLinkName.Buffer);
                // store item
                InsertTailList(&SubDeviceDescriptor->SymbolicLinkList, &SymEntry->Entry);
            }
            else
            {
                // allocating failed
                RtlFreeUnicodeString(&SymbolicLinkName);
            }
        }
    }

    // release SubDevice reference
    SubDevice->Release();

    return STATUS_SUCCESS;
}