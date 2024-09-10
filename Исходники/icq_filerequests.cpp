void CIcqProto::handleFileAck(PBYTE buf, WORD wLen, DWORD dwUin, DWORD dwCookie, WORD wStatus, char* pszText)
{
	char* pszFileName = NULL;
	DWORD dwFileSize;
	MCONTACT hCookieContact;
	WORD wPort;
	WORD wFilenameLength;
	filetransfer* ft;

	// Find the filetransfer that belongs to this response
	if (!FindCookie(dwCookie, &hCookieContact, (void**)&ft)) {
		NetLog_Direct("Error: Received unexpected file transfer request response");
		return;
	}

	FreeCookie(dwCookie);

	if (hCookieContact != HContactFromUIN(dwUin, NULL)) {
		NetLog_Direct("Error: UINs do not match in file transfer request response");
		return;
	}

	// If status != 0, a request has been denied
	if (wStatus != 0) {
		NetLog_Direct("File transfer denied by %u.", dwUin);
		ProtoBroadcastAck(ft->hContact, ACKTYPE_FILE, ACKRESULT_DENIED, (HANDLE)ft, 0);

		FreeCookie(dwCookie);

		return;
	}

	if (wLen < 6) { // sanity check
		NetLog_Direct("Ignoring malformed file transfer request response");
		return;
	}

	// Port to connect to
	unpackWord(&buf, &wPort);
	ft->dwRemotePort = wPort;
	wLen -= 2;

	// Unknown
	buf += 2;
	wLen -= 2;

	// Filename
	unpackLEWord(&buf, &wFilenameLength);
	if (wFilenameLength > 0) {
		if (wFilenameLength > wLen - 2)
			wFilenameLength = wLen - 2;
		pszFileName = (char*)_alloca(wFilenameLength + 1);
		unpackString(&buf, pszFileName, wFilenameLength);
		pszFileName[wFilenameLength] = '\0';
	}
	wLen = wLen - 2 - wFilenameLength;

	if (wLen >= 4) { // Total filesize
		unpackLEDWord(&buf, &dwFileSize);
		wLen -= 4;
	}
	else
		dwFileSize = 0;

	NetLog_Direct("File transfer ack from %u, port %u, name %s, size %u", dwUin, ft->dwRemotePort, pszFileName, dwFileSize);

	ProtoBroadcastAck(ft->hContact, ACKTYPE_FILE, ACKRESULT_CONNECTING, (HANDLE)ft, 0);

	OpenDirectConnection(ft->hContact, DIRECTCONN_FILE, ft);
}