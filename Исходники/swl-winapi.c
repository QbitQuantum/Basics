SWL_API enum swl_result swl_platform_allocate(const char *title, unsigned int width, unsigned int height, swl_window_t *window, swl_display_t *display)
{
	WNDCLASS swc;
	ATOM register_class;
	RECT rect;
	HDC hdc;
	DWORD style = WS_CAPTION | WS_VISIBLE | WS_SYSMENU;

	if(swl.resizable)
		style |= WS_SIZEBOX;

	swc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	swc.lpfnWndProc = wnd_proc;
	swc.cbClsExtra = 0;
	swc.cbWndExtra = 0;
	swc.hInstance = 0;
	swc.hIcon = 0;
	swc.hCursor = LoadCursor(NULL, IDC_ARROW);
	swc.lpszMenuName = 0;
	swc.hbrBackground = 0;
	swc.lpszClassName = "RenderFrame";

	register_class = RegisterClass(&swc);

	if (!register_class)
		return SWLR_ERROR_BACKEND_WINAPI_REGISTER_CLASS;

	SetRect(&rect, 0, 0, width, height);
	
	AdjustWindowRectEx(&rect, style, false, 0);
	
	window_handle = CreateWindow("RenderFrame", title, style, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, 0);
	
	if(window_handle == 0)
		return SWLR_ERROR_BACKEND_WINAPI_HANDLE;
	
	hdc = GetDC(window_handle);
	
	if (!hdc)
		return SWLR_ERROR_BACKEND_WINAPI_DEVICE;

	*display = hdc;
	*window = window_handle;
	
	RAWINPUTDEVICE mouse;
	mouse.usUsagePage = 1;
	mouse.usUsage = 2;
	mouse.dwFlags = 0;
	mouse.hwndTarget = window_handle;
	
	if(RegisterRawInputDevices(&mouse, 1, sizeof(mouse)) == FALSE)
		return SWLR_ERROR_BACKEND_WINAPI_RAW_INPUT;
	
	return SWLR_OK;
}