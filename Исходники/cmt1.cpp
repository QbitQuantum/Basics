//////////////////////////////////////////////////////////////////////////////////////////
// Write data to the end of the file.
XsensResultValue Cmt1f::appendData(const uint32_t length, const void* data)
{
	if (!m_isOpen) return m_lastResult = XRV_NOFILEOPEN;
	if (m_readOnly) return m_lastResult = XRV_READONLY;

	if (m_reading || m_writePos != m_fileSize)
	{
		m_reading = false;
		FSEEK_R(0);
	}
	fwrite(data, 1, length, m_handle);
	m_writePos = FTELL();
	m_fileSize = m_writePos;

	return (m_lastResult = XRV_OK);
}