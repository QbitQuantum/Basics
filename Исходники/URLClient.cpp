bool CUrlClient::SendHttpBlockRequests()
{
	USES_CONVERSION;
	m_dwLastBlockReceived = ::GetTickCount();
	if (reqfile == NULL)
		throw CString(_T("Failed to send block requests - No 'reqfile' attached"));

	CreateBlockRequests(PARTSIZE / EMBLOCKSIZE);
	if (m_PendingBlocks_list.IsEmpty()){
//==> Extended Failed/Success Statistic by NetF [shadow2004]
#ifdef FSSTATS
		SetDownloadState(DS_NONEEDEDPARTS, REASON_NoNeededParts);
#else
		SetDownloadState(DS_NONEEDEDPARTS);
#endif
//<== Extended Failed/Success Statistic by NetF [shadow2004]
        SwapToAnotherFile(_T("A4AF for NNP file. UrlClient::SendHttpBlockRequests()"), true, false, false, NULL, true, true);
		return false;
	}
	
	POSITION pos = m_PendingBlocks_list.GetHeadPosition();
	Pending_Block_Struct* pending = m_PendingBlocks_list.GetNext(pos);
	m_uReqStart = pending->block->StartOffset;
	m_uReqEnd = pending->block->EndOffset;
	bool bMergeBlocks = true;
	while (pos)
	{
		POSITION posLast = pos;
		pending = m_PendingBlocks_list.GetNext(pos);
		if (bMergeBlocks && pending->block->StartOffset == m_uReqEnd + 1)
			m_uReqEnd = pending->block->EndOffset;
		else
		{
			bMergeBlocks = false;
			reqfile->RemoveBlockFromList(pending->block->StartOffset, pending->block->EndOffset);
			delete pending->block;
			delete pending;
			m_PendingBlocks_list.RemoveAt(posLast);
		}
	}

	m_nUrlStartPos = m_uReqStart;

	CStringA strHttpRequest;
	strHttpRequest.AppendFormat("GET %s HTTP/1.0\r\n", m_strUrlPath);
	strHttpRequest.AppendFormat("Accept: */*\r\n");
	strHttpRequest.AppendFormat("Range: bytes=%u-%u\r\n", m_uReqStart, m_uReqEnd);
	strHttpRequest.AppendFormat("Connection: Keep-Alive\r\n");
	strHttpRequest.AppendFormat("Host: %s\r\n", T2CA(m_strHost));
	strHttpRequest.AppendFormat("\r\n");

	if (thePrefs.GetDebugClientTCPLevel() > 0)
		Debug(_T("Sending HTTP request:\n%hs"), strHttpRequest);
	CRawPacket* pHttpPacket = new CRawPacket(strHttpRequest);
	theStats.AddUpDataOverheadFileRequest(pHttpPacket->size);
	socket->SendPacket(pHttpPacket);
	STATIC_DOWNCAST(CHttpClientDownSocket, socket)->SetHttpState(HttpStateRecvExpected);
	return true;
}