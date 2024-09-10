/* Some code stolen from BlueCove. */
static int findHaggleService(BT_ADDR *pb)
{
	BTHNS_RESTRICTIONBLOB queryservice;
	unsigned char uuid[] = HAGGLE_BLUETOOTH_SDP_UUID;
	BLOB blob;
	WSAQUERYSET queryset;
	SOCKADDR_BTH sa;
	HANDLE hLookupSearchServices;
	int found = 0;

	memset(&queryservice, 0, sizeof(queryservice));

	queryservice.type = SDP_SERVICE_SEARCH_REQUEST;

	convertUUIDBytesToGUID((char *) uuid, &queryservice.uuids[0].u.uuid128);

	//UUID is full 128 bits
	queryservice.uuids[0].uuidType = SDP_ST_UUID128;

	// build BLOB pointing to service query

	blob.cbSize = sizeof(queryservice);
	blob.pBlobData = (BYTE *) & queryservice;

	// build query
	memset(&queryset, 0, sizeof(WSAQUERYSET));

	queryset.dwSize = sizeof(WSAQUERYSET);
	queryset.dwNameSpace = NS_BTH;
	queryset.lpBlob = &blob;


	// Build address
	memset(&sa, 0, sizeof(sa));
	sa.addressFamily = AF_BT;
	sa.btAddr = *pb;
	CSADDR_INFO csai;
	memset(&csai, 0, sizeof(csai));
	csai.RemoteAddr.lpSockaddr = (sockaddr *) &sa;
	csai.RemoteAddr.iSockaddrLength = sizeof(sa);
	queryset.lpcsaBuffer = &csai;

	// begin query

	if (WSALookupServiceBegin(&queryset, 0, &hLookupSearchServices)) {
		int last_error = WSAGetLastError();
		CM_DBG("WSALookupServiceBegin error [%s]", StrError(last_error));
		return -1;
	}
	// fetch results
	int bufSize = 0x2000;
	void *buf = malloc(bufSize);

	if (buf == NULL) {
		WSALookupServiceEnd(hLookupSearchServices);
		return NULL;
	}
	memset(buf, 0, bufSize);

	LPWSAQUERYSET pwsaResults = (LPWSAQUERYSET) buf;
	pwsaResults->dwSize = sizeof(WSAQUERYSET);
	pwsaResults->dwNameSpace = NS_BTH;
	pwsaResults->lpBlob = NULL;

	DWORD size = bufSize;

	if (WSALookupServiceNext(hLookupSearchServices, LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RETURN_ADDR, &size, pwsaResults)) {
		int last_error = WSAGetLastError();

		switch (last_error) {
		case WSANO_DATA:
			//HAGGLE_DBG("SDP: no data\n");
			found = -1;
			break;
		case WSA_E_NO_MORE:
			//HAGGLE_DBG("End of SDP list\n");
			break;
		case WSAENOTCONN:
			found = -1;
			HAGGLE_DBG("Could not connect to SDP service\n");
			break;
		case WSASERVICE_NOT_FOUND:
			found = 0;
			HAGGLE_DBG("SDP Service not found\n");
			break;
		default:
			CM_DBG("WSALookupServiceNext error [%s]\n", StrError(last_error));
			found = -1;
		}
	} else {
		unsigned long cChannel = 0;
		found = 1;
		HAGGLE_DBG("Found Haggle service\n");
		if (ERROR_SUCCESS == FindRFCOMMChannel(
			pwsaResults->lpBlob->pBlobData,
			pwsaResults->lpBlob->cbSize,
			&cChannel)) {
			HAGGLE_DBG("RFCOMM channel is %d\n", (int)cChannel);
			found = cChannel;
		}
	}
	WSALookupServiceEnd(hLookupSearchServices);
	free(buf);

	return found;
}