BOOL CIECanvas::Initialize(HWND hwnd, int tryMozilla) {

	hwndParent = hwnd;
	
	/*if (tryMozilla) { // Initialize using mozilla..

		hwndChild = ::CreateWindow("AtlAxWin", CLSID_MozillaBrowserString, 
			WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0,0,0,0, hwnd, NULL,
			::GetModuleHandle(NULL), NULL);

		// We should try to fallback to IE if mozilla not available...

	} else { // Initialize with IE5
*/
		hwndChild = ::CreateWindow("AtlAxWin", "Shell.Explorer.1", 
			WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0,0,0,0, hwnd, NULL,
			::GetModuleHandle(NULL), NULL);
/*	}*/

    IUnknown *pUnk = NULL;
    AtlAxGetControl(hwndChild, &pUnk);
    
    pUnk->QueryInterface(IID_IWebBrowser2, (void**)&m_spBrowser);

    if (m_spBrowser) {
        m_spBrowser->put_Visible(VARIANT_TRUE);

		// Set up the event sink
        BOOL bAdvised = AfxConnectionAdvise(pUnk /*m_spBrowser*/, DIID_DWebBrowserEvents2,
                                            m_pIE4Events->GetInterface(&IID_IUnknown),
                                            TRUE, &m_dwCookie);

        //printf("Advise for DWebBrowserEvents2 %s\n", bAdvised ? "succeeded" : "failed");

		m_spBrowser->Refresh();
        CComVariant ve;
        CComVariant vurl("about:blank");
		m_spBrowser->Navigate2(&vurl, &ve, &ve, &ve, &ve);
		return TRUE;
	}
	return FALSE;
}