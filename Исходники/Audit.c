void
DisplayNtStatus(
    LPSTR szAPI,
    NTSTATUS Status
    )
{
    //
    // convert the NTSTATUS to Winerror and DisplayWinError()
    //
    DisplayWinError(szAPI, LsaNtStatusToWinError(Status) );
}