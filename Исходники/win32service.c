/* {{{ proto bool win32_set_service_status(int status, [int checkpoint])
   Update the service status */
static PHP_FUNCTION(win32_set_service_status)
{
	long status;
	long checkpoint = 0;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &status, &checkpoint)) {
		RETURN_FALSE;
	}

	SVCG(st.dwCurrentState) = status;
	/* CheckPoints are only valid for the SERVICE_*_PENDING statuses. */
	if ((status == SERVICE_CONTINUE_PENDING) || (status == SERVICE_PAUSE_PENDING) || (status == SERVICE_START_PENDING) || (status == SERVICE_STOP_PENDING)) {
		SVCG(st.dwCheckPoint) = checkpoint;
	}

	if (!SetServiceStatus(SVCG(sh), &SVCG(st))) {
		RETURN_LONG(GetLastError())
	} else {
		RETURN_TRUE;
	}
}