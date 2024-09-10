lwres_result_t
lwres_conf_parse(lwres_context_t *ctx, const char *filename) {
	lwres_result_t ret;
	lwres_conf_t *confdata;
	FIXED_INFO * FixedInfo;
	ULONG    BufLen = sizeof(FIXED_INFO);
	DWORD    dwRetVal;
	IP_ADDR_STRING *pIPAddr;

	REQUIRE(ctx != NULL);
	confdata = &ctx->confdata;
	REQUIRE(confdata != NULL);

	/* Use the resolver if there is one */
	ret = generic_lwres_conf_parse(ctx, filename);
	if ((ret != LWRES_R_NOTFOUND && ret != LWRES_R_SUCCESS) ||
		(ret == LWRES_R_SUCCESS && confdata->nsnext > 0))
		return (ret);

	/*
	 * We didn't get any nameservers so we need to do this ourselves
	 */
	FixedInfo = (FIXED_INFO *) GlobalAlloc(GPTR, BufLen);
	dwRetVal = GetNetworkParams(FixedInfo, &BufLen);
	if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
		GlobalFree(FixedInfo);
		FixedInfo = GlobalAlloc(GPTR, BufLen);
		dwRetVal = GetNetworkParams(FixedInfo, &BufLen);
	}
	if (dwRetVal != ERROR_SUCCESS) {
		GlobalFree(FixedInfo);
		return (LWRES_R_FAILURE);
	}

	/* Get the search list from the registry */
	get_win32_searchlist(ctx);

	/* Use only if there is no search list */
	if (confdata->searchnxt == 0 && strlen(FixedInfo->DomainName) > 0) {
		confdata->domainname = lwres_strdup(ctx, FixedInfo->DomainName);
		if (confdata->domainname == NULL) {
			GlobalFree(FixedInfo);
			return (LWRES_R_FAILURE);
		}
	} else
		confdata->domainname = NULL;

	/* Get the list of nameservers */
	pIPAddr = &FixedInfo->DnsServerList;
	while (pIPAddr) {
		if (confdata->nsnext >= LWRES_CONFMAXNAMESERVERS)
			break;

		ret = lwres_create_addr(pIPAddr->IpAddress.String,
				&confdata->nameservers[confdata->nsnext++], 1);
		if (ret != LWRES_R_SUCCESS) {
			GlobalFree(FixedInfo);
			return (ret);
		}
		pIPAddr = pIPAddr ->Next;
	}

	GlobalFree(FixedInfo);
	return (LWRES_R_SUCCESS);
}