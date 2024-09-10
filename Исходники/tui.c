static INT
TUILoggedOutSAS(
    IN OUT PGINA_CONTEXT pgContext)
{
    WCHAR UserName[256];
    WCHAR Password[256];
    NTSTATUS Status;
    NTSTATUS SubStatus = STATUS_SUCCESS;

    TRACE("TUILoggedOutSAS()\n");

    /* Ask the user for credentials */
    if (!ReadString(IDS_ASKFORUSER, UserName, _countof(UserName), TRUE))
        return WLX_SAS_ACTION_NONE;
    if (!ReadString(IDS_ASKFORPASSWORD, Password, _countof(Password), FALSE))
        return WLX_SAS_ACTION_NONE;

    Status = DoLoginTasks(pgContext, UserName, NULL, Password, &SubStatus);
    if (Status == STATUS_SUCCESS)
    {
        if (CreateProfile(pgContext, UserName, NULL, Password))
            return WLX_SAS_ACTION_LOGON;
    }

    return WLX_SAS_ACTION_NONE;
}