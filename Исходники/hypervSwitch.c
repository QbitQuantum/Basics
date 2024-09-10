/**
 * Gets the switch port info from WMI (switch port friendly name, ifSpeed) 
 * and merges into the list of existing ports.
 */
void readWMISwitchPorts(HSP *sp)
{
	myLog(LOG_INFO, "entering readWMISwitchPorts");
	BSTR path = SysAllocString(WMI_VIRTUALIZATION_NS_V2);
	HRESULT hr = S_FALSE;
	IWbemServices *pNamespace = NULL;

	hr = connectToWMI(path, &pNamespace);
	if (FAILED(hr)) {
		//only try the v2 namespace since this will only be present
		//with the extensible switch that supports sampling.
	    //don't try to get counters if there is no sampling.
		SysFreeString(path);
		myLog(LOG_INFO, "readWMISwitchPorts: virtualization namespace v2 not found");
		return;
	} else {
		SysFreeString(path);
	}

	BSTR queryLang = SysAllocString(L"WQL");
	BSTR query = SysAllocString(L"SELECT * FROM Msvm_EthernetSwitchPort");
	IEnumWbemClassObject *switchPortEnum = NULL;
	hr = pNamespace->ExecQuery(queryLang, query, WBEM_FLAG_FORWARD_ONLY, NULL, &switchPortEnum);
	SysFreeString(queryLang);
	SysFreeString(query);
	if (FAILED(hr)) {
		myLog(LOG_ERR,"readWMISwitchPorts: ExecQuery() failed for query %S error=0x%x", query, hr);
		CoUninitialize();
		return;
	}

	if (sp->vAdaptorList == NULL) {
		sp->vAdaptorList = adaptorListNew();
	}
	IWbemClassObject *switchPortObj = NULL;

	BSTR propElementName = SysAllocString(L"ElementName");
	BSTR propSystemName = SysAllocString(L"SystemName");
	BSTR propName = SysAllocString(L"Name");
	BSTR propSpeed = SysAllocString(L"Speed");
	//could also get ifDirection but FullDuplex=True always
	VARIANT systemVal;
	VARIANT elementVal;
	VARIANT nameVal;
	VARIANT speedVal;

	hr = WBEM_S_NO_ERROR;
	while (WBEM_S_NO_ERROR == hr) {
		SFLAdaptor *vAdaptor = NULL;
		ULONG uReturned = 1;
		hr = switchPortEnum->Next(WBEM_INFINITE, 1, &switchPortObj, &uReturned);
		if (0 == uReturned) {
			break;
		}
		HRESULT portHr;
		portHr = switchPortObj->Get(propName, 0, &nameVal, 0, 0);
		char portGuid[FORMATTED_GUID_LEN+1];
		guidToString(nameVal.bstrVal, (UCHAR *)portGuid, FORMATTED_GUID_LEN);
		myLog(LOG_INFO, "readWMISwitchPorts: portGuid=%s", portGuid);
		VariantClear(&nameVal);
		vAdaptor = adaptorListGet(sp->vAdaptorList, portGuid);
		if (vAdaptor != NULL) {
			portHr = switchPortObj->Get(propSystemName, 0, &systemVal, 0, 0);
			portHr = switchPortObj->Get(propElementName, 0, &elementVal, 0, 0);
			portHr = switchPortObj->Get(propSpeed, 0, &speedVal, 0, 0);
			int length = SysStringLen(systemVal.bstrVal)+1; //include room for terminating null
			wchar_t *switchName = (wchar_t *)my_calloc(length*sizeof(wchar_t));
			wcscpy_s(switchName, length, systemVal.bstrVal);
			length = SysStringLen(elementVal.bstrVal)+1; 
			wchar_t *friendlyName = (wchar_t *)my_calloc(length*sizeof(wchar_t));
			wcscpy_s(friendlyName, length, elementVal.bstrVal);
			ULONGLONG ifSpeed = _wcstoui64(speedVal.bstrVal, NULL, 10);
			VariantClear(&systemVal);
			VariantClear(&elementVal);
			VariantClear(&speedVal);
			HVSVPortInfo *portInfo = (HVSVPortInfo *)vAdaptor->userData;
			if (portInfo->switchName != NULL) {
				my_free(portInfo->switchName);
			}
			portInfo->switchName = switchName;
			if (portInfo->portFriendlyName != NULL) {
				my_free(portInfo->portFriendlyName);
			}
			portInfo->portFriendlyName = friendlyName;
			setPortCountersInstance(vAdaptor);
			vAdaptor->ifSpeed = ifSpeed;
			//Get the MACs and VM system name when we enumerate the vms.
			myLog(LOG_INFO, 
				  "readWMISwitchPorts: updated switch port %s %S portId=%u ifIndex=%u ifSpeed=%llu counterName=%S", 
				  vAdaptor->deviceName, portInfo->portFriendlyName, portInfo->portId, vAdaptor->ifIndex, 
				  vAdaptor->ifSpeed, portInfo->portCountersInstance);
		} else {
			myLog(LOG_INFO, "readWMISwitchPorts: vAdapter not found");
		}
		switchPortObj->Release();
	}
	switchPortEnum->Release();
	pNamespace->Release();
	CoUninitialize();
	SysFreeString(propElementName);
	SysFreeString(propSystemName);
	SysFreeString(propName);
	SysFreeString(propSpeed);

	return;
}