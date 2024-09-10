/******************************************************************************
 * LsaNtStatusToWinError [ADVAPI32.@]
 *
 * Converts an LSA NTSTATUS code to a Windows error code.
 *
 * PARAMS
 *  Status [I] NTSTATUS code.
 *
 * RETURNS
 *  Success: Corresponding Windows error code.
 *  Failure: ERROR_MR_MID_NOT_FOUND.
 */
ULONG WINAPI LsaNtStatusToWinError(NTSTATUS Status)
{
    return RtlNtStatusToDosError(Status);
}