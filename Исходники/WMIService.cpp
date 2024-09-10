jobject WMIService::OpenNamespace(JNIEnv* pJavaEnv, LPWSTR nsName, LONG lFlags)
{
	CComPtr<IWbemServices> ptrNamespace;
	HRESULT hres = ptrWbemServices->OpenNamespace(nsName, lFlags, NULL, &ptrNamespace, NULL);
	if (FAILED(hres)) {
		THROW_COMMON_ERROR(L"Can't open namespace", hres);
		return NULL;
	}
    hres = CoSetProxyBlanket(
		ptrNamespace,				 // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
		);
    if (FAILED(hres)) {
        THROW_COMMON_ERROR(L"Can't set proxy blanket for opened namespace", hres);
		return NULL;
    }

	JNIMetaData& jniMeta = JNIMetaData::GetMetaData(pJavaEnv);
	
	jobject newServiceObject = pJavaEnv->NewObject(jniMeta.wmiServiceClass, jniMeta.wmiServiceConstructor);
	if (pJavaEnv->ExceptionCheck()) {
		return NULL;
	}
	WMIService* pServiceHandler = new WMIService(pJavaEnv, newServiceObject);
	pServiceHandler->ptrWbemServices = ptrNamespace;

	//WriteLog(pJavaEnv, LT_DEBUG, bstr_t("Connected to WMI namespace ") + nsName);

	return newServiceObject;
}