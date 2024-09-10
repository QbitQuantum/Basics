DWORD CDOPPEngineDlg::threadLoop()
{
    bool   bCapture = false;

    bCapture = (m_pShowWinCheckBox->GetCheck() == BST_CHECKED);

    // Create window with ogl context to load extensions
    WNDCLASSEX		wndclass;
	const LPCWSTR   cClassName   = _T("OGL");
	const LPCWSTR	cWindowName  = _T("DOPP Capture");

	// Register WindowClass for GL window
	wndclass.cbSize         = sizeof(WNDCLASSEX);
	wndclass.style          = CS_OWNDC;
	wndclass.lpfnWndProc    = WndProc;
	wndclass.cbClsExtra     = 0;
	wndclass.cbWndExtra     = 0;
	wndclass.hInstance      = (HINSTANCE)GetModuleHandle(NULL);
	wndclass.hIcon		    = (HICON)LoadImage((HINSTANCE)AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, NULL); 
	wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground  = NULL;
	wndclass.lpszMenuName   = NULL;
	wndclass.lpszClassName  = cClassName;
	wndclass.hIconSm		= (HICON)LoadImage((HINSTANCE)AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, NULL); 

	if (!RegisterClassEx(&wndclass))
		return FALSE;
     
    GLWindow* pWin = new GLWindow("DOPP Capture", "OGL");

    pWin->create(g_uiWindowWidth, g_uiWindowHeight, false, false, false, true);

    // GLWindow::create context will destroy the initial window and create a new one. To avoid that
    // WndProc emits a PostQuitMessage a pointer to the initial window is passed. If this pointer is 
    // valid we know that it is the temporary window and should not emit PostQuitMessage.
    SetWindowLongPtr(pWin->getWnd(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWin));

    pWin->createContext(0);

    GLDOPPEngine* pEngine = NULL;

    switch (m_uiEffectSelection)
    {
        case COLOR_INVERT:
            pEngine = new GLDOPPColorInvert;
            break;

        case EDGE_FILTER:
            pEngine = new GLDOPPEdgeFilter;
            break;

        case DISTORT_EFFECT:
            pEngine = new GLDOPPDistort;
            break;

        case ROTATE_DESKTOP:
            pEngine = new GLDOPPRotate;
            break;

        default:
            pEngine = new GLDOPPEngine;
            break;
    }

    // m_uiDesktopSelection is the id of the selected element in the Combo Box
    // Need to add 1 to get the desktop id as shown in CCC
    if (!pEngine->initDOPP(m_uiDesktopSelection + 1))
    {
        // prevent thread loop to start due to error
        m_bEngineRunning = false;
    }



    if (!pEngine->initEffect())
    {
        // prevent thread loop to start due to error
        m_bEngineRunning = false;
    }


	if (m_bEngineRunning && m_uiEffectSelection == ROTATE_DESKTOP)
    {
        GLDOPPRotate* pRot = dynamic_cast<GLDOPPRotate*>(pEngine);
        pRot->setRotation((float)m_uiRotationAngle);
    }



    if (bCapture && m_bEngineRunning)
    {
        // Open window only if this option was checked in the GUI
        pWin->open();
    }

    // Enable SW mouse
    SystemParametersInfo(SPI_SETMOUSETRAILS, 2, 0, 0);

    MSG mMsg;

    while(m_bEngineRunning)
    {
        pEngine->processDesktop();
        
        if (bCapture)
        {
            // Blit FBO of DOPPEngine into the window
            glViewport(0, 0, g_uiWindowWidth, g_uiWindowHeight);

            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, pEngine->getPresentBuffer());

            glBlitFramebuffer(0, pEngine->getDesktopHeight(), pEngine->getDesktopWidth(), 0, 0, 0, g_uiWindowWidth, g_uiWindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            pWin->swapBuffers();

            if (PeekMessage(&mMsg, NULL, 0, 0, PM_REMOVE))
		    {
			    if (mMsg.message == WM_QUIT)
			    {
				    m_bEngineRunning = false;
			    }
                else
			    {
				    TranslateMessage(&mMsg);
				    DispatchMessage(&mMsg);
			    }
		    }
        }
    } 

    // Disable SW mouse
    SystemParametersInfo(SPI_SETMOUSETRAILS, 1, 0, 0);

    delete pEngine;

    delete pWin;

    ::UnregisterClass(cClassName, NULL);

    return 0;
}