/*
 * @implemented
 */
BOOL
WINAPI
EmptyWorkingSet(HANDLE hProcess)
{
    SYSTEM_INFO SystemInfo;
    QUOTA_LIMITS QuotaLimits;
    NTSTATUS Status;

    GetSystemInfo(&SystemInfo);

    /* Query the working set */
    Status = NtQueryInformationProcess(hProcess,
                                       ProcessQuotaLimits,
                                       &QuotaLimits,
                                       sizeof(QuotaLimits),
                                       NULL);

    if (!NT_SUCCESS(Status))
    {
        SetLastError(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    /* Empty the working set */
    QuotaLimits.MinimumWorkingSetSize = -1;
    QuotaLimits.MaximumWorkingSetSize = -1;

    /* Set the working set */
    Status = NtSetInformationProcess(hProcess,
                                     ProcessQuotaLimits,
                                     &QuotaLimits,
                                     sizeof(QuotaLimits));
    if (!NT_SUCCESS(Status) && Status != STATUS_PRIVILEGE_NOT_HELD)
    {
        SetLastError(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    return TRUE;
}