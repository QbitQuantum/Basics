VOID
NTAPI
RawChannelSetIBufferIndex(IN PSAC_CHANNEL Channel,
                          IN ULONG BufferIndex)
{
    NTSTATUS Status;
    ASSERT(Channel);
    ASSERT(Channel->IBufferIndex < SAC_RAW_IBUFFER_SIZE);

    /* Set the new index, and if it's not zero, it means we have data */
    Channel->IBufferIndex = BufferIndex;
    _InterlockedExchange(&Channel->ChannelHasNewIBufferData, BufferIndex != 0);

    /* If we have new data, and an event has been registered... */
    if (!(Channel->IBufferIndex) &&
        (Channel->Flags & SAC_CHANNEL_FLAG_HAS_NEW_DATA_EVENT))
    {
        /* Go ahead and signal it */
        ChannelClearEvent(Channel, HasNewDataEvent);
        UNREFERENCED_PARAMETER(Status);
    }
}