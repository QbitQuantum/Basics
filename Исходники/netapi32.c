NET_API_STATUS
WINAPI
NetpNtStatusToApiStatus(NTSTATUS Status)
{
    return RtlNtStatusToDosError(Status);
}