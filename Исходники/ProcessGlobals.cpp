void ProcessGlobals::cleanUp()
{

	// free any memory taken with service param config

	if (serviceParams != NULL)
	{
		delete serviceParams;
		serviceParams = NULL;
	}

	// release any handles that were obtained
	// (functions will set to null afterwards)

	deregisterEventSource(&hEventSource);
	closeEventHandle(&hWaitForStop);
	closeEventHandle(&hWaitForStart);

	// note that service status handle does not need to be closed
}