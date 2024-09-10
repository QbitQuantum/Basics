void CTcpAgent::CompressFreeSocket(size_t size, BOOL bForce)
{
	CCriSecLock locallock(m_csFreeSocket);

	DWORD now = ::TimeGetTime();

	while(m_lsFreeSocket.size() > size)
	{
		TSocketObj* pSocketObj = m_lsFreeSocket.front();

		if(bForce || (now - pSocketObj->freeTime) >= m_dwFreeSocketObjLockTime)
		{
			m_lsFreeSocket.pop_front();
			DeleteSocketObj(pSocketObj);
		}
		else
			break;
	}
}