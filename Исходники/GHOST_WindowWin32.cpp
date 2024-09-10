GHOST_WindowWin32::GHOST_WindowWin32(GHOST_SystemWin32 *system,
        const STR_String &title,
        GHOST_TInt32 left,
        GHOST_TInt32 top,
        GHOST_TUns32 width,
        GHOST_TUns32 height,
        GHOST_TWindowState state,
        GHOST_TDrawingContextType type,
	bool wantStereoVisual,
	bool alphaBackground,
        GHOST_TUns16 wantNumOfAASamples,
        GHOST_TEmbedderWindowID parentwindowhwnd,
        bool is_debug)
    : GHOST_Window(width, height, state,
                   wantStereoVisual, false, wantNumOfAASamples),
      m_inLiveResize(false),
      m_system(system),
      m_hDC(0),
      m_hasMouseCaptured(false),
      m_hasGrabMouse(false),
      m_nPressedButtons(0),
      m_customCursor(0),
      m_wantAlphaBackground(alphaBackground),
      m_wintab(NULL),
      m_tabletData(NULL),
      m_tablet(0),
      m_maxPressure(0),
      m_normal_state(GHOST_kWindowStateNormal),
	  m_user32(NULL),
      m_parentWindowHwnd(parentwindowhwnd),
      m_debug_context(is_debug)
{
	if (state != GHOST_kWindowStateFullScreen) {
		RECT rect;
		MONITORINFO monitor;
		GHOST_TUns32 tw, th;

#ifndef _MSC_VER
		int cxsizeframe = GetSystemMetrics(SM_CXSIZEFRAME);
		int cysizeframe = GetSystemMetrics(SM_CYSIZEFRAME);
#else
		// MSVC 2012+ returns bogus values from GetSystemMetrics, bug in Windows
		// http://connect.microsoft.com/VisualStudio/feedback/details/753224/regression-getsystemmetrics-delivers-different-values
		RECT cxrect = {0, 0, 0, 0};
		AdjustWindowRectEx(&cxrect, WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_THICKFRAME | WS_DLGFRAME, FALSE, 0);

		int cxsizeframe = abs(cxrect.bottom);
		int cysizeframe = abs(cxrect.left);
#endif

		width += cxsizeframe * 2;
		height += cysizeframe * 2 + GetSystemMetrics(SM_CYCAPTION);

		rect.left = left;
		rect.right = left + width;
		rect.top = top;
		rect.bottom = top + height;

		monitor.cbSize = sizeof(monitor);
		monitor.dwFlags = 0;

		// take taskbar into account
		GetMonitorInfo(MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST), &monitor);

		th = monitor.rcWork.bottom - monitor.rcWork.top;
		tw = monitor.rcWork.right - monitor.rcWork.left;

		if (tw < width) {
			width = tw;
			left = monitor.rcWork.left;
		}
		else if (monitor.rcWork.right < left + (int)width)
			left = monitor.rcWork.right - width;
		else if (left < monitor.rcWork.left)
			left = monitor.rcWork.left;

		if (th < height) {
			height = th;
			top = monitor.rcWork.top;
		}
		else if (monitor.rcWork.bottom < top + (int)height)
			top = monitor.rcWork.bottom - height;
		else if (top < monitor.rcWork.top)
			top = monitor.rcWork.top;

		int wintype = WS_OVERLAPPEDWINDOW;
		if (m_parentWindowHwnd != 0) {
			wintype = WS_CHILD;
			GetWindowRect((HWND)m_parentWindowHwnd, &rect);
			left = 0;
			top = 0;
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}

		wchar_t *title_16 = alloc_utf16_from_8((char *)(const char *)title, 0);
		m_hWnd = ::CreateWindowW(
			s_windowClassName,          // pointer to registered class name
			title_16,                   // pointer to window name
			wintype,                    // window style
			left,                       // horizontal position of window
			top,                        // vertical position of window
			width,                      // window width
			height,                     // window height
			(HWND)m_parentWindowHwnd,  // handle to parent or owner window
			0,                          // handle to menu or child-window identifier
			::GetModuleHandle(0),       // handle to application instance
			0);                         // pointer to window-creation data
		free(title_16);
	}
	else {
		wchar_t *title_16 = alloc_utf16_from_8((char *)(const char *)title, 0);
		m_hWnd = ::CreateWindowW(
		    s_windowClassName,          // pointer to registered class name
		    title_16,                   // pointer to window name
		    WS_POPUP | WS_MAXIMIZE,     // window style
		    left,                       // horizontal position of window
		    top,                        // vertical position of window
		    width,                      // window width
		    height,                     // window height
		    HWND_DESKTOP,               // handle to parent or owner window
		    0,                          // handle to menu or child-window identifier
		    ::GetModuleHandle(0),       // handle to application instance
		    0);                         // pointer to window-creation data
		free(title_16);
	}
	if (m_hWnd) {
		// Register this window as a droptarget. Requires m_hWnd to be valid.
		// Note that OleInitialize(0) has to be called prior to this. Done in GHOST_SystemWin32.
		m_dropTarget = new GHOST_DropTargetWin32(this, m_system);
		if (m_dropTarget) {
			::RegisterDragDrop(m_hWnd, m_dropTarget);
		}

		// Store a pointer to this class in the window structure
		::SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR) this);

		if (!m_system->m_windowFocus) {
			// Lower to bottom and don't activate if we don't want focus
			::SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		}

		// Store the device context
		m_hDC = ::GetDC(m_hWnd);

		GHOST_TSuccess success = setDrawingContextType(type);

		if (success) {
			// Show the window
			int nCmdShow;
			switch (state) {
				case GHOST_kWindowStateMaximized:
					nCmdShow = SW_SHOWMAXIMIZED;
					break;
				case GHOST_kWindowStateMinimized:
					nCmdShow = (m_system->m_windowFocus) ? SW_SHOWMINIMIZED : SW_SHOWMINNOACTIVE;
					break;
				case GHOST_kWindowStateNormal:
				default:
					nCmdShow = (m_system->m_windowFocus) ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE;
					break;
			}

			::ShowWindow(m_hWnd, nCmdShow);
#ifdef WIN32_COMPOSITING
			if (alphaBackground && parentwindowhwnd == 0) {

				HRESULT hr = S_OK;

				// Create and populate the Blur Behind structure
				DWM_BLURBEHIND bb = { 0 };

				// Enable Blur Behind and apply to the entire client area
				bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
				bb.fEnable = true;
				bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);

				// Apply Blur Behind
				hr = DwmEnableBlurBehindWindow(m_hWnd, &bb);
				DeleteObject(bb.hRgnBlur);
			}
#endif
			// Force an initial paint of the window
			::UpdateWindow(m_hWnd);
		}
		else {
			//invalidate the window
			::DestroyWindow(m_hWnd);
			m_hWnd = NULL;
		}
	}

	if (parentwindowhwnd != 0) {
		RAWINPUTDEVICE device = {0};
		device.usUsagePage  = 0x01; /* usUsagePage & usUsage for keyboard*/
		device.usUsage      = 0x06; /* http://msdn.microsoft.com/en-us/windows/hardware/gg487473.aspx */
		device.dwFlags |= RIDEV_INPUTSINK; // makes WM_INPUT is visible for ghost when has parent window
		device.hwndTarget = m_hWnd;
		RegisterRawInputDevices(&device, 1, sizeof(device));
	}

	m_wintab = ::LoadLibrary("Wintab32.dll");
	if (m_wintab) {
		GHOST_WIN32_WTInfo fpWTInfo = (GHOST_WIN32_WTInfo) ::GetProcAddress(m_wintab, "WTInfoA");
		GHOST_WIN32_WTOpen fpWTOpen = (GHOST_WIN32_WTOpen) ::GetProcAddress(m_wintab, "WTOpenA");

		// Let's see if we can initialize tablet here.
		// Check if WinTab available by getting system context info.
		LOGCONTEXT lc = { 0 };
		lc.lcOptions |= CXO_SYSTEM;
		if (fpWTInfo && fpWTInfo(WTI_DEFSYSCTX, 0, &lc)) {
			// Now init the tablet
			/* The maximum tablet size, pressure and orientation (tilt) */
			AXIS TabletX, TabletY, Pressure, Orientation[3];

			// Open a Wintab context

			// Open the context
			lc.lcPktData = PACKETDATA;
			lc.lcPktMode = PACKETMODE;
			lc.lcOptions |= CXO_MESSAGES;
			lc.lcMoveMask = PACKETDATA;

			/* Set the entire tablet as active */
			fpWTInfo(WTI_DEVICES, DVC_X, &TabletX);
			fpWTInfo(WTI_DEVICES, DVC_Y, &TabletY);

			/* get the max pressure, to divide into a float */
			BOOL pressureSupport = fpWTInfo(WTI_DEVICES, DVC_NPRESSURE, &Pressure);
			if (pressureSupport)
				m_maxPressure = Pressure.axMax;
			else
				m_maxPressure = 0;

			/* get the max tilt axes, to divide into floats */
			BOOL tiltSupport = fpWTInfo(WTI_DEVICES, DVC_ORIENTATION, &Orientation);
			if (tiltSupport) {
				/* does the tablet support azimuth ([0]) and altitude ([1]) */
				if (Orientation[0].axResolution && Orientation[1].axResolution) {
					/* all this assumes the minimum is 0 */
					m_maxAzimuth = Orientation[0].axMax;
					m_maxAltitude = Orientation[1].axMax;
				}
				else {  /* no so dont do tilt stuff */
					m_maxAzimuth = m_maxAltitude = 0;
				}
			}

			if (fpWTOpen) {
				// The Wintab spec says we must open the context disabled if we are using cursor masks.
				m_tablet = fpWTOpen(m_hWnd, &lc, FALSE);
				if (m_tablet) {
					m_tabletData = new GHOST_TabletData();
					m_tabletData->Active = GHOST_kTabletModeNone;
				}

				GHOST_WIN32_WTEnable fpWTEnable = (GHOST_WIN32_WTEnable) ::GetProcAddress(m_wintab, "WTEnable");
				if (fpWTEnable) {
					fpWTEnable(m_tablet, TRUE);
				}
			}
		}
	}
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (LPVOID *)&m_Bar);
}