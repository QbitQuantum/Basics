void CNetDDESvrApp::OnDDERequest(CNetDDESvrSocket& oConnection, CNetDDEPacket& oReqPacket)
{
	ASSERT(oReqPacket.DataType() == CNetDDEPacket::DDE_REQUEST);

	bool     bResult = false;

	HCONV	 hConv;
	uint32   nConvID;
	CString  strItem;
	uint32   nFormat;
	CBuffer  oBuffer;

	// Decode message.
	CMemStream oStream(oReqPacket.Buffer());

	oStream.Open();
	oStream.Seek(sizeof(CNetDDEPacket::Header));

	oStream.Read(&hConv, sizeof(hConv));
	oStream >> nConvID;
	oStream >> strItem;
	oStream >> nFormat;

	oStream.Close();

	if (App.m_bTraceRequests)
		App.Trace(TXT("DDE_REQUEST: %s %s"), strItem, CClipboard::FormatName(nFormat));

	try
	{
		// Locate the conversation.
		CDDECltConv* pConv = m_pDDEClient->FindConversation(hConv);

		if (pConv != NULL)
		{
			// Call DDE to make the request.
			CDDEData oData = pConv->Request(strItem, nFormat);

			oBuffer = oData.GetBuffer();

			bResult = true;
		}
	}
	catch (CDDEException& e)
	{
		App.Trace(TXT("DDE_ERROR: %s"), e.twhat());
	}

	// Create response message.
	CBuffer    oRspBuffer;
	CMemStream oRspStream(oRspBuffer);

	oRspStream.Create();

	oRspStream << bResult;
	oRspStream << oBuffer;

	oRspStream.Close();

	// Send response message.
	CNetDDEPacket oRspPacket(CNetDDEPacket::DDE_REQUEST, oReqPacket.PacketID(), oRspBuffer);

	oConnection.SendPacket(oRspPacket);

	// Update stats.
	++m_nPktsSent;
}