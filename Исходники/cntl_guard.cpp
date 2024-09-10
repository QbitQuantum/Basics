void CNTL_shutdown_service(const TEXT* message)
{
/**************************************
 *
 *	C N T L _ s h u t d o w n _ s e r v i c e
 *
 **************************************
 *
 * Functional description
 *
 **************************************/
	const char* strings[2];
	char buffer[BUFFER_SMALL];

	sprintf(buffer, "%s error: %lu", service_name->c_str(), GetLastError());

	HANDLE event_source = RegisterEventSource(NULL, service_name->c_str());
	if (event_source)
	{
		strings[0] = buffer;
		strings[1] = message;
		ReportEvent(event_source, EVENTLOG_ERROR_TYPE, 0, 0, NULL, 2, 0, strings, NULL);
		DeregisterEventSource(event_source);
	}

	if (stop_event_handle)
		SetEvent(stop_event_handle);
}