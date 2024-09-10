bool NtQuerySysHandleInfo(DynBuf & buf)
{
    ULONG RequiredSize = NULL;

    buf.Allocate(sizeof(SYSTEM_HANDLE_INFORMATION));

    NtQuerySystemInformation(SystemHandleInformation, buf.GetPtr(), (ULONG)buf.Size(), &RequiredSize);

    buf.Allocate(RequiredSize + sizeof(SYSTEM_HANDLE_INFORMATION));

    return (NtQuerySystemInformation(SystemHandleInformation, buf.GetPtr(), (ULONG)buf.Size(), &RequiredSize) >= 0);
}