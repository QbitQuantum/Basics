BOOLEAN
EnableUserModePnpManager(VOID)
{
    LARGE_INTEGER Timeout;

    /* Start the PnP thread */
    if (hPnpThread != NULL)
        NtResumeThread(hPnpThread, NULL);

    /*
     * Wait a little bit so that we get a chance to have some events being
     * queued by the time the device-installation thread becomes resumed.
     */
    Timeout.QuadPart = -10000000LL; /* Wait for 1 second */
    NtWaitForSingleObject(hDeviceInstallListNotEmpty, FALSE, &Timeout);

    /* Start the device installation thread */
    if (hDeviceInstallThread != NULL)
        NtResumeThread(hDeviceInstallThread, NULL);

    return TRUE;
}