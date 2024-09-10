STDMETHODIMP CMyBHO::SetSite(IUnknown *pUnkSite)
{
	if(pUnkSite != NULL)
	{
		pUnkSite->QueryInterface(IID_IWebBrowser2,(void **)&m_spWebBrowser);
		CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> spCPC(m_spWebBrowser);
		HRESULT hr = spCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, &m_spCP);
		m_spCP->Advise(reinterpret_cast<IDispatch*>(this),&m_dwCookie);
#ifdef __LEA_LOG
		char tempPath[MAX_PATH];
		DWORD dwLen = GetTempPathA(MAX_PATH,tempPath);
		strcat_s(tempPath,LOG_FILE);
		if((m_fpLog = fopen(tempPath,"a+")) == NULL)
		{
			TCHAR Msg[1024];
			wsprintf(Msg,L"Log file open error. ");
			MessageBox(NULL, Msg,L"Warning!",MB_OK|MB_ICONINFORMATION);
		}
#endif

	}
	else
	{
		m_spWebBrowser.Release();
#ifdef __LEA_LOG
		if(m_fpLog !=NULL)
		{
			fclose(m_fpLog);
		}	
#endif
	}

	//MessageBox(NULL,L"Success fully loaded",L"Lea BHO",MB_OK|MB_ICONINFORMATION);
	return IObjectWithSiteImpl::SetSite(pUnkSite);
}