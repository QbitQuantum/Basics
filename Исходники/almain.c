STATIC
NET_API_STATUS
AlUpdateStatus(
    VOID
    )
/*++

Routine Description:

    This routine updates the Alerter service status with the Service
    Controller.

Arguments:

    None.

Return Value:

    NET_API_STATUS - NERR_Success or reason for failure.

--*/
{
    NET_API_STATUS status = NERR_Success;


    if (AlGlobalData.StatusHandle == (SERVICE_STATUS_HANDLE) NULL) {
        NetpKdPrint((
            "[Alerter] Cannot call SetServiceStatus, no status handle.\n"
            ));

        return ERROR_INVALID_HANDLE;
    }

    if (! SetServiceStatus(AlGlobalData.StatusHandle, &AlGlobalData.Status)) {

        status = GetLastError();

        IF_DEBUG(MAIN) {
            NetpKdPrint(("[Alerter] SetServiceStatus error %lu\n", status));
        }
    }