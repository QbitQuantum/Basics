HWND MetaTaskbar::createTaskSw(ULONG id, ULONG state)
{
vnclog.Print(1, _T("%s: id=0x%X state=0x%X\n"), __FUNCTION__, id, state);
    char className[TaskSwClassNameLen];
    sprintf(className, TaskSwClassNameTemplate, id);

	// Create a dummy window to handle taskbar messages
	WNDCLASSEX wndclass;
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= 0;
	wndclass.lpfnWndProc	= MetaTaskbar::WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= m_pApp->m_instance;
	wndclass.hIcon			= NULL;
	wndclass.hCursor		= NULL;
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= (const char *) NULL;
	wndclass.lpszClassName	= className;
	wndclass.hIconSm		= NULL;
	RegisterClassEx(&wndclass);

    HWND hwnd = CreateWindow(className,
                className,
                WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
				0, 0, 0, 0,
				NULL,
				NULL,
				m_pApp->m_instance,
				NULL);

    if (hwnd == NULL) {
        vnclog.Print(0, TEXT("MetaTaskbar : ERROR : failed to create task switch window\n"));
        return NULL;
    }

    HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
    SetWindowRgn(hwnd, hRgn, FALSE);     // set this window transparent

	SetWindowLong(hwnd, GWL_USERDATA, (LONG) this);

    HMENU hsysmenu = GetSystemMenu(hwnd, FALSE);
    if (hsysmenu == NULL) {
        vnclog.Print(0, TEXT("MetaTaskbar : ERROR : failed to get system menu of task switch window\n"));
    } else {
        RemoveMenu(hsysmenu, SC_SIZE, MF_BYCOMMAND);
        RemoveMenu(hsysmenu, SC_MOVE, MF_BYCOMMAND);
    }

    taskbarControl(hwnd, TASKBAR_ADD);

    TaskSwState tswstate;
    tswstate.hwnd  = hwnd;
    tswstate.state = state;
	omni_mutex_lock l(m_taskSwitchesLock);
    m_taskSwitches.insert(IdStateMap::value_type(id, tswstate));

    if (state & rfbWindowStateMinimized)
        ShowWindow(hwnd, SW_MINIMIZE);
    else if (state & rfbWindowStateMaximized)
        ShowWindow(hwnd, SW_MAXIMIZE);

    return hwnd;
}