static BOOL GetNetworkServersEnum(StringTimeNode** head, NETRESOURCE *nr)
{
	HANDLE hEnum;
	DWORD cbBuffer = 16384;
	NETRESOURCE *nrLocal;
	DWORD dwResultEnum;
	DWORD cEntries = (DWORD)-1;
	DWORD i;

	DWORD dwResult = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY,
									RESOURCEUSAGE_CONTAINER, nr, &hEnum);

	if (dwResult != NO_ERROR)
		return FALSE;

	nrLocal = (LPNETRESOURCE) GlobalAlloc(GPTR, cbBuffer);
	if (!nrLocal)
		return FALSE;

	for(;;) {
		ZeroMemory(nrLocal, cbBuffer);
		dwResultEnum = WNetEnumResource(hEnum, &cEntries, nrLocal, &cbBuffer);
		if (dwResultEnum != NO_ERROR)
			break;

		for (i = 0; i < cEntries; i++) {
			AddToListIfServer(head, &nrLocal[i]);
			if (RESOURCEUSAGE_CONTAINER == (nrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER)) {
				GetNetworkServersEnum(head, &nrLocal[i]);
			}
		}
	}

	GlobalFree((HGLOBAL) nrLocal);
	dwResult = WNetCloseEnum(hEnum);

	if (dwResult != NO_ERROR)
		return FALSE;

	return TRUE;
}