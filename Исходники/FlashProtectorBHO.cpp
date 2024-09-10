STDMETHODIMP CFlashProtectorBHO::SetSite(IUnknown* pUnkSite)
{
	if (pUnkSite != NULL)
	{
		// Cache the pointer to IWebBrowser2.
		HRESULT hr = pUnkSite->QueryInterface(IID_IWebBrowser2, (void **)&m_spWebBrowser);
		if (SUCCEEDED(hr))
		{
			// Register to sink events from DWebBrowserEvents2.
			hr = DispEventAdvise(m_spWebBrowser);
			if (SUCCEEDED(hr))
			{
				m_fAdvised = TRUE;
			}
		}
		//
		BOOL is_ie_protect_mode = FALSE;
		hr = IEIsProtectedModeProcess(&is_ie_protect_mode);
		long hook_result = 0;
		if(SUCCEEDED(hr) && is_ie_protect_mode) {
			hook_result = IEHooker::GetIEHooker()->Hook(true);
		} else {
			hook_result = IEHooker::GetIEHooker()->Hook(false);
		}

	}
	else
	{
		// Unregister event sink.
		if (m_fAdvised)
		{
			DispEventUnadvise(m_spWebBrowser);
			m_fAdvised = FALSE;
		}

		// Release cached pointers and other resources here.
		m_spWebBrowser.Release();
	}

	// Call base class implementation.
	return IObjectWithSiteImpl<CFlashProtectorBHO>::SetSite(pUnkSite);
}