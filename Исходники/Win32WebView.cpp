bool CWin32WebView::init(const char *pszUrl, 
						 cocos2d::CCRect screenFrame, 
						 const char *pszTitle, 
						 const char *pszNormalImg,
						 const char *pszPushImg)
{
	bool bRet = false;
	while (1)
	{
		if (OleInitialize(NULL) != S_OK)
		{
			break;
		}

		HINSTANCE hInstance = GetModuleHandle( NULL );
		WNDCLASS  wc;		// Windows Class Structure
		HWND hParent = CCDirector::sharedDirector()->getOpenGLView()->getHWnd();
		float scale = CC_CONTENT_SCALE_FACTOR();
		screenFrame.origin.x *= scale;
		screenFrame.origin.y *= scale;
		screenFrame.size.width *= scale;
		screenFrame.size.height *= scale;

		// Redraw On Size, And Own DC For Window.
		wc.style          = CS_HREDRAW|CS_HREDRAW;  
		wc.lpfnWndProc    = _WindowProcContainer;							// WndProc Handles Messages
		wc.cbClsExtra     = 0;                              // No Extra Window Data
		wc.cbWndExtra     = 0;								// No Extra Window Data
		wc.hInstance      = hInstance;						// Set The Instance
		wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );	// Load The Default Icon
		wc.hCursor        = LoadCursor( NULL, IDC_ARROW );	// Load The Arrow Pointer
		wc.hbrBackground  = NULL;                           // No Background Required For GL
		wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
		wc.lpszClassName  = WINDOW_CLASS_CONTAINER;  
		wc.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(86, 49, 10));



		if(!RegisterClass(&wc))
		{
			break;
		}

		m_hContainer = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	// Extended Style For The Window
			WINDOW_CLASS_CONTAINER,									// Class Name
			NULL,												// Window Title
			WS_CHILD,	// Defined Window Style
			(int)screenFrame.origin.x, (int)screenFrame.origin.y,								                // Window Position
			(int)screenFrame.size.width,                                                  // Window Width
			(int)screenFrame.size.height,                                                  // Window Height
			hParent,												// No Parent Window
			(HMENU)ID_BUTTON,												// No Menu
			hInstance,											// Instance
			NULL );

		if(m_hContainer == NULL)
		{		
			break;
		}

		screenFrame.origin.y = 0;
		screenFrame.origin.x = 0;
		// web view
		if (pszTitle && strlen(pszTitle) > 0)
		{
			int width, height;
			HBITMAP hNormal = bitmapWithPath(pszNormalImg, width, height);

			screenFrame.origin.y += height;
			screenFrame.size.height -= height;

			HWND hButton = CreateWindowA("Button",
				"Hello",
				BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_FLAT ,
				screenFrame.size.width - width,0,                                                    
				width, height,                                                  
				m_hContainer,
				(HMENU)ID_BUTTON,
				hInstance,
				NULL);
			LRESULT lr = SendMessage(hButton,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hNormal );

			int nFontHeight = 18 * scale;
			wchar_t* pszTemp = CharToWChar(pszTitle, CP_UTF8);
			HWND hStatic = CreateWindow(TEXT("Static"),
				LPCWSTR(pszTemp),
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				(screenFrame.size.width - 200)/2, (height - nFontHeight)/2,
				200,nFontHeight,
				m_hContainer,
				0,
				hInstance,
				0);
			delete []pszTemp;

			if (NULL == hStatic)
			{
				break;
			}

			HFONT hFont= CreateFontA (nFontHeight, 0, 0, 0, 
				FW_DONTCARE, 
				FALSE, 
				FALSE, 
				FALSE, 
				ANSI_CHARSET, 
				OUT_DEFAULT_PRECIS, 
				CLIP_DEFAULT_PRECIS, 
				DEFAULT_QUALITY, 
				DEFAULT_PITCH | FF_SWISS,
				"Arial");
			if (hFont)
			{
				SendMessage (hStatic, WM_SETFONT, WPARAM (hFont), TRUE);
			}
		}

		wc.style          = CS_HREDRAW|CS_HREDRAW;  
		wc.lpfnWndProc    = _WindowProcWebView;							// WndProc Handles Messages
		wc.cbClsExtra     = 0;                              // No Extra Window Data
		wc.cbWndExtra     = 0;								// No Extra Window Data
		wc.hInstance      = hInstance;						// Set The Instance
		wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );	// Load The Default Icon
		wc.hCursor        = LoadCursor( NULL, IDC_ARROW );	// Load The Arrow Pointer
		wc.hbrBackground  = NULL;                           // No Background Required For GL
		wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
		wc.lpszClassName  = WINDOW_CLASS_WEBVIEW;  

		if(!RegisterClass(&wc))
		{
			break;
		}

		m_hWebView = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	// Extended Style For The Window
			WINDOW_CLASS_WEBVIEW,									// Class Name
			NULL,												// Window Title
			WS_CHILD,	// Defined Window Style
			(int)screenFrame.origin.x, (int)screenFrame.origin.y,								                // Window Position
			(int)screenFrame.size.width,                                                  // Window Width
			(int)screenFrame.size.height,                                                  // Window Height
			m_hContainer,												// No Parent Window
			NULL,												// No Menu
			hInstance,											// Instance
			NULL );

		if(m_hWebView == NULL)
		{		
			break;
		}

		wchar_t* pszTemp = CharToWChar(pszUrl, CP_UTF8);
		DisplayHTMLPage(m_hWebView, pszTemp);
		delete []pszTemp;

		ShowWindow(m_hWebView, SW_SHOW);
		UpdateWindow(m_hWebView);

		ShowWindow(m_hContainer, SW_SHOW);
		UpdateWindow(m_hContainer);

		bRet = true;
		break;
	}
	if (!bRet)
	{
		close();
		OleUninitialize();
	}
	return bRet;
}