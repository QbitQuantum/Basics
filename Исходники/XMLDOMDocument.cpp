STDMETHODIMP CXMLDOMDocument::load(VARIANT xmlSource, VARIANT_BOOL  *isSuccessful)
{
	ATLTRACE(_T("CXMLDOMDocument::load\n"));

	if (NULL == isSuccessful)
		return E_POINTER;

	*isSuccessful = VARIANT_FALSE;

	if (V_VT(&xmlSource) != VT_BSTR					&&
		V_VT(&xmlSource) != VT_DISPATCH				&&
		V_VT(&xmlSource) != (VT_ARRAY | VT_VARIANT)	&&
		V_VT(&xmlSource) != (VT_ARRAY | VT_UI1)		&&
		V_VT(&xmlSource) != VT_UNKNOWN)
		return E_INVALIDARG;

	// do not start another thread if there is another active
	if (NULL != m_hParseThread) {
		DWORD exitCode = 0;
		BOOL rc = ::GetExitCodeThread(m_hParseThread, &exitCode);
		if (!rc || STILL_ACTIVE == exitCode)
			return S_OK;
		
		::CloseHandle(m_hParseThread);
		m_hParseThread = NULL;
	}

	HRESULT hr = S_OK;
	m_bAbort = false;
	
	m_FileName = _T("");
	m_xml = _T("");
	m_TmpDocument = 0;
	m_bThreadValidate = m_bValidate;
	
	if (V_VT(&xmlSource) == VT_BSTR) {
		m_FileName = V_BSTR(&xmlSource);
		if (0 == m_FileName.length())
			return E_INVALIDARG;

		// see if the file is relative path
		if (!PathIsURL(m_FileName) && PathIsRelative(m_FileName)) {
			// try appending baseurl if exists
			_bstr_t baseURL;
			if (S_OK == GetBaseURL(baseURL)) {
				// change any backslashes to slashes
				LPTSTR loc = _tcschr(m_FileName,_T('\\'));
				while (loc != NULL) {
					*loc = _T('/');
					loc = _tcschr(m_FileName,_T('\\'));
				}
				m_FileName = baseURL + _T("/") + m_FileName;
			}
			else {
				TCHAR szCurDir[MAX_PATH];
				GetCurrentDirectory(MAX_PATH,szCurDir);
				m_FileName=_bstr_t(szCurDir) + _T("\\") + m_FileName;
			}
		}
	}
	else
	if (V_VT(&xmlSource) == VT_UNKNOWN) {
		CComQIPtr<IStream,&IID_IStream> pS(V_UNKNOWN(&xmlSource));
		if (!pS)
			return E_INVALIDARG;

		CComBSTR b;
		hr = b.ReadFromStream(pS);
		if (S_OK != hr)
			return hr;

		m_xml = b;
		if (0 == m_xml.length())
			return E_INVALIDARG;
	}
	else
	if (V_VT(&xmlSource) == VT_DISPATCH) {
		CComQIPtr<IXMLDOMDocument,&IID_IXMLDOMDocument> pDoc(V_DISPATCH(&xmlSource));
		if (!pDoc)
			return E_INVALIDARG;
		
		BSTR b = NULL;
		hr = pDoc->get_xml(&b);
		if (S_OK != hr)
			return hr;

		m_xml = b;
		::SysFreeString(b);

		if (0 == m_xml.length())
			return E_INVALIDARG;
	}
	else
	if (V_VT(&xmlSource) == (VT_ARRAY | VT_VARIANT)) {
		SAFEARRAY *pArray = reinterpret_cast<SAFEARRAY *> (xmlSource.byref);
		if (NULL == pArray)
			return E_INVALIDARG;

		long lLBoundVar = 0;
		long lUBoundVar = 0;
	
		UINT dims = ::SafeArrayGetDim(pArray);
		if (dims == 0)
			return E_INVALIDARG;
	
		hr = ::SafeArrayGetLBound(pArray, dims, &lLBoundVar);
		if (S_OK != hr)
			return hr;

		hr = ::SafeArrayGetUBound(pArray, dims, &lUBoundVar);
		if (S_OK != hr)
			return hr;

		if (lUBoundVar >= lLBoundVar) {
			VARIANT *pIndex = NULL;
			hr = ::SafeArrayAccessData(pArray, reinterpret_cast<void **> (&pIndex));
			if (S_OK != hr)
				return hr;

			int length = lUBoundVar-lLBoundVar+2;
			BYTE *body = new BYTE[length];
			for (long i = 0; i <= lUBoundVar-lLBoundVar; ++i) {	
				VARIANT var = pIndex[i];
				if (V_VT(&var) != VT_UI1) {
					hr = E_INVALIDARG;
					break;
				}
				body[i] = V_UI1(&var);
			}
			body[length-1] = 0;
					
			::SafeArrayUnaccessData(pArray);
			if (S_OK != hr) {
				delete [] body;
				return hr;
			}
			m_xml = reinterpret_cast<char*> (body);
			delete [] body;
			if (0 == m_xml.length())
				return E_INVALIDARG;
		}
	}	
	else
	if (V_VT(&xmlSource) == (VT_ARRAY | VT_UI1)) {
		SAFEARRAY *pArray = reinterpret_cast<SAFEARRAY *> (xmlSource.byref);
		if (NULL == pArray)
			return E_INVALIDARG;

		long lLBoundVar = 0;
		long lUBoundVar = 0;
	
		UINT dims = ::SafeArrayGetDim(pArray);
		if (dims == 0)
			return E_INVALIDARG;
	
		hr = ::SafeArrayGetLBound(pArray, dims, &lLBoundVar);
		if (S_OK != hr)
			return hr;

		hr = ::SafeArrayGetUBound(pArray, dims, &lUBoundVar);
		if (S_OK != hr)
			return hr;

		if (lUBoundVar >= lLBoundVar) {
			BYTE *pIndex = NULL;
			hr = ::SafeArrayAccessData(pArray, reinterpret_cast<void **> (&pIndex));
			if (S_OK != hr)
				return hr;

			int length = lUBoundVar-lLBoundVar+2;
			BYTE *body = new BYTE[length];
			for (long i = 0; i <= lUBoundVar-lLBoundVar; ++i)	
				body[i] = pIndex[i];
			
			body[length-1] = 0;
			::SafeArrayUnaccessData(pArray);
			m_xml = reinterpret_cast<char*> (body);
			delete [] body;
			if (0 == m_xml.length())
				return E_INVALIDARG;
		}
	}	

	UINT nthreadID = 0;
	m_hParseThread = reinterpret_cast<HANDLE> (_beginthreadex(NULL,
												 0,
											     CXMLDOMDocument::ParseThread,
												 (void *) this,
												 0,
												 &nthreadID));
	if (NULL == m_hParseThread)
		return S_OK;
	
	if (m_bAsync) {
		*isSuccessful = VARIANT_TRUE;
		return S_OK;
	}

	bool bWait = true;
	while (bWait) {
		DWORD dwEvt = MsgWaitForMultipleObjects(1,&m_hParseThread,FALSE,INFINITE,QS_ALLINPUT);
		switch(dwEvt) {
			case WAIT_OBJECT_0:
				bWait = false;
				break;
			case WAIT_OBJECT_0 + 1:
			{
				MSG msg;
				while(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
					if (WM_CLOSE == msg.message || WM_QUIT == msg.message) {
						 bWait = false;
						 m_bAbort = true;
						 break;
					}
					else {
						PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				break;
			}
			default:
				m_bAbort = true;
				bWait = false;
				break;
		}
	}

	if (m_bAbort)
		return S_OK;

	if (m_bParseError)
		return hr;

    if(m_Document)
        delete m_Document;
	m_Document = m_TmpDocument;
	m_TmpDocument = 0;
	
	m_url = m_FileName;
	*isSuccessful = VARIANT_TRUE;
	
	return hr;
}