NTSTATUS
NTAPI
VTUTF8ChannelCreate(IN PSAC_CHANNEL Channel)
{
    NTSTATUS Status;
    CHECK_PARAMETER(Channel);

    /* Allocate the output buffer */
    Channel->OBuffer = SacAllocatePool(SAC_VTUTF8_OBUFFER_SIZE, GLOBAL_BLOCK_TAG);
    CHECK_ALLOCATION(Channel->OBuffer);

    /* Allocate the input buffer */
    Channel->IBuffer = SacAllocatePool(SAC_VTUTF8_IBUFFER_SIZE, GLOBAL_BLOCK_TAG);
    CHECK_ALLOCATION(Channel->IBuffer);

    /* Initialize the output stream */
    Status = VTUTF8ChannelOInit(Channel);
    if (NT_SUCCESS(Status)) return Status;

    /* Reset all flags and return success */
    _InterlockedExchange(&Channel->ChannelHasNewOBufferData, 0);
    _InterlockedExchange(&Channel->ChannelHasNewIBufferData, 0);
    return STATUS_SUCCESS;
}