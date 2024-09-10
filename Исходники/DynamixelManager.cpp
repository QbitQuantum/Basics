uint8_t DynamixelManager::read(uint8_t *data, size_t len) {
	while (m_mutex)
		;
	acquireMutex();
	uint8_t ret = m_serial->readBytes(reinterpret_cast<char*>(data), len);
	releaseMutex();
	return ret;
}