/**
 * vlopt_window_show(): Show the VDP Layer Options window.
 * @param parent Parent window.
 */
void vlopt_window_show(void *parent)
{
	if (vlopt_window)
	{
		// VDP Layer Options window is already visible.
		// Set focus.
		// TODO
		return;
	}
	
	// Initialize the Win32 Unicode Translation Layer.
	w32u_init();
	
	vlopt_window_child_windows_created = FALSE;
	
	// If no HINSTANCE was specified, use the main executable's HINSTANCE.
	if (!vlopt_hInstance)
		vlopt_hInstance = pGetModuleHandleU(NULL);
	
	// Create the window class.
	if (vlopt_window_wndclass.lpfnWndProc != vlopt_window_wndproc)
	{
		vlopt_window_wndclass.style = 0;
		vlopt_window_wndclass.lpfnWndProc = vlopt_window_wndproc;
		vlopt_window_wndclass.cbClsExtra = 0;
		vlopt_window_wndclass.cbWndExtra = 0;
		vlopt_window_wndclass.hInstance = vlopt_hInstance;
		vlopt_window_wndclass.hIcon = LoadIconA(vlopt_hInstance, MAKEINTRESOURCE(IDI_VLOPT));
		vlopt_window_wndclass.hCursor = LoadCursorA(NULL, IDC_ARROW);
		vlopt_window_wndclass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		vlopt_window_wndclass.lpszMenuName = NULL;
		vlopt_window_wndclass.lpszClassName = "vlopt_window_wndclass";
		
		pRegisterClassU(&vlopt_window_wndclass);
	}
	
	// Create the window.
	vlopt_window = pCreateWindowU("vlopt_window_wndclass", "VDP Layer Options",
					WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION,
					CW_USEDEFAULT, CW_USEDEFAULT,
					DLU_X(VLOPT_WINDOW_WIDTH), DLU_Y(VLOPT_WINDOW_HEIGHT),
					(HWND)parent, NULL, vlopt_hInstance, NULL);
	
	// Window adjustment.
	gsft_win32_set_actual_window_size(vlopt_window, DLU_X(VLOPT_WINDOW_WIDTH), DLU_Y(VLOPT_WINDOW_HEIGHT));
	gsft_win32_center_on_window(vlopt_window, (HWND)parent);
	
	UpdateWindow(vlopt_window);
	ShowWindow(vlopt_window, TRUE);
	
	// Register the window with MDP Host Services.
	vlopt_host_srv->window_register(&mdp, vlopt_window);
}