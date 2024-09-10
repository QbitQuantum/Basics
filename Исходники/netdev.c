int if_up(char *devname)
{
	/* Get network adapter status from WMI using COM */
        DWORD ifStatus = 0;
	HRESULT hres;
        IWbemLocator *locator=NULL;
        IWbemServices *services=NULL;
        IEnumWbemClassObject *results=NULL;
        BSTR resource=SysAllocString(L"ROOT\\CIMV2");
        BSTR language=SysAllocString(L"WQL");
        LPWSTR query_h=L"SELECT NetConnectionStatus FROM Win32_NetworkAdapter " 
                       L"WHERE NetConnectionID = ";

	size_t len=_mbslen(devname);
        size_t cont=0;

        /* Count how many single single quotes(') in devname for escap */
        /* single quotes(') in WQL query string */
        char *pc=devname;
        for(; pc=(char *)_mbschr(pc,'\''); pc++) {
                cont++;
        }
        /* Need to add two single quotes(') at begin and after devname */
        WCHAR query_str[len+cont+wcslen(query_h)+3];
        wcscpy(query_str,query_h);
        /* Add start single quote(') to query string before append devname */
        wcscat(query_str,L"'");
        WCHAR connid[len+1];
        mbstowcs(connid,devname,len+1);
        WCHAR *pw, *qw=connid;
        for(pw=connid; pw=wcschr(pw, L'\''); pw++) {
                /* Escape single quotes(') in devname */
                wcsncat(query_str,qw,pw-qw);
                wcscat(query_str,L"\\");
                qw=pw;
        }
        wcscat(query_str,qw);
        /* Append terminal single quote(') to query string */
        wcscat(query_str,L"'");
        BSTR query=SysAllocString(query_str);	

        // initialize COM
        hres=CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
        	log_warn("Failed to initialize COM library:0x%x\n", hres);
        	goto cleanup;
    	}
        hres=CoInitializeSecurity(NULL, -1, NULL, NULL,
                             RPC_C_AUTHN_LEVEL_DEFAULT,
                             RPC_C_IMP_LEVEL_IMPERSONATE,
                             NULL, EOAC_NONE, NULL);
	if (FAILED(hres))
    	{
        	log_warn("Failed to initialize security:0x%x\n",hres);
        	CoUninitialize();
        	goto cleanup;
    	}
        // connect to WMI
        hres=CoCreateInstance(&CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
                         &IID_IWbemLocator, (LPVOID *) &locator);
	if (FAILED(hres))
    	{
        	log_warn("Failed to create IWbemLocator object:0x%x\n",hres);
        	CoUninitialize();
        	goto cleanup;
    	}
        hres=locator->lpVtbl->ConnectServer(locator,
				resource,
				NULL, NULL, NULL, 0,
				NULL, NULL, &services);
	if (FAILED(hres))
	{
        	log_warn("Could not connect:0x%x\n",hres);
        	locator->lpVtbl->Release(locator);     
        	CoUninitialize();
        	goto cleanup;
    	}
        // issue a WMI query
        hres=services->lpVtbl->ExecQuery(services, language, query,
                                    WBEM_FLAG_BIDIRECTIONAL,
                                    NULL, &results);
	if (FAILED(hres))
    	{
        	log_warn("Query for processes failed:0x%x\n",hres);
        	services->lpVtbl->Release(services);
        	locator->lpVtbl->Release(locator);     
        	CoUninitialize();
        	goto cleanup;
    	}
        // list the query results
        else
	{
                IWbemClassObject *result = NULL;
                ULONG returnedCount = 0;
                // enumerate the retrieved objects
                while((results->lpVtbl->Next(results, WBEM_INFINITE, 1, &result, &returnedCount)) == S_OK) {
                        VARIANT status;
                        // obtain the desired properties of the next result 
                        result->lpVtbl->Get(result, L"NetConnectionStatus", 0, &status, 0, 0);
                        // release the current result object
                        result->lpVtbl->Release(result);
                        if(status.intVal==2) {
                                ifStatus=-1;
                                break;
                        }
                }
        }
        // release WMI COM interfaces
        results->lpVtbl->Release(results);
        services->lpVtbl->Release(services);
        locator->lpVtbl->Release(locator);
        // unwind everything else we've allocated
        CoUninitialize();

cleanup:
        SysFreeString(query);
        SysFreeString(language);
        SysFreeString(resource);

	return ifStatus;
}