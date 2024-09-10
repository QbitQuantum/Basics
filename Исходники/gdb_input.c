static
void
ReadMemorySendHandler(
    _In_ ULONG PacketType,
    _In_ PSTRING MessageHeader,
    _In_ PSTRING MessageData)
{
    DBGKD_MANIPULATE_STATE64* State = (DBGKD_MANIPULATE_STATE64*)MessageHeader->Buffer;

    if (PacketType != PACKET_TYPE_KD_STATE_MANIPULATE)
    {
        // KdAssert
        KDDBGPRINT("Wrong packet type (%lu) received after DbgKdReadVirtualMemoryApi request.\n", PacketType);
        while (1);
    }

    if (State->ApiNumber != DbgKdReadVirtualMemoryApi)
    {
        KDDBGPRINT("Wrong API number (%lu) after DbgKdReadVirtualMemoryApi request.\n", State->ApiNumber);
    }

    /* Check status */
    if (!NT_SUCCESS(State->ReturnStatus))
        send_gdb_ntstatus(State->ReturnStatus);
    else
        send_gdb_memory(MessageData->Buffer, MessageData->Length);
    KdpSendPacketHandler = NULL;
    KdpManipulateStateHandler = NULL;

#if !MONOPROCESS
    /* Reset the TLB */
    if ((gdb_dbg_pid != 0) && gdb_pid_to_handle(gdb_dbg_pid) != PsGetCurrentProcessId())
    {
        __writecr3(PsGetCurrentProcess()->Pcb.DirectoryTableBase[0]);
    }
#endif
}