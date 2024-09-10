HRESULT CWordObject::Release()
{
	HRESULT hr;
	
	if (m_pUnknown == NULL) 
		return S_OK;

	LPUNKNOWN lpUnk = NULL;
	
	if (m_pStrUnknown != NULL)
	{
		hr = CoGetInterfaceAndReleaseStream(m_pStrUnknown, IID_IUnknown, (void**) &lpUnk);
		if (FAILED(hr))
		{
			LOG_WS_ERROR(_T("CoGetInterfaceAndReleaseStream FAILED."));	
		}
	}
	else
	{
		lpUnk = m_pUnknown;
		m_pWordCreator->AddRef(lpUnk);
	}


	try
	{
		m_pUnknown->Release();
		m_pUnknown = NULL;
	}
	catch(...)
	{
		m_pUnknown = NULL;
		LOG_WS_ERROR(_T("m_pUnknown Failed to release"));
	}

	
	if (NULL == lpUnk)
	{
		LOG_WS_ERROR(_T("lpUnk == NULL"));
		return E_FAIL;
	}



	if (m_bUsingCurrentInstance)
	{	
		hr = S_FALSE;
	}
	else if (!IsVisible(lpUnk))
	{
		hr = Quit(lpUnk);
	}
	else
	{
		// If Word is visible, then only quit the cached Word instance if we are sure that
		// there aren't any manually opened documents.  i.e. if the user has opened a document,
		// so that there is a visible instance of Word open while DeltaVw is still open.
		Word::_ApplicationPtr pApp = GetApplicationPtr();

		if( pApp )
		{
			long lNumDocs = pApp->Documents->Count;

			if( lNumDocs <= 0 )
			{
				LOG_WS_INFO(L"No open documents found for the current Word instance.  Quitting Word");

				SetVisible(false);
				hr = Quit(lpUnk);
			}
			else
			{
				LOG_WS_INFO(L"Documents are still open in the current Word instance.  NOT quitting Word");
			}
		}
	}

	if (IsCachingWordEnabled())
		m_pGit->RevokeInterfaceFromGlobal(m_dwSessionCookie);

	try
	{
		if (lpUnk)
		{
			lpUnk->Release();
			lpUnk = NULL;			
		}
	}
	catch(...)
	{
		lpUnk = NULL;	
		LOG_WS_ERROR(_T("m_pUnknown Failed to release"));
	}

	// This is required to stop the DeltaView app tests from hanging
	Sleep(125);
	
	return hr;
}