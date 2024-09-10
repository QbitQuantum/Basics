bool csGraphics2DOpenGL::Open ()
{
  if (is_open) return true;

  csRef<iVerbosityManager> verbosemgr (
    csQueryRegistry<iVerbosityManager> (object_reg));
  if (verbosemgr) 
    detector.SetVerbose (verbosemgr->Enabled ("renderer.windows.gldriver"));
  
  // create the window.
  if (FullScreen)
  {
    SwitchDisplayMode (false);
  }

  int pixelFormat = -1;
  csGLPixelFormatPicker picker (this);
  /*
    Check if the WGL pixel format check should be used at all.
    It appears that some drivers take "odd" choices when using the WGL
    pixel format path (e.g. returning Accum-capable formats even if none
    was requested).
   */
  bool doWGLcheck = false;
  {
    GLPixelFormat format;
    if (picker.GetNextFormat (format))
    {
      doWGLcheck = (format[glpfvMultiSamples] != 0);
      picker.Reset ();
    }
  }
  if (doWGLcheck)
    pixelFormat = FindPixelFormatWGL (picker);

  m_bActivated = true;

  int wwidth = fbWidth;
  int wheight = fbHeight;
  DWORD exStyle = 0;
  DWORD style = WS_POPUP | WS_SYSMENU;
  int xpos = 0;
  int ypos = 0;
  if (FullScreen)
  {
    /*exStyle |= WS_EX_TOPMOST;*/
  }
  else
  {
    style |= WS_CAPTION | WS_MINIMIZEBOX;
    if (AllowResizing) 
      style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    
    wwidth += 2 * GetSystemMetrics (SM_CXFIXEDFRAME);
    wheight += 2 * GetSystemMetrics (SM_CYFIXEDFRAME) + GetSystemMetrics (SM_CYCAPTION);
    xpos = (GetSystemMetrics (SM_CXSCREEN) - wwidth) / 2;
    ypos = (GetSystemMetrics (SM_CYSCREEN) - wheight) / 2;
  }

  m_hWnd = m_piWin32Assistant->CreateCSWindow (this, exStyle, style,
    xpos, ypos, wwidth, wheight);

  if (!m_hWnd)
    SystemFatalError (L"Cannot create Crystal Space window", GetLastError());

  SetTitle (win_title);
  
  // Subclass the window
  if (IsWindowUnicode (m_hWnd))
  {
    m_OldWndProc = (WNDPROC)SetWindowLongPtrW (m_hWnd, GWLP_WNDPROC, 
      (LONG_PTR) WindowProc);
    SetWindowLongPtrW (m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
  }
  else
  {
    m_OldWndProc = (WNDPROC)SetWindowLongPtrA (m_hWnd, GWLP_WNDPROC, 
      (LONG_PTR) WindowProc);
    SetWindowLongPtrA (m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
  }

  hDC = GetDC (m_hWnd);
  if (pixelFormat == -1)
  {
    picker.Reset();
    pixelFormat = FindPixelFormatGDI (hDC, picker);
  }

  PIXELFORMATDESCRIPTOR pfd;
  if (DescribePixelFormat (hDC, pixelFormat, 
    sizeof(PIXELFORMATDESCRIPTOR), &pfd) == 0)
    SystemFatalError (L"DescribePixelFormat failed.", GetLastError());

  if (SetPixelFormat (hDC, pixelFormat, &pfd) != TRUE)
  {
    HRESULT spfErr = (HRESULT)GetLastError();
    SystemFatalError (L"SetPixelFormat failed.", spfErr);
  }

  currentFormat[glpfvColorBits] = pfd.cColorBits;
  currentFormat[glpfvAlphaBits] = pfd.cAlphaBits;
  currentFormat[glpfvDepthBits] = pfd.cDepthBits;
  currentFormat[glpfvStencilBits] = pfd.cStencilBits;
  currentFormat[glpfvAccumColorBits] = pfd.cAccumBits;
  currentFormat[glpfvAccumAlphaBits] = pfd.cAccumAlphaBits;

  Depth = pfd.cColorBits; 

  hardwareAccelerated = !(pfd.dwFlags & PFD_GENERIC_FORMAT) ||
    (pfd.dwFlags & PFD_GENERIC_ACCELERATED);

  hGLRC = wglCreateContext (hDC);
  wglMakeCurrent (hDC, hGLRC);

  UpdateWindow (m_hWnd);
  ShowWindow (m_hWnd, m_nCmdShow);
  SetForegroundWindow (m_hWnd);
  SetFocus (m_hWnd);
  
  /* Small hack to emit "no HW acceleration" message on both GDI Generic and
   * sucky Direct3D default OpenGL */
  hardwareAccelerated &= 
    (strncmp ((char*)glGetString (GL_VENDOR), "Microsoft", 9) != 0);
  if (!hardwareAccelerated)
  {
    Report (CS_REPORTER_SEVERITY_WARNING,
      "No hardware acceleration!");
  }

  detector.DoDetection (m_hWnd, hDC);
  Report (CS_REPORTER_SEVERITY_NOTIFY,
    "GL driver: %s %s", detector.GetDriverDLL(), 
    detector.GetDriverVersion() ? detector.GetDriverVersion() : 
      "<version unknown>");

  if (FullScreen)
  {
    /* 
     * from the Windows Shell docs:
     * "It is possible to cover the taskbar by explicitly setting the size 
     * of the window rectangle equal to the size of the screen with 
     * SetWindowPos."
     */
    SetWindowPos (m_hWnd, CS_WINDOW_Z_ORDER, 0, 0, fbWidth, fbHeight, 0);
  }

  if (!csGraphics2DGLCommon::Open ())
    return false;

  ext.InitWGL_EXT_swap_control (hDC);

  if (ext.CS_WGL_EXT_swap_control)
  {
    ext.wglSwapIntervalEXT (vsync ? 1 : 0);
    vsync = (ext.wglGetSwapIntervalEXT() != 0);
    Report (CS_REPORTER_SEVERITY_NOTIFY,
      "VSync is %s.", 
      vsync ? "enabled" : "disabled");
  }

  return true;
}