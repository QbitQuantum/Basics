COlePropPage::COlePropPage(CLSID clsidPage, LPUNKNOWN* lpAryUnk, int& count) : CPropertyPage(COlePropPage::IDD),
	m_clsidPage(clsidPage), m_pObject(lpAryUnk)
{
	// Create COM Property page and get IPropertyPage interface
	EnableAutomation();
	HRESULT hRes = E_FAIL;
	m_pPropPage=NULL;
	try {
		hRes = CoCreateInstance( m_clsidPage, NULL, CLSCTX_INPROC, IID_IPropertyPage, (void**)&m_pPropPage );
		if( FAILED( hRes ) )
			AfxThrowOleException( hRes );
		
		hRes = m_pPropPage->SetPageSite( (IPropertyPageSite*) GetInterface( &IID_IPropertyPageSite ) );
		if( FAILED( hRes ) )
			AfxThrowOleException( hRes );
		
		hRes = m_pPropPage->SetObjects( count, m_pObject );
		if( FAILED( hRes ) )
			AfxThrowOleException( hRes );
		
		IMalloc     *pIMalloc;
		if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
			AfxThrowOleException(E_FAIL);
		
		PROPPAGEINFO* pPPI = (PROPPAGEINFO*) pIMalloc->Alloc(sizeof(PROPPAGEINFO));
		pPPI->cb = sizeof(PROPPAGEINFO);
		hRes = m_pPropPage->GetPageInfo(pPPI);
#ifndef UNICODE
		m_strCaption.Format("%S", pPPI->pszTitle);
#else
		m_strCaption = pPPI->pszTitle;
#endif
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;
		m_psp.hIcon = ::LoadIcon(NULL, IDI_QUESTION);
		
		pIMalloc->Free(pPPI);
		pIMalloc->Release();
		
		
	} catch (COleException * e)
	{
		throw (e);
	}
}