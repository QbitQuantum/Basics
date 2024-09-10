static int smpd_build_spn_list()
{
    HRESULT hr;
    IDirectoryObject *pSCP = NULL;
    ADS_ATTR_INFO *pPropEntries = NULL;
    IDirectorySearch *pSearch = NULL;
    ADS_SEARCH_HANDLE hSearch = NULL;
    LPWSTR pszDN;                  /* distinguished name of SCP. */
    LPWSTR pszServiceDNSName;      /* service DNS name. */
    LPWSTR pszClass;               /* name of service class. */
    USHORT usPort;                 /* service port. */
    WCHAR pszSearchString[SMPD_MAX_NAME_LENGTH];
    char temp_str[SMPD_MAX_NAME_LENGTH];
    char temp_str2[SMPD_MAX_NAME_LENGTH];
    smpd_host_spn_node_t *iter;
    /* double t1, t2; */
    static int initialized = 0;

    if (initialized)
    {
	return SMPD_SUCCESS;
    }
    initialized = 1;

    /* t1 = PMPI_Wtime(); */

    CoInitialize(NULL);

    /* Get an IDirectorySearch pointer for the Global Catalog.  */
    hr = GetGCSearch(&pSearch);
    if (FAILED(hr) || pSearch == NULL) 
    {
	smpd_err_printf("GetGC failed 0x%x\n", hr);
	goto Cleanup;
    }

    /* Set up a deep search.
      Thousands of objects are not expected in this example, therefore
      query for 1000 rows per page.*/
    ADS_SEARCHPREF_INFO SearchPref[2];
    DWORD dwPref = sizeof(SearchPref)/sizeof(ADS_SEARCHPREF_INFO);
    SearchPref[0].dwSearchPref =    ADS_SEARCHPREF_SEARCH_SCOPE;
    SearchPref[0].vValue.dwType =   ADSTYPE_INTEGER;
    SearchPref[0].vValue.Integer =  ADS_SCOPE_SUBTREE;

    SearchPref[1].dwSearchPref =    ADS_SEARCHPREF_PAGESIZE;
    SearchPref[1].vValue.dwType =   ADSTYPE_INTEGER;
    SearchPref[1].vValue.Integer =  1000;

    hr = pSearch->SetSearchPreference(SearchPref, dwPref);
    if (FAILED(hr))
    {
	smpd_err_printf("Failed to set search prefs: hr:0x%x\n", hr);
	goto Cleanup;
    }

    /* Execute the search. From the GC get the distinguished name 
      of the SCP. Use the DN to bind to the SCP and get the other 
      properties. */
    LPWSTR rgszDN[] = {L"distinguishedName"};

    /* Search for a match of the product GUID. */
    swprintf(pszSearchString, L"keywords=%s", SMPD_SERVICE_VENDOR_GUIDW);
    hr = pSearch->ExecuteSearch(pszSearchString, rgszDN, 1, &hSearch);
    /*hr = pSearch->ExecuteSearch(L"keywords=5722fe5f-cf46-4594-af7c-0997ca2e9d72", rgszDN, 1, &hSearch);*/
    if (FAILED(hr))
    {
	smpd_err_printf("ExecuteSearch failed: hr:0x%x\n", hr);
	goto Cleanup;
    }

    /* Loop through the results. Each row should be an instance of the 
      service identified by the product GUID.
      Add logic to select from multiple service instances. */
    while (SUCCEEDED(hr = pSearch->GetNextRow(hSearch)))
    {
	if (hr == S_ADS_NOMORE_ROWS)
	{
	    DWORD dwError = ERROR_SUCCESS;
	    WCHAR szError[512];
	    WCHAR szProvider[512];

	    ADsGetLastError(&dwError, szError, 512, szProvider, 512);
	    if (ERROR_MORE_DATA == dwError)
	    {
		continue;
	    }
	    goto Cleanup;
	}

	ADS_SEARCH_COLUMN Col;

	hr = pSearch->GetColumn(hSearch, L"distinguishedName", &Col);
	pszDN = AllocADsStr(Col.pADsValues->CaseIgnoreString);
	pSearch->FreeColumn(&Col);

	/* Bind to the DN to get the other properties. */
	LPWSTR lpszLDAPPrefix = L"LDAP://";
	DWORD dwSCPPathLength = (DWORD)(wcslen(lpszLDAPPrefix) + wcslen(pszDN) + 1);
	LPWSTR pwszSCPPath = (LPWSTR)malloc(sizeof(WCHAR) * dwSCPPathLength);
	if (pwszSCPPath)
	{
	    wcscpy(pwszSCPPath, lpszLDAPPrefix);
	    wcscat(pwszSCPPath, pszDN);
	}       
	else
	{
	    smpd_err_printf("Failed to allocate a buffer\n");
	    goto Cleanup;
	}               
	/*wprintf(L"pszDN = %s\n", pszDN);*/
	/*FreeADsStr(pszDN);*/

	hr = ADsGetObject(pwszSCPPath, IID_IDirectoryObject, (void**)&pSCP);
	free(pwszSCPPath);

	if (SUCCEEDED(hr)) 
	{
	    /* Properties to retrieve from the SCP object. */
	    LPWSTR rgszAttribs[]=
	    {
		{L"serviceClassName"},
		{L"serviceDNSName"},
		/*{L"serviceDNSNameType"},*/
		{L"serviceBindingInformation"}
	    };

	    DWORD dwAttrs = sizeof(rgszAttribs)/sizeof(LPWSTR);
	    DWORD dwNumAttrGot;
	    hr = pSCP->GetObjectAttributes(rgszAttribs, dwAttrs, &pPropEntries, &dwNumAttrGot);
	    if (FAILED(hr)) 
	    {
		smpd_err_printf("GetObjectAttributes Failed. hr:0x%x\n", hr);
		goto Cleanup;
	    }

	    pszServiceDNSName = NULL;
	    pszClass = NULL;
	    iter = (smpd_host_spn_node_t*)malloc(sizeof(smpd_host_spn_node_t));
	    if (iter == NULL)
	    {
		smpd_err_printf("Unable to allocate memory to store an SPN entry.\n");
		goto Cleanup;
	    }
	    iter->next = NULL;
	    iter->host[0] = '\0';
	    iter->spn[0] = '\0';
	    iter->dnshost[0] = '\0';

	    /* Loop through the entries returned by GetObjectAttributes 
	    and save the values in the appropriate buffers.  */
	    for (int i = 0; i < (LONG)dwAttrs; i++) 
	    {
		if ((wcscmp(L"serviceDNSName", pPropEntries[i].pszAttrName) == 0) &&
		    (pPropEntries[i].dwADsType == ADSTYPE_CASE_IGNORE_STRING)) 
		{
		    pszServiceDNSName = AllocADsStr(pPropEntries[i].pADsValues->CaseIgnoreString);
		    /*wprintf(L"pszServiceDNSName = %s\n", pszServiceDNSName);*/
		}

		/*
		if ((wcscmp(L"serviceDNSNameType", pPropEntries[i].pszAttrName) == 0) &&
		(pPropEntries[i].dwADsType == ADSTYPE_CASE_IGNORE_STRING)) 
		{
		pszServiceDNSNameType = AllocADsStr(pPropEntries[i].pADsValues->CaseIgnoreString);
		wprintf(L"pszServiceDNSNameType = %s\n", pszServiceDNSNameType);
		}
		*/

		if ((wcscmp(L"serviceClassName", pPropEntries[i].pszAttrName) == 0) &&
		    (pPropEntries[i].dwADsType == ADSTYPE_CASE_IGNORE_STRING)) 
		{
		    pszClass = AllocADsStr(pPropEntries[i].pADsValues->CaseIgnoreString);
		    /*wprintf(L"pszClass = %s\n", pszClass);*/
		}

		if ((wcscmp(L"serviceBindingInformation", pPropEntries[i].pszAttrName) == 0) &&
		    (pPropEntries[i].dwADsType == ADSTYPE_CASE_IGNORE_STRING)) 
		{
		    usPort=(USHORT)_wtoi(pPropEntries[i].pADsValues->CaseIgnoreString);
		    /*wprintf(L"usPort = %d\n", usPort);*/
		}
	    }

	    wcstombs(iter->dnshost, pszServiceDNSName, SMPD_MAX_NAME_LENGTH);
	    wcstombs(temp_str, pszClass, SMPD_MAX_NAME_LENGTH);
	    /*MPIU_Snprintf(iter->spn, SMPD_MAX_NAME_LENGTH, "%s/%s:%d", temp_str, iter->dnshost, usPort);*/
	    wcstombs(temp_str2, pszDN, SMPD_MAX_NAME_LENGTH);
	    MPIU_Snprintf(iter->spn, SMPD_MAX_NAME_LENGTH, "%s/%s/%s", temp_str, iter->dnshost, temp_str2);
	    MPIU_Strncpy(iter->host, iter->dnshost, SMPD_MAX_NAME_LENGTH);
	    strtok(iter->host, ".");
	    iter->next = spn_list;
	    spn_list = iter;
	    if (pszServiceDNSName != NULL)
	    {
		FreeADsStr(pszServiceDNSName);
	    }
	    if (pszClass != NULL)
	    {
		FreeADsStr(pszClass);
	    }
	}
	FreeADsStr(pszDN);
    }

Cleanup:
    /*
    iter = spn_list;
    while (iter != NULL)
    {
	printf("host   : %s\n", iter->host);
	printf("dnshost: %s\n", iter->dnshost);
	printf("spn    : %s\n", iter->spn);
	iter = iter->next;
    }
    fflush(stdout);
    */
    if (pSCP)
    {
	pSCP->Release();
	pSCP = NULL;
    }

    if (pPropEntries)
    {
	FreeADsMem(pPropEntries);
	pPropEntries = NULL;
    }

    if (pSearch)
    {
	if (hSearch)
	{
	    pSearch->CloseSearchHandle(hSearch);
	    hSearch = NULL;
	}

	pSearch->Release();
	pSearch = NULL;
    }
    CoUninitialize();

    /* t2 = PMPI_Wtime();
    smpd_dbg_printf("build_spn_list took %0.6f seconds\n", t2-t1);
    */

    return SMPD_SUCCESS;
}