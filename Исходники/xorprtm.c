DWORD
CE_Cleanup(PCONFIGURATION_ENTRY pce)
{
    DWORD dwErr = NO_ERROR;
    int i;

    if (pce->hRtmNotificationHandle) {
        dwErr = RtmDeregisterFromChangeNotification(
            pce->hRtmHandle,
            pce->hRtmNotificationHandle);
        if (dwErr != NO_ERROR)
            TRACE1(CONFIGURATION,
                   "Error %u deregistering for change from RTM", dwErr);
    }
    pce->hRtmNotificationHandle = NULL;

    if (pce->hRtmHandle) {
        dwErr = RtmDeregisterEntity(pce->hRtmHandle);

        if (dwErr != NO_ERROR)
            TRACE1(CONFIGURATION,
                   "Error %u deregistering from RTM", dwErr);
    }
    pce->hRtmHandle             = NULL;

    for (i = 0; i < PIPE_INSTANCES; i++) {
	if (pce->pipes[i]) {
	    pipe_destroy(pce->pipes[i]);
	    pce->pipes[i] = NULL;
	}
    }

    if (pce->hMprConfig != NULL) {
	MprConfigServerDisconnect(pce->hMprConfig);
    }
    pce->hMprConfig = NULL;

    pce->iscStatus = XORPRTM_STATUS_STOPPED;

    return NO_ERROR;
}