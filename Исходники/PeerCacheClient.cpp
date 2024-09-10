UINT CUpDownClient::ProcessPeerCacheUpHttpRequest(const CStringAArray& astrHeaders)
{
	ASSERT( m_ePeerCacheUpState == PCUS_WAIT_CACHE_REPLY );

	if (astrHeaders.GetCount() == 0)
		return HTTP_STATUS_BAD_REQUEST;

	const CStringA& rstrHdr = astrHeaders.GetAt(0);
	char szUrl[1024];
	UINT uHttpMajVer, uHttpMinVer;
	if (sscanf(rstrHdr, "GET %1023s HTTP/%u.%u", szUrl, &uHttpMajVer, &uHttpMinVer) != 3){
		DebugHttpHeaders(astrHeaders);
		return HTTP_STATUS_BAD_REQUEST;
	}
	if (uHttpMajVer != 1 || (uHttpMinVer != 0 && uHttpMinVer != 1)){
		DebugHttpHeaders(astrHeaders);
		return HTTP_STATUS_BAD_REQUEST;
	}

	char szFileHash[33];
	if (sscanf(szUrl, "/.ed2khash=%32s", szFileHash) != 1){
		DebugHttpHeaders(astrHeaders);
		return HTTP_STATUS_BAD_REQUEST;
	}
	uchar aucUploadFileID[16];
	if (!strmd4(szFileHash, aucUploadFileID)){
		DebugHttpHeaders(astrHeaders);
		return HTTP_STATUS_BAD_REQUEST;
	}

	CKnownFile* pUploadFile = theApp.sharedfiles->GetFileByID(aucUploadFileID);
	if (pUploadFile == NULL){
		DebugHttpHeaders(astrHeaders);
		return HTTP_STATUS_NOT_FOUND;
	}

	bool bValidRange = false;
	uint64 ui64RangeStart = 0;
	uint64 ui64RangeEnd = 0;
	DWORD dwPushID = 0;
	for (int i = 1; i < astrHeaders.GetCount(); i++)
	{
		const CStringA& rstrHdr = astrHeaders.GetAt(i);
		if (strnicmp(rstrHdr, "Range:", 6) == 0)
		{
			int iParams;
			if (   (iParams = sscanf((LPCSTR)rstrHdr+6," bytes = %I64u - %I64u", &ui64RangeStart, &ui64RangeEnd)) != 2
				&& (iParams = sscanf((LPCSTR)rstrHdr+6," bytes = %I64u -", &ui64RangeStart)) != 1){
				DebugHttpHeaders(astrHeaders);
				TRACE("*** Unexpected HTTP %hs\n", rstrHdr);
				return HTTP_STATUS_BAD_REQUEST;
			}
			if (iParams == 1)
				ui64RangeEnd = pUploadFile->GetFileSize() - (uint64)1;

			if (ui64RangeEnd < ui64RangeStart){
				DebugHttpHeaders(astrHeaders);
				TRACE("*** Unexpected HTTP %hs\n", rstrHdr);
				return HTTP_STATUS_INV_RANGE;
			}

			bValidRange = true;
		}
		else if (strnicmp(rstrHdr, "X-ED2K-PushId:", 14) == 0)
		{
			if (sscanf((LPCSTR)rstrHdr+14, "%u", &dwPushID) != 1){
				DebugHttpHeaders(astrHeaders);
				TRACE("*** Unexpected HTTP %hs\n", rstrHdr);
				return HTTP_STATUS_BAD_REQUEST;
			}
		}
	}

	if (!bValidRange){
		DebugHttpHeaders(astrHeaders);
		return HTTP_STATUS_LENGTH_REQUIRED;
	}

	m_uPeerCacheUploadPushId = dwPushID;

	//PC-TODO: Where does this flag need to be cleared again? 
	// When client is removed from uploading list?
	// When client is allowed to send more block requests?
	
	// everything is setup for uploading with PeerCache.
	SetPeerCacheUpState(PCUS_UPLOADING);

	Requested_Block_Struct* reqblock = new Requested_Block_Struct;
	reqblock->StartOffset = ui64RangeStart;
	reqblock->EndOffset = ui64RangeEnd + 1;
	md4cpy(reqblock->FileID, aucUploadFileID);
	reqblock->transferred = 0;
	AddReqBlock(reqblock);

	return HTTP_STATUS_OK;
}