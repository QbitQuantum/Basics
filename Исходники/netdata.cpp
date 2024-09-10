int CNetData::AddString(const char *pszString, int iSize)
{
	int iLen = Strnlen(pszString, iSize-1);

	if(m_iPos + (int)sizeof(unsigned short) + iLen > m_iSize)
		return -1;

	if(-1 == AddWord(iLen))
		return -1;

	memcpy(m_pBuf + m_iPos, pszString, iLen);
	m_iPos += iLen;

	return m_iPos;
}