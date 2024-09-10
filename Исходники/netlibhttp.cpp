INT_PTR NetlibHttpTransaction(WPARAM wParam, LPARAM lParam)
{
	NetlibUser *nlu = (NetlibUser*)wParam;
	NETLIBHTTPREQUEST *nlhr = (NETLIBHTTPREQUEST*)lParam, *nlhrReply;

	if (GetNetlibHandleType(nlu) != NLH_USER || !(nlu->user.flags & NUF_OUTGOING) ||
		nlhr == NULL || nlhr->cbSize != sizeof(NETLIBHTTPREQUEST) ||
		nlhr->szUrl == NULL || nlhr->szUrl[0] == 0)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	if (nlhr->nlc != NULL && GetNetlibHandleType(nlhr->nlc) != NLH_CONNECTION)
		nlhr->nlc = NULL;

	NetlibConnection *nlc = NetlibHttpProcessUrl(nlhr, nlu, (NetlibConnection*)nlhr->nlc);
	if (nlc == NULL)
		return 0;

	NETLIBHTTPREQUEST nlhrSend;
	char szUserAgent[64];

	nlhrSend = *nlhr;
	nlhrSend.flags &= ~NLHRF_REMOVEHOST;
	nlhrSend.flags |= NLHRF_GENERATEHOST | NLHRF_SMARTREMOVEHOST | NLHRF_SMARTAUTHHEADER;

	bool doneUserAgentHeader = NetlibHttpFindHeader(nlhr, "User-Agent") != NULL;
	bool doneAcceptEncoding = NetlibHttpFindHeader(nlhr, "Accept-Encoding") != NULL;

	if (!doneUserAgentHeader || !doneAcceptEncoding) {
		nlhrSend.headers = (NETLIBHTTPHEADER*)mir_alloc(sizeof(NETLIBHTTPHEADER) * (nlhrSend.headersCount + 2));
		memcpy(nlhrSend.headers, nlhr->headers, sizeof(NETLIBHTTPHEADER) * nlhr->headersCount);
	}

	if (!doneUserAgentHeader) {
		nlhrSend.headers[nlhrSend.headersCount].szName = "User-Agent";
		nlhrSend.headers[nlhrSend.headersCount].szValue = szUserAgent;
		++nlhrSend.headersCount;

		char szMirandaVer[64];
		strncpy_s(szMirandaVer, MIRANDA_VERSION_STRING, _TRUNCATE);
		#if defined(_WIN64)
			strncat_s(szMirandaVer, " x64", _TRUNCATE);
		#endif

		char *pspace = strchr(szMirandaVer, ' ');
		if (pspace) {
			*pspace++ = '\0';
			mir_snprintf(szUserAgent, "Miranda/%s (%s)", szMirandaVer, pspace);
		}
		else mir_snprintf(szUserAgent, "Miranda/%s", szMirandaVer);
	}
	if (!doneAcceptEncoding) {
		nlhrSend.headers[nlhrSend.headersCount].szName = "Accept-Encoding";
		nlhrSend.headers[nlhrSend.headersCount].szValue = "deflate, gzip";
		++nlhrSend.headersCount;
	}
	if (NetlibHttpSendRequest((WPARAM)nlc, (LPARAM)&nlhrSend) == SOCKET_ERROR) {
		if (!doneUserAgentHeader || !doneAcceptEncoding) mir_free(nlhrSend.headers);
		nlhr->resultCode = nlhrSend.resultCode;
		NetlibCloseHandle((WPARAM)nlc, 0);
		return 0;
	}
	if (!doneUserAgentHeader || !doneAcceptEncoding)
		mir_free(nlhrSend.headers);

	DWORD dflags = (nlhr->flags & NLHRF_DUMPASTEXT ? MSG_DUMPASTEXT : 0) |
		(nlhr->flags & NLHRF_NODUMP ? MSG_NODUMP : (nlhr->flags & NLHRF_DUMPPROXY ? MSG_DUMPPROXY : 0)) |
		(nlhr->flags & NLHRF_NOPROXY ? MSG_RAW : 0);

	DWORD hflags =
		(nlhr->flags & NLHRF_NODUMP ? MSG_NODUMP : (nlhr->flags & NLHRF_DUMPPROXY ? MSG_DUMPPROXY : 0)) |
		(nlhr->flags & NLHRF_NOPROXY ? MSG_RAW : 0);

	if (nlhr->requestType == REQUEST_HEAD)
		nlhrReply = (NETLIBHTTPREQUEST*)NetlibHttpRecvHeaders((WPARAM)nlc, 0);
	else
		nlhrReply = NetlibHttpRecv(nlc, hflags, dflags);

	if (nlhrReply) {
		nlhrReply->szUrl = nlc->szNewUrl;
		nlc->szNewUrl = NULL;
	}

	if ((nlhr->flags & NLHRF_PERSISTENT) == 0 || nlhrReply == NULL) {
		NetlibCloseHandle((WPARAM)nlc, 0);
		if (nlhrReply)
			nlhrReply->nlc = NULL;
	}
	else nlhrReply->nlc = nlc;

	return (INT_PTR)nlhrReply;
}