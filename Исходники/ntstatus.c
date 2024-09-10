FSP_API DWORD FspWin32FromNtStatus(NTSTATUS Status)
{
    InitOnceExecuteOnce(&FspNtStatusInitOnce, FspNtStatusInitialize, 0, 0);
    if (0 == FspRtlNtStatusToDosError)
        return ERROR_MR_MID_NOT_FOUND;

    return FspRtlNtStatusToDosError(Status);
}