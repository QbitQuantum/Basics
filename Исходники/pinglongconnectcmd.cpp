//TPingSynCmd////////////////////////////////////////////////////////////////////////
int TPingSynCmd::Decode(CBufMgr &bufMgr)
{
	if (bufMgr.GetString (m_PeerInfo.strPeerId) != 0)
	{
		WRITE_TRACE("Ping, Decode for peerid FAILED!!");
		return -1;
	}
	if (m_PeerInfo.strPeerId.length() != COMMON_PEERID_LEN)
	{
		WRITE_TRACE("Ping, peerid len is invalide, %d", m_PeerInfo.strPeerId.length ());
		return -2;
	}
	if (bufMgr.GetInt(m_PeerInfo.nInternalIp) != 0)
	{
		WRITE_TRACE("Ping, Decode for nInternalIp FAILED!!");
		return -1;
	}
// 	if (bufMgr.GetInt(m_PeerInfo.nSubMask) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nSubMask FAILED!!");
// 		return -1;
// 	}
	if (bufMgr.GetShort(m_PeerInfo.nTcpPort) != 0)
	{
		WRITE_TRACE("Ping, Decode for nTcpPort FAILED!!");
		return -1;
	}
// 	if (bufMgr.GetInt(m_PeerInfo.nProductFlag) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nProductFlag FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetInt(m_PeerInfo.nProductReleaseId) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nProductReleaseId FAILED!!");
// 		return -1;
// 	}
// 	int nSuperNodeNum = 0;
// 	if (bufMgr.GetInt(nSuperNodeNum) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nSuperNodeNum FAILED!!");
// 		return -1;
// 	}
// 	else
// 	{
// 		if (nSuperNodeNum < 0)
// 		{
// 			WRITE_TRACE("Ping, Decode for nSuperNodeNum(< 0) FAILED!!");
// 			return -2;
// 		}
// 	}
// 	m_PeerInfo.vecSuperNode.clear();
// 	string strSuperNodePeerId;
// 	for (int iA = 0; iA < nSuperNodeNum; iA ++)
// 	{
// 		if (bufMgr.GetString(strSuperNodePeerId) != 0)
// 		{
// 			WRITE_TRACE("Ping, Decode for nSuperNodeNum FAILED!!");
// 			return -1;
// 		}
// 		if (strSuperNodePeerId.length() != COMMON_PEERID_LEN)
// 		{
// 			WRITE_TRACE("Ping, supernode peerid len is invalide, %d", strSuperNodePeerId.length ());
// 			return -2;
// 		}
// 		else
// 		{
// 			m_PeerInfo.vecSuperNode.push_back(strSuperNodePeerId);
// 		}
// 	}
// 	if (bufMgr.GetInt(m_PeerInfo.nNatType) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nNatType FAILED!!");
// 		return -1;
// 	}
	if (bufMgr.GetInt(m_PeerInfo.nUpnpMapdeIp) != 0)
	{
		WRITE_TRACE("Ping, Decode for nUpnpMapdeIp FAILED!!");
		return -1;
	}
	if (bufMgr.GetShort(m_PeerInfo.nUpnpMapedPort) != 0)
	{
		WRITE_TRACE("Ping, Decode for nUpnpMapedPort FAILED!!");
		return -1;
	}
// 	if (bufMgr.GetInt(m_PeerInfo.nOnlineTime) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nOnlineTime FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetInt(m_PeerInfo.nDownloadBytes) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nDownloadBytes FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetInt(m_PeerInfo.nUploadBytes) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nUploadBytes FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetShort(m_PeerInfo.nCurUploadResource) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nCurUploadResource FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetChar(m_PeerInfo.nCurUploadTaskNum) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nCurUploadTaskNum FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetChar(m_PeerInfo.nCurDownloadTaskNum) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nCurDownloadTaskNum FAILED!!");
// 		return -1;
// 	}
	if (bufMgr.GetChar((char&)m_PeerInfo.nCurUploadPipeNum) != 0)
	{
		WRITE_TRACE("Ping, Decode for nCurUploadPipeNum FAILED!!");
		return -1;
	}
	if (bufMgr.GetChar(m_PeerInfo.nCurUploadPipeStatus) != 0)
	{
		WRITE_TRACE("Ping, Decode for nCurUploadPipeStatus FAILED!!");
		return -1;
	}
// 	if (bufMgr.GetShort(m_PeerInfo.nCurDownloadSpeed) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nCurUploadPipeNum FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetShort(m_PeerInfo.nCurUploadSpeed) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nCurUploadSpeed FAILED!!");
// 		return -1;
// 	}
	if (bufMgr.GetShort(m_PeerInfo.nMaxDownloadSpeed) != 0)
	{
		WRITE_TRACE("Ping, Decode for nMaxDownloadSpeed FAILED!!");
		return -1;
	}
	if (bufMgr.GetShort(m_PeerInfo.nMaxUploadSpeed) != 0)
	{
		WRITE_TRACE("Ping, Decode for nMaxDownloadSpeed FAILED!!");
		return -1;
	}
// 	if (bufMgr.GetShort(m_PeerInfo.nSmartUploadSpeedLimit) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nMaxDownloadSpeed FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetShort(m_PeerInfo.nUserUploadSpeedLimit) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nUserUploadSpeedLimit FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetShort(m_PeerInfo.nDownloadSpeedLimit) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nDownloadSpeedLimit FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetShort(m_PeerInfo.nPeerStatus) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nDownloadSpeedLimit FAILED!!");
// 		return -1;
// 	}
	if (bufMgr.GetShort(m_PeerInfo.nLocalBindPort) != 0)
	{
		WRITE_TRACE("Ping, Decode for nLocalBindPort FAILED!!");
		return -1;
	}
// 	if (bufMgr.GetShort(m_PeerInfo.nExternalNeighbor) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nExternalNeighbor FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetShort(m_PeerInfo.nInternalNeighbor) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for nInternalNeighbor FAILED!!");
// 		return -1;
// 	}
// 	if (bufMgr.GetString(m_PeerInfo.strPartnerPeerId) != 0)
// 	{
// 		WRITE_TRACE("Ping, Decode for strPartnerPeerId FAILED!!");
// 		return -1;
// 	}
	
	//////////////////////////////////////////////////////////////////////////
	if (bufMgr.GetInt(m_PeerInfo.nExternalIp) != 0)
	{
		WRITE_TRACE("Ping, Decode for nExternalIp FAILED!!");
		return -1;
	}
	if (bufMgr.GetShort(m_PeerInfo.nExternalPort) != 0)
	{
		WRITE_TRACE("Ping, Decode for nExternalPort FAILED!!");
		return -1;
	}	
	return 0;
}