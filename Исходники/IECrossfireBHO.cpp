bool IECrossfireBHO::initServer(bool startIfNeeded) {
	if (m_server) {
		return true;
	}
	if (!startIfNeeded && !FindWindow(ServerWindowClass, NULL)) {
		return false;
	}

	/* the following is intentionally commented */

//	CComPtr<IDispatch> dispatch = NULL;
//	long applicationHwnd = 0;
//	HRESULT hr = m_webBrowser->get_Application(&dispatch);
//	if (SUCCEEDED(hr)) {
//		DISPID dispId;
//		CComBSTR name("HWND");
//		hr = dispatch->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_SYSTEM_DEFAULT, &dispId);
//		if (SUCCEEDED(hr)) {
//			DISPPARAMS params;
//			memset(&params, 0, sizeof(DISPPARAMS));
//			VARIANT variant;
//			hr = dispatch->Invoke(dispId, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &params, &variant, NULL, NULL);
//			if (SUCCEEDED(hr)) {
//				applicationHwnd = variant.lVal;
//			}
//		}
//	}
//	if (!applicationHwnd) {
//		Logger::error("IECrossfireBHO.initServer(): failed to get the application HWND", hr);
//		return false;
//	}

	CComPtr<ICrossfireServerClass> serverClass = NULL;
	HRESULT hr = CoGetClassObject(CLSID_CrossfireServer, CLSCTX_ALL, 0, IID_ICrossfireServerClass, (LPVOID*)&serverClass);
	if (FAILED(hr)) {
		Logger::error("IECrossfireBHO.initServer(): CoGetClassObject() failed", hr);
		return false;
	}

	hr = serverClass->GetServer(/*applicationHwnd,*/ &m_server);
	if (FAILED(hr)) {
		Logger::error("IECrossfireBHO.initServer(): GetController() failed", hr);
		return false;
	}

	hr = m_server->getState(&m_serverState);
	if (FAILED(hr)) {
		Logger::error("IECrossfireBHO.initServer(): getState() failed", hr);
	}

	if (m_serverState == STATE_CONNECTED) {
		hr = m_server->registerBrowser(GetCurrentProcessId(), this);
		if (FAILED(hr)) {
			Logger::error("IECrossfireBHO.initServer(): registerBrowser() failed", hr);
			/* continue */
		}
	}

	return true;
}