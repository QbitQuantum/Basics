NTSTATUS
HidClassPDO_HandleQueryDeviceId(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp)
{
    NTSTATUS Status;
    LPWSTR Buffer;
    LPWSTR NewBuffer, Ptr;
    ULONG Length;

    //
    // copy current stack location
    //
    IoCopyCurrentIrpStackLocationToNext(Irp);

    //
    // call mini-driver
    //
    Status = HidClassFDO_DispatchRequestSynchronous(DeviceObject, Irp);
    if (!NT_SUCCESS(Status))
    {
        //
        // failed
        //
        return Status;
    }

    //
    // get buffer
    //
    Buffer = (LPWSTR)Irp->IoStatus.Information;
    Length = wcslen(Buffer);

    //
    // allocate new buffer
    //
    NewBuffer = ExAllocatePoolWithTag(NonPagedPool, (Length + 1) * sizeof(WCHAR), HIDCLASS_TAG);
    if (!NewBuffer)
    {
        //
        // failed to allocate buffer
        //
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //
    // replace bus
    //
    wcscpy(NewBuffer, L"HID\\");

    //
    // get offset to first '\\'
    //
    Ptr = wcschr(Buffer, L'\\');
    if (Ptr)
    {
        //
        // append result
        //
        wcscat(NewBuffer, Ptr + 1);
    }

    //
    // free old buffer
    //
    ExFreePoolWithTag(Buffer, 0);

    //
    // store result
    //
    DPRINT("NewBuffer %S\n", NewBuffer);
    Irp->IoStatus.Information = (ULONG_PTR)NewBuffer;
    return STATUS_SUCCESS;
}