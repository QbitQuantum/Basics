CrossfireServer::~CrossfireServer() {
	delete m_bpManager;

	std::map<DWORD,CrossfireContext*>::iterator iterator = m_contexts->begin();
	while (iterator != m_contexts->end()) {
		delete iterator->second;
		iterator++;
	}
	delete m_contexts;

	std::map<DWORD, IBrowserContext*>::iterator iterator2 = m_browsers->begin();
	while (iterator2 != m_browsers->end()) {
		iterator2->second->Release();
		iterator2++;
	}
	delete m_browsers;

	std::vector<CrossfireEvent*>::iterator iterator3 = m_pendingEvents->begin();
	while (iterator3 != m_pendingEvents->end()) {
		if (m_connection) {
			sendEvent(*iterator3);
		}
		delete *iterator3;
		iterator3++;
	}
	delete m_pendingEvents;

	delete m_inProgressPacket;
	delete m_processor;
	if (m_connection) {
		delete m_connection;
	}

	if (m_messageWindow) {
		DestroyWindow(m_messageWindow);
		UnregisterClass(WindowClass, GetModuleHandle(NULL));
	}

//	if (m_windowHandle) {
		CComPtr<ICrossfireServerClass> serverClass = NULL;
		HRESULT hr = CoGetClassObject(CLSID_CrossfireServer, CLSCTX_ALL, 0, IID_ICrossfireServerClass, (LPVOID*)&serverClass);
		if (FAILED(hr)) {
			Logger::error("~CrossfireServer: CoGetClassObject() failed", hr);
			return;
		}

		hr = serverClass->RemoveServer(/*m_windowHandle*/ 0);
		if (FAILED(hr)) {
			Logger::error("~CrossfireServer: RemoveServer() failed", hr);
			return;
		}
//	}
}