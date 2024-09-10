static BOOL
IsDeviceStarted(
    IN DEVINST DevInst,
    IN HMACHINE hMachine,
    OUT BOOL *IsEnabled)
{
    CONFIGRET cr;
    ULONG Status, ProblemNumber;
    BOOL Ret = FALSE;

    cr = CM_Get_DevNode_Status_Ex(
        &Status,
        &ProblemNumber,
        DevInst,
        0,
        hMachine);
    if (cr == CR_SUCCESS)
    {
        *IsEnabled = ((Status & DN_STARTED) != 0);
    Ret = TRUE;
    }

    return Ret;
}