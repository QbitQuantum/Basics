NTSTATUS
NTAPI
IKsAllocator_fnQueryInterface(
    IKsAllocator * iface,
    IN  REFIID refiid,
    OUT PVOID* Output)
{
    PALLOCATOR This = (PALLOCATOR)CONTAINING_RECORD(iface, ALLOCATOR, lpVtbl);

    if (IsEqualGUIDAligned(refiid, &IID_IUnknown) ||
        IsEqualGUIDAligned(refiid, &IID_IKsAllocator))
    {
        *Output = &This->lpVtbl;
        _InterlockedIncrement(&This->ref);
        return STATUS_SUCCESS;
    }
    return STATUS_UNSUCCESSFUL;
}