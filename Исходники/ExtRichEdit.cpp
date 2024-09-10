void CExtRichEdit::InsertFace(CString strPicPath)
{
	LPLOCKBYTES lpLockBytes = NULL;
	SCODE sc;
	HRESULT hr;
	//print to RichEdit' s IClientSite
	LPOLECLIENTSITE m_lpClientSite;
	//A smart point to IAnimator
	IGifAnimatorPtr	m_lpAnimator;
	//ptr 2 storage	
	LPSTORAGE m_lpStorage;
	//the object 2 b insert 2
	LPOLEOBJECT	m_lpObject;

	//Create lockbytes
	sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
		AfxThrowOleException(sc);
	ASSERT(lpLockBytes != NULL);
	
	//use lockbytes to create storage
	sc = ::StgCreateDocfileOnILockBytes(lpLockBytes,
		STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, &m_lpStorage);
	if (sc != S_OK)
	{
		VERIFY(lpLockBytes->Release() == 0);
		lpLockBytes = NULL;
		AfxThrowOleException(sc);
	}
	ASSERT(m_lpStorage != NULL);
	
	//get the ClientSite of the very RichEditCtrl
	GetIRichEditOle()->GetClientSite(&m_lpClientSite);
	ASSERT(m_lpClientSite != NULL);

	try
	{
		//Initlize COM interface
		hr = ::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
		if( FAILED(hr) )
			_com_issue_error(hr);
		
		//Get GifAnimator object
		//here, I used a smart point, so I do not need to free it
		hr = m_lpAnimator.CreateInstance(CLSID_GifAnimator);	
		if( FAILED(hr) )
				_com_issue_error(hr);
		//COM operation need BSTR, so get a BSTR
		BSTR path = strPicPath.AllocSysString();

		//Load the gif
		hr = m_lpAnimator->LoadFromFile(path);
		if( FAILED(hr) )
			_com_issue_error(hr);
			
	//	TRACE0( m_lpAnimator->GetFilePath() );
		
		//get the IOleObject
		hr = m_lpAnimator.QueryInterface(IID_IOleObject, (void**)&m_lpObject);
		if( FAILED(hr) )
			_com_issue_error(hr);
		
		//Set it 2 b inserted
		OleSetContainedObject(m_lpObject, TRUE);
		
		//2 insert in 2 richedit, you need a struct of REOBJECT
		REOBJECT reobject;
		ZeroMemory(&reobject, sizeof(REOBJECT));

		reobject.cbStruct = sizeof(REOBJECT);	
		CLSID clsid;
		sc = m_lpObject->GetUserClassID(&clsid);
		if (sc != S_OK)
			AfxThrowOleException(sc);
		//set clsid
		reobject.clsid = clsid;
		//can be selected
		reobject.cp = REO_CP_SELECTION;
		//content, but not static
		reobject.dvaspect = DVASPECT_CONTENT;
		//goes in the same line of text line
		reobject.dwFlags = REO_BELOWBASELINE; //REO_RESIZABLE |
		reobject.dwUser = 0;
		//the very object
		reobject.poleobj = m_lpObject;
		//client site contain the object
		reobject.polesite = m_lpClientSite;
		//the storage 
		reobject.pstg = m_lpStorage;
		
		SIZEL sizel;
		sizel.cx = sizel.cy = 0;
		reobject.sizel = sizel;
		HWND hWndRT = this->m_hWnd;
		//Sel all text
//		::SendMessage(hWndRT, EM_SETSEL, 0, -1);
//		DWORD dwStart, dwEnd;
//		::SendMessage(hWndRT, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
//		::SendMessage(hWndRT, EM_SETSEL, dwEnd+1, dwEnd+1);
		//Insert after the line of text
		GetIRichEditOle()->InsertObject(&reobject);
		::SendMessage(hWndRT, EM_SCROLLCARET, (WPARAM)0, (LPARAM)0);
		VARIANT_BOOL ret;
		//do frame changing
		ret = m_lpAnimator->TriggerFrameChange();
		//show it
		m_lpObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, m_lpClientSite, 0, m_hWnd, NULL);
		m_lpObject->DoVerb(OLEIVERB_SHOW, NULL, m_lpClientSite, 0, m_hWnd, NULL);
		
		//redraw the window to show animation
		RedrawWindow();

		if (m_lpClientSite)
		{
			m_lpClientSite->Release();
			m_lpClientSite = NULL;
		}
		if (m_lpObject)
		{
			m_lpObject->Release();
			m_lpObject = NULL;
		}
		if (m_lpStorage)
		{
			m_lpStorage->Release();
			m_lpStorage = NULL;
		}
		
		SysFreeString(path);
	}
	catch( _com_error e )
	{
		AfxMessageBox(e.ErrorMessage());
		::CoUninitialize();	
	}
}