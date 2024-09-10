MIXER_STATUS
CreatePinCallback(
    IN PVOID Ctx,
    IN ULONG VirtualDeviceId,
    IN ULONG PinId,
    IN HANDLE hFilter,
    IN PKSPIN_CONNECT PinConnect,
    IN ACCESS_MASK DesiredAccess,
    OUT PHANDLE PinHandle)
{
    ULONG BytesReturned;
    SYSAUDIO_INSTANCE_INFO InstanceInfo;
    NTSTATUS Status;
    ULONG FreeIndex;
    PPIN_CREATE_CONTEXT Context = (PPIN_CREATE_CONTEXT)Ctx;

    /* setup property request */
    InstanceInfo.Property.Set = KSPROPSETID_Sysaudio;
    InstanceInfo.Property.Id = KSPROPERTY_SYSAUDIO_INSTANCE_INFO;
    InstanceInfo.Property.Flags = KSPROPERTY_TYPE_SET;
    InstanceInfo.Flags = 0;
    InstanceInfo.DeviceNumber = VirtualDeviceId;

    /* attach to virtual device */
    Status = KsSynchronousIoControlDevice(Context->DeviceExtension->FileObject, KernelMode, IOCTL_KS_PROPERTY, (PVOID)&InstanceInfo, sizeof(SYSAUDIO_INSTANCE_INFO), NULL, 0, &BytesReturned);

    if (!NT_SUCCESS(Status))
        return MM_STATUS_UNSUCCESSFUL;

    /* close existing pin */
    FreeIndex = ClosePin(Context->ClientInfo, VirtualDeviceId, PinId, Context->DeviceType);

    /* now create the pin */
    Status = KsCreatePin(Context->DeviceExtension->hSysAudio, PinConnect, DesiredAccess, PinHandle);

    /* check for success */
    if (!NT_SUCCESS(Status))
        return MM_STATUS_UNSUCCESSFUL;

    /* store the handle */
    Status = InsertPinHandle(Context->ClientInfo, VirtualDeviceId, PinId, Context->DeviceType, *PinHandle, FreeIndex);
    if (!NT_SUCCESS(Status))
    {
        /* failed to insert handle */
        ZwClose(*PinHandle);
        return MM_STATUS_UNSUCCESSFUL;
    }

    return MM_STATUS_SUCCESS;
}