/*
 * Fills the IFEntry buffer from tcpip.sys.
 * The buffer size MUST be FIELD_OFFSET(IFEntry, if_descr[MAX_ADAPTER_DESCRIPTION_LENGTH + 1]).
 * See MSDN IFEntry struct definition if you don't believe me. ;-)
 */
static
NTSTATUS
GetInterfaceEntry(
    _In_ HANDLE TcpFile,
    _In_ TDIEntityID InterfaceID,
    _Out_ IFEntry* Entry)
{
    TCP_REQUEST_QUERY_INFORMATION_EX TcpQueryInfo;
    IO_STATUS_BLOCK StatusBlock;
    NTSTATUS Status;

    ZeroMemory(&TcpQueryInfo, sizeof(TcpQueryInfo));
    TcpQueryInfo.ID.toi_class = INFO_CLASS_PROTOCOL;
    TcpQueryInfo.ID.toi_type = INFO_TYPE_PROVIDER;
    TcpQueryInfo.ID.toi_id = IP_MIB_STATS_ID;
    TcpQueryInfo.ID.toi_entity = InterfaceID;

    Status = NtDeviceIoControlFile(
        TcpFile,
        NULL,
        NULL,
        NULL,
        &StatusBlock,
        IOCTL_TCP_QUERY_INFORMATION_EX,
        &TcpQueryInfo,
        sizeof(TcpQueryInfo),
        Entry,
        FIELD_OFFSET(IFEntry, if_descr[MAX_ADAPTER_DESCRIPTION_LENGTH + 1]));
    if (Status == STATUS_PENDING)
    {
        /* So we have to wait a bit */
        Status = NtWaitForSingleObject(TcpFile, FALSE, NULL);
        if (NT_SUCCESS(Status))
            Status = StatusBlock.Status;
    }

    return Status;
}