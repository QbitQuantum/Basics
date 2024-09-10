static DWORD WINAPI control_handler(DWORD control, DWORD event_type, void *event_data, void *context)
{
	switch(control) {
	case SERVICE_CONTROL_STOP:
		keep_running = false;
		ctx->abort();
		return NO_ERROR;
	case SERVICE_CONTROL_INTERROGATE:
		return NO_ERROR;
	}
	return ERROR_CALL_NOT_IMPLEMENTED;
}