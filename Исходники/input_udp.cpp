void CInputUDP::Handshake(LPDESC pDesc, const char * c_pData)
{
	TPacketCGHandshake * pInfo = (TPacketCGHandshake *) c_pData;

	if (pDesc->GetHandshake() == pInfo->dwHandshake)
	{
		sys_log(0, "UDP: Grant %s:%d", inet_ntoa(m_SockAddr.sin_addr), m_SockAddr.sin_port);
		pDesc->UDPGrant(m_SockAddr);
		return;
	}
	else
		sys_log(0, "UDP: Handshake differs %s", pDesc->GetHostName());
}