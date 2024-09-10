	BrowserControlPane::BrowserControlPane(HWND hpwnd, HINSTANCE hInstance, RECT* ipBoundRect)
		: hparentwnd(hpwnd)
		// 콘트롤 폐인 없음... : ControlPane( ipBoundRect )
	{
		HRESULT					err;
		RECT					bounds;
		TCHAR*					sClassName = TEXT("NexonADBrowser");
		WNDCLASS				windowClass;
		CComPtr< IOleObject >	pOleObject;
		RECT					clientRECT;

		ASSERT(ipBoundRect != NULL);

		this->isActivated = TRUE;
		this->allowNewWindow = TRUE;
		this->showScrollBar = FALSE;
		this->sLimitToInside[0] = 0;
		this->timeout = kInitialTimeout;
		this->keyHandling = kHandleAndDontPass;
		this->mouseHandling = kHandleAndDontPass;
		// this->initialLoading = TRUE;
		this->initialLoading = FALSE;

		bounds = *ipBoundRect;

		// create window

		windowClass.style = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW | CS_DBLCLKS | CS_OWNDC;
		windowClass.lpfnWndProc = (WNDPROC)BrowserControlPane::WindowProcEntry;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = NULL;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH) ::GetStockObject(BLACK_BRUSH);
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = sClassName;
		RegisterClass(&windowClass);

		ASSERT(s_pInCreation == NULL);
		s_pInCreation = this;
		this->hwnd = CreateWindowEx(0, sClassName, _T(""), WS_CHILD | WS_CLIPSIBLINGS,
			bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top,
			hparentwnd, (HMENU)NULL, hInstance, (LPVOID)NULL);
		::SetWindowLongA(this->hwnd, GWL_USERDATA, (DWORD) this);
		s_pInCreation = NULL;

		// create WebBrowser control
		err = ::CoCreateInstance(CLSID_WebBrowser, NULL, CLSCTX_INPROC, IID_IOleObject, (void**)&pOleObject);
		ASSERT(SUCCEEDED(err));
		if (SUCCEEDED(err))
		{
			err = pOleObject->SetClientSite(this);
			ASSERT(SUCCEEDED(err));
		}

		// in-place actvivate the control
		if (SUCCEEDED(err))
		{
			::SetRect(&clientRECT, 0, 0, bounds.right - bounds.left, bounds.bottom - bounds.top);
			err = pOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, this, 0, this->hwnd, &clientRECT);
			ASSERT(SUCCEEDED(err));
		}

		// get the browser control pointer
		if (SUCCEEDED(err))
		{
			this->pBrowser = pOleObject;
			ASSERT(this->pBrowser != NULL);
		}

		// setup connection for events
		if (SUCCEEDED(err))
		{
			err = AtlAdvise(this->pBrowser, (IOleClientSite*) this, DIID_DWebBrowserEvents2, &this->connCookie);
			ASSERT(SUCCEEDED(err));
		}

		// set size
		if (SUCCEEDED(err))
		{
			CComQIPtr<IOleInPlaceObject, &IID_IOleInPlaceObject>	pInPlaceObject(this->pBrowser);

			ASSERT(pInPlaceObject != NULL);
			err = pInPlaceObject->SetObjectRects(&clientRECT, &clientRECT);
			ASSERT(SUCCEEDED(err));
		}

		if (FAILED(err))
		{
			if (this->pBrowser != NULL)
			{
				err = AtlUnadvise(this->pBrowser, DIID_DWebBrowserEvents2, this->connCookie);
				ASSERT(SUCCEEDED(err));
			}

			this->pBrowser.Release();
			::OleUninitialize();
			::DestroyWindow(this->hwnd);
			this->hwnd = NULL;
		}
	}