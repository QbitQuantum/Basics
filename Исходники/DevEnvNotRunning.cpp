extern "C" UINT __stdcall DevEnvNotRunning(MSIHANDLE hInstall)
{
    UINT errCode;
    DevEnvStatus status;
    bool cancelled = false;
    MSIHANDLE hMessage = NULL;

    status = GetDevEnvStatus(hInstall);
    while (!cancelled && status == StatusRunning)
    {
        if (hMessage == NULL)
        {
            hMessage = MsiCreateRecord(2);
        }

        MsiRecordClearData(hMessage);
        MsiRecordSetInteger(hMessage, 1, messageIdCloseDevEnv);

        int result = MsiProcessMessage(
            hInstall,
            static_cast<INSTALLMESSAGE>(INSTALLMESSAGE_WARNING | MB_RETRYCANCEL),
            hMessage);
        cancelled = (result == IDCANCEL);

        if (!cancelled)
        {
            status = GetDevEnvStatus(hInstall);
        }
    }

    switch (status)
    {
    case StatusNotRunning:
        errCode = ERROR_SUCCESS;
        break;

    case StatusRunning:
        errCode = ERROR_INSTALL_USEREXIT;
        break;

    case StatusError:
    default:
        Log(LogError, hInstall, L"Failed to search for running DevEnv.exe process.");
        errCode = ERROR_INSTALL_FAILURE;
        break;
    }

    if (hMessage != NULL) MsiCloseHandle(hMessage);

    return errCode;
}