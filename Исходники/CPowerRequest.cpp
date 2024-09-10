CPowerRequest::~CPowerRequest() {
	if (m_Request != INVALID_HANDLE_VALUE) {
		CloseHandle(m_Request);
	} else {
		if (m_bDisplay || m_bSystem) SetThreadExecutionState(ES_CONTINUOUS);
	}
}