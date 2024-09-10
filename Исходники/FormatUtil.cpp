BOOL CFormatUtil::SetFormat(char *pcFormat)
{
	if (NULL == pcFormat)
		return FALSE;

	m_iLength = strnlen_s(pcFormat, MAX_PATH);
	m_pcFormat = new char[m_iLength + 1];
	memcpy(m_pcFormat, pcFormat, m_iLength);
	m_pcFormat[m_iLength] = '\0';

	FormatPaser();

	return TRUE;
}