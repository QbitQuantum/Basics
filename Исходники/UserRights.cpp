void CheckRetVal(NTSTATUS res, ULONG okRetVal = ERROR_SUCCESS)
{
    ULONG err = LsaNtStatusToWinError(res);
    if (err != ERROR_SUCCESS && err != okRetVal)
    {
        Win32Exception::Throw(err);
    }
}