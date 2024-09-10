bool PCSCReader::open(
	void)
{
	// No valid context so we should leave ...
	if (0x00 == m_hScardContext)
		return false;

	long retValue = SCARD_S_SUCCESS;
	retValue = SCardReconnect(m_hCard, SCARD_SHARE_SHARED, SCARD_PROTOCOL_ANY,
							  SCARD_LEAVE_CARD, &m_dwProtocol);
#if !defined(__APPLE__)
	BYTE atr[512];
	DWORD len = sizeof(atr);
	SCardGetAttrib(m_hCard, SCARD_ATTR_ATR_STRING, (LPBYTE) &atr, &len);
#else
	unsigned char atr[512];
	uint32_t len = sizeof(atr);
	char szReader[128];
	uint32_t cch = 128;
	uint32_t dwState;
	uint32_t dwProtocol;
	SCardStatus(m_hCard, szReader, &cch, &dwState, &dwProtocol, (unsigned char *)&atr, &len);
#endif
	return true;
}