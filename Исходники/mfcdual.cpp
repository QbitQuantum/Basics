HRESULT DualHandleException(REFIID riidSource, const CException* pAnyException)
{
	USES_CONVERSION;

	ASSERT_VALID(pAnyException);

	TRACE0("DualHandleException called\n");

	// Set ErrInfo object so that VTLB binding container
	// applications can get rich error information.
	ICreateErrorInfo* pcerrinfo;
	HRESULT hr = CreateErrorInfo(&pcerrinfo);
	if (SUCCEEDED(hr))
	{
		TCHAR   szDescription[256];
		LPCTSTR pszDescription = szDescription;
		GUID    guid = GUID_NULL;
		DWORD   dwHelpContext = 0;
		BSTR    bstrHelpFile = NULL;
		BSTR    bstrSource = NULL;
		if (pAnyException->IsKindOf(RUNTIME_CLASS(COleDispatchException)))
		{
			// specific IDispatch style exception
			COleDispatchException* e = (COleDispatchException*)pAnyException;

			guid = riidSource;
			hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF,
							  (e->m_wCode + 0x200));

			pszDescription = e->m_strDescription;
			dwHelpContext = e->m_dwHelpContext;

			// propagate source and help file if present
			// call ::SysAllocString directly so no further exceptions are thrown
			if (!e->m_strHelpFile.IsEmpty())
				bstrHelpFile = ::SysAllocString(T2COLE(e->m_strHelpFile));
			if (!e->m_strSource.IsEmpty())
				bstrSource = ::SysAllocString(T2COLE(e->m_strSource));

		}
		else if (pAnyException->IsKindOf(RUNTIME_CLASS(CMemoryException)))
		{
			// failed memory allocation
			AfxLoadString(AFX_IDP_FAILED_MEMORY_ALLOC, szDescription);
			hr = E_OUTOFMEMORY;
		}
		else
		{
			// other unknown/uncommon error
			AfxLoadString(AFX_IDP_INTERNAL_FAILURE, szDescription);
			hr = E_UNEXPECTED;
		}

		if (bstrHelpFile == NULL && dwHelpContext != 0)
			bstrHelpFile = ::SysAllocString(T2COLE(AfxGetApp()->m_pszHelpFilePath));

		if (bstrSource == NULL)
			bstrSource = ::SysAllocString(T2COLE(AfxGetAppName()));

		// Set up ErrInfo object
		pcerrinfo->SetGUID(guid);
		pcerrinfo->SetDescription(::SysAllocString(T2COLE(pszDescription)));
		pcerrinfo->SetHelpContext(dwHelpContext);
		pcerrinfo->SetHelpFile(bstrHelpFile);
		pcerrinfo->SetSource(bstrSource);

		TRACE(_T("\tSource = %ws\n"), bstrSource);
		TRACE(_T("\tDescription = %s\n"), pszDescription);
		TRACE(_T("\tHelpContext = %lx\n"), dwHelpContext);
		TRACE(_T("\tHelpFile = %ws\n"), bstrHelpFile);

		// Set the ErrInfo object for the current thread
		IErrorInfo* perrinfo;
		if (SUCCEEDED(pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID*)&perrinfo)))
		{
			SetErrorInfo(0, perrinfo);
			perrinfo->Release();
		}

		pcerrinfo->Release();
	}

	TRACE(_T("DualHandleException returning HRESULT %lx\n"), hr);

	return hr;
}