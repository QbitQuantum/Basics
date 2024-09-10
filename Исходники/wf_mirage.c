BOOL wf_mirror_driver_cleanup(wfInfo* wfi)
{
	int status;

	status = ExtEscape(wfi->driverDC, dmf_esc_usm_pipe_unmap, sizeof(GETCHANGESBUF), (LPSTR) wfi->changeBuffer, 0, 0);
	
	if (status <= 0)
	{
		WLog_ERR(TAG, "Failed to unmap shared memory from the driver! code %d", status);
	}

	if (wfi->driverDC != NULL)
	{
		status = DeleteDC(wfi->driverDC);

		if (status == 0)
		{
			WLog_ERR(TAG, "Failed to release DC!"));
		}