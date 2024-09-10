/* DG_CONTROL/DAT_IDENTITY/MSG_OPENDS */
TW_UINT16 TWAIN_OpenDS (pTW_IDENTITY pOrigin, TW_MEMREF pData)
{
	TW_UINT16 i = 0;
	pTW_IDENTITY pIdentity = (pTW_IDENTITY) pData;
	activeDS *newSource;
	const char *modname = NULL;
	HMODULE hmod;

	TRACE("DG_CONTROL/DAT_IDENTITY/MSG_OPENDS\n");
        TRACE("pIdentity is %s\n", pIdentity->ProductName);
	if (!DSM_initialized) {
		FIXME("seq error\n");
		DSM_twCC = TWCC_SEQERROR;
		return TWRC_FAILURE;
	}
	twain_autodetect();
	if (!nrdevices) {
		FIXME("no devs.\n");
		DSM_twCC = TWCC_NODS;
		return TWRC_FAILURE;
	}

	if (pIdentity->ProductName[0] != '\0') {
		/* Make sure the source to be opened exists in the device list */
		for (i = 0; i<nrdevices; i++)
			if (!strcmp (devices[i].identity.ProductName, pIdentity->ProductName))
				break;
		if (i == nrdevices)
			i = 0;
	} /* else use the first device */

	/* the source is found in the device list */
	newSource = HeapAlloc (GetProcessHeap(), 0, sizeof (activeDS));
	if (!newSource) {
		DSM_twCC = TWCC_LOWMEMORY;
		FIXME("Out of memory.\n");
		return TWRC_FAILURE;
	}
	hmod = LoadLibraryA(devices[i].modname);
	if (!hmod) {
		ERR("Failed to load TWAIN Source %s\n", modname);
		DSM_twCC = TWCC_OPERATIONERROR;
                HeapFree(GetProcessHeap(), 0, newSource);
		return TWRC_FAILURE;
	}
	newSource->hmod = hmod; 
	newSource->dsEntry = (DSENTRYPROC)GetProcAddress(hmod, "DS_Entry"); 
	if (TWRC_SUCCESS != newSource->dsEntry (pOrigin, DG_CONTROL, DAT_IDENTITY, MSG_OPENDS, pIdentity)) {
		DSM_twCC = TWCC_OPERATIONERROR;
                HeapFree(GetProcessHeap(), 0, newSource);
		return TWRC_FAILURE;
	}
	/* Assign name and id for the opened data source */
	pIdentity->Id = DSM_sourceId ++;
	/* add the data source to an internal active source list */
	newSource->next = activeSources;
	newSource->identity.Id = pIdentity->Id;
	strcpy (newSource->identity.ProductName, pIdentity->ProductName);
	activeSources = newSource;
	DSM_twCC = TWCC_SUCCESS;
	return TWRC_SUCCESS;
}