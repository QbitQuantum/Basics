void __cdecl CMsnProto::MsnFileAckThread(void* arg)
{
	filetransfer* ft = (filetransfer*)arg;

	TCHAR filefull[MAX_PATH];
	mir_sntprintf(filefull, _T("%s\\%s"), ft->std.tszWorkingDir, ft->std.tszCurrentFile);
	replaceStrT(ft->std.tszCurrentFile, filefull);

	ResetEvent(ft->hResumeEvt);
	if (ProtoBroadcastAck(ft->std.hContact, ACKTYPE_FILE, ACKRESULT_FILERESUME, ft, (LPARAM)&ft->std))
		WaitForSingleObject(ft->hResumeEvt, INFINITE);

	ft->create();

#ifdef OBSOLETE
	if (ft->tType != SERVER_HTTP) {
		if (ft->p2p_appID != 0) {
			if (fcrt)
				p2p_sendFeedStart(ft);
			p2p_sendStatus(ft, fcrt ? 200 : 603);
		}
		else msnftp_sendAcceptReject(ft, fcrt);
	}
#endif

	ProtoBroadcastAck(ft->std.hContact, ACKTYPE_FILE, ACKRESULT_INITIALISING, ft, 0);

	if (ft->tType == SERVER_HTTP) {
		const char *pszSkypeToken;

		if (ft->fileId != -1 && (pszSkypeToken=authSkypeToken.Token())) {
			NETLIBHTTPHEADER nlbhHeaders[3] = { 0 };
			NETLIBHTTPREQUEST nlhr = { 0 }, *nlhrReply;
			char szRange[32];

			nlbhHeaders[0].szName = "User-Agent";		nlbhHeaders[0].szValue = (LPSTR)MSN_USER_AGENT;
			nlbhHeaders[1].szName = "Authorization";	nlbhHeaders[1].szValue = (char*)pszSkypeToken;
			nlhr.headersCount = 2;
			if (ft->std.currentFileProgress) {
				mir_snprintf(szRange, sizeof(szRange), "bytes=%I64d-", ft->std.currentFileProgress);
				nlbhHeaders[2].szName = "Range";
				nlbhHeaders[2].szValue = szRange;
				nlhr.headersCount++;
			}

			nlhr.cbSize = sizeof(nlhr);
			nlhr.requestType = REQUEST_GET;
			nlhr.flags = NLHRF_GENERATEHOST | NLHRF_SMARTREMOVEHOST | NLHRF_SMARTAUTHHEADER | NLHRF_HTTP11;
			nlhr.szUrl = ft->szInvcookie;
			nlhr.headers = (NETLIBHTTPHEADER*)&nlbhHeaders;

			NETLIBOPENCONNECTION nloc = { 0 };
			MyNetlibConnFromUrl(nlhr.szUrl, nloc);
			nloc.flags |= NLOCF_HTTP;
			if (nloc.flags & NLOCF_SSL) nlhr.flags |= NLHRF_SSL;
			HANDLE nlc = (HANDLE)CallService(MS_NETLIB_OPENCONNECTION, (WPARAM)m_hNetlibUser, (LPARAM)&nloc);

			if (nlc && CallService(MS_NETLIB_SENDHTTPREQUEST, (WPARAM)nlc, (LPARAM)&nlhr) != SOCKET_ERROR &&
				(nlhrReply = (NETLIBHTTPREQUEST*)CallService(MS_NETLIB_RECVHTTPHEADERS, (WPARAM)nlc, 0))) 
			{
					if (nlhrReply->resultCode == 200 || nlhrReply->resultCode == 206) {
						INT_PTR dw;
						char buf[1024];

						ProtoBroadcastAck(ft->std.hContact, ACKTYPE_FILE, ACKRESULT_CONNECTED, ft, 0);
						while (!ft->bCanceled && ft->std.currentFileProgress < ft->std.currentFileSize &&
							(dw = Netlib_Recv(nlc, buf, sizeof(buf), MSG_NODUMP))>0 && dw!=SOCKET_ERROR) 
						{
							_write(ft->fileId, buf, dw);
							ft->std.totalProgress += dw;
							ft->std.currentFileProgress += dw;
							ProtoBroadcastAck(ft->std.hContact, ACKTYPE_FILE, ACKRESULT_DATA, ft, (LPARAM)&ft->std);
						}
						if (ft->std.currentFileProgress == ft->std.currentFileSize) ft->std.currentFileNumber++;

					}
					CallService(MS_NETLIB_FREEHTTPREQUESTSTRUCT, 0, (LPARAM)nlhrReply);
			}
			Netlib_CloseHandle(nlc);
			mir_free((char*)nloc.szHost);
			if (ft->std.currentFileNumber >= ft->std.totalFiles) ft->complete();
		}
		delete ft;
	}
}