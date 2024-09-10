void WINAPI ServiceControlHandler(DWORD dwCtrlCode)
{
	switch(dwCtrlCode) {
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			lprintf(LOG_NOTICE,"Received termination control signal: %d", dwCtrlCode);
			svc_status.dwWaitHint=NTSVC_TIMEOUT_SHUTDOWN;
			svc_status.dwCurrentState=SERVICE_STOP_PENDING;
			SetServiceStatus(svc_status_handle, &svc_status);
			terminated=TRUE;
//			SetEvent(service_event);
			break;
		case SERVICE_CONTROL_INTERROGATE:
			lprintf(LOG_DEBUG,"Ignoring service control signal: SERVICE_CONTROL_INTERROGATE");
			break;
		default:
			lprintf(LOG_WARNING,"Received unsupported service control signal: %d", dwCtrlCode);
			break;
	}
}