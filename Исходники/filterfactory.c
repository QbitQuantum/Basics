NTSTATUS
NTAPI
IKsFilterFactory_fnQueryInterface(
    IKsFilterFactory * iface,
    IN  REFIID refiid,
    OUT PVOID* Output)
{
    NTSTATUS Status;

    IKsFilterFactoryImpl * This = (IKsFilterFactoryImpl*)CONTAINING_RECORD(iface, IKsFilterFactoryImpl, Header.OuterUnknown);

    if (IsEqualGUIDAligned(refiid, &IID_IUnknown))
    {
        *Output = &This->Header.OuterUnknown;
        _InterlockedIncrement(&This->ref);
        return STATUS_SUCCESS;
    }

    if (This->Header.ClientAggregate)
    {
         /* using client aggregate */
         Status = This->Header.ClientAggregate->lpVtbl->QueryInterface(This->Header.ClientAggregate, refiid, Output);

         if (NT_SUCCESS(Status))
         {
             /* client aggregate supports interface */
             return Status;
         }
    }

    DPRINT("IKsFilterFactory_fnQueryInterface no interface\n");
    return STATUS_NOT_SUPPORTED;
}