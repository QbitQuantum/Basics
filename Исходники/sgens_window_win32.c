/**
 * sgens_window_show(): Show the VDP Layer Options window.
 * @param parent Parent window.
 */
void MDP_FNCALL sgens_window_show(void *parent)
{
	if (sgens_window)
	{
		// Sonic Gens window is already visible. Set focus.
		// TODO: Figure out how to do this.
		ShowWindow(sgens_window, SW_SHOW);
		return;
	}
	
	// Initialize the Win32 Unicode Translation Layer.
	w32u_init();
	
	sgens_window_child_windows_created = FALSE;
	
	// If no HINSTANCE was specified, use the main executable's HINSTANCE.
	if (!sgens_hInstance)
		sgens_hInstance = GetModuleHandle(NULL);
	
	if (sgens_wndclass.lpfnWndProc != sgens_window_wndproc)
	{
		// Create the window class.
		sgens_wndclass.style = 0;
		sgens_wndclass.lpfnWndProc = sgens_window_wndproc;
		sgens_wndclass.cbClsExtra = 0;
		sgens_wndclass.cbWndExtra = 0;
		sgens_wndclass.hInstance = sgens_hInstance;
		sgens_wndclass.hIcon = LoadIconA(sgens_hInstance, MAKEINTRESOURCE(IDI_SGENS));
		sgens_wndclass.hCursor = LoadCursorA(NULL, IDC_ARROW);
		sgens_wndclass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		sgens_wndclass.lpszMenuName = NULL;
		sgens_wndclass.lpszClassName = "mdp_misc_sgens_window";
		
		pRegisterClassU(&sgens_wndclass);
	}
	
	// Create the window.
	sgens_window = pCreateWindowU("mdp_misc_sgens_window", "Sonic Gens",
					WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION,
					CW_USEDEFAULT, CW_USEDEFAULT,
					SGENS_WINDOW_WIDTH, SGENS_WINDOW_HEIGHT,
					(HWND)parent, NULL, sgens_hInstance, NULL);
	
	// Window adjustment.
	gsft_win32_set_actual_window_size(sgens_window, SGENS_WINDOW_WIDTH, SGENS_WINDOW_HEIGHT);
	gsft_win32_center_on_window(sgens_window, (HWND)parent);
	
	// Update the current ROM type and information display.
	sgens_window_update_rom_type();
	sgens_window_update();
	
	UpdateWindow(sgens_window);
	ShowWindow(sgens_window, TRUE);
	
	// Register the window with MDP Host Services.
	sgens_host_srv->window_register(&mdp, sgens_window);
}