cglApp::cglApp(int nW, int nH, void* hInst, int nCmdShow) 
  : m_hWnd(NULL)
  , m_hInstance(hInst)
  , m_nClearColor(0xFF007F00)
  , m_pD3D(NULL)
  , m_nFrameCount(0)
  , m_rPrevTime(0.0f)
{
  // Register window class
  WNDCLASS wndClass;
  wndClass.style          = 0;
  wndClass.lpfnWndProc    = D3DBaseAppCallback;
  wndClass.cbClsExtra     = 0;
  wndClass.cbWndExtra     = 4;
  wndClass.hInstance      = HINSTANCE(hInst);
  wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wndClass.hbrBackground  = HBRUSH(GetStockObject(WHITE_BRUSH));
  wndClass.lpszMenuName   = NULL;
  wndClass.lpszClassName  = s_windowClassName;
  RegisterClass(&wndClass);

  // Adjust window in regard to client area nW x nH
  int  nStyle = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  RECT rRect;
  SetRect(&rRect, 0, 0, nW, nH);
  AdjustWindowRect(&rRect, nStyle, TRUE);
  
  // Create main window
  m_hWnd = NULL;
  m_hWnd = (void*)CreateWindow(s_windowClassName, getWindowText(), nStyle,
                               CW_USEDEFAULT, CW_USEDEFAULT, 
                               (rRect.right - rRect.left), (rRect.bottom - rRect.top),
                               NULL, NULL, HINSTANCE(hInst), NULL);
  if (m_hWnd == NULL)
    return;
    
  // Set pointer
  SetWindowLong(HWND(m_hWnd), 0, LONG(this));

  // Show window
  ShowWindow(HWND(m_hWnd), nCmdShow);
  UpdateWindow(HWND(m_hWnd));
  
  // We need to determine the BPP of desktop
  HDC hDC = GetDC(HWND(m_hWnd));            // Get DC of desktop
  int nBPP = GetDeviceCaps(hDC, BITSPIXEL); // Retrieve BPP
  ReleaseDC(HWND(m_hWnd), hDC);             // Release DC handle

  // Create our D3D class
  cglD3D::CreateParams params;
  params.hWnd    = m_hWnd;
  params.nBPP    = (nBPP == 32) ? cglD3D::BPP_32 : cglD3D::BPP_16;
  params.nWidth  = nW;
  params.nHeight = nH;
  m_pD3D = new cglD3D(params);
  // Check creation result
  if (m_pD3D == NULL || m_pD3D->isFailed())
    return;

  // Init random generator
  srand(0);
}