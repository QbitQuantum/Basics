LLUdpQWave::~LLUdpQWave()
{

	QOSRemoveSocketFromFlow(s_qosHandle, NULL, m_qos.handle, 0);

	HeapFree(GetProcessHeap(), 0, m_transmitEl);
	CloseHandle(m_sendOverlapped.hEvent);

	if (m_socketRx != -1)
		close(m_socketRx);
	if (m_socketTx != -1)
		close(m_socketTx);
	m_socketRx = m_socketTx = -1;
}