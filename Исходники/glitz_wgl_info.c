static void
_glitz_wgl_create_root_context (glitz_wgl_screen_info_t *screen_info)
{
    WNDCLASSEX wcl;
    ATOM klass;

    static PIXELFORMATDESCRIPTOR pfd = {
	sizeof (PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
	PFD_TYPE_RGBA,
	32,
	0, 0, 0,
	0, 0, 0,
	0, 0,
	0, 0, 0, 0, 0,
	0,
	0,
	0,
	PFD_MAIN_PLANE,
	0,
	0,
	0,
	0
    };

    int pixel_format;

    wcl.cbSize = sizeof (wcl);
    wcl.style = 0;
    wcl.lpfnWndProc = DefWindowProc;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hInstance = GetModuleHandle (NULL);
    wcl.hIcon = NULL;
    wcl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wcl.hbrBackground = NULL;
    wcl.lpszMenuName = NULL;
    wcl.lpszClassName = "glitz-wgl-root-window-class";
    wcl.hIconSm = NULL;

    klass = RegisterClassEx (&wcl);

    if (!klass) {
	exit (1);
    }

    screen_info->root_window =
	CreateWindowEx (0, (LPCTSTR) (DWORD) klass, "glitz-wgl-root-window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			100, 100,
			GetDesktopWindow (),
			NULL, GetModuleHandle (NULL), NULL);

    screen_info->root_dc = GetDC (screen_info->root_window);

    pixel_format = ChoosePixelFormat (screen_info->root_dc, &pfd);

    if (pixel_format != 0) {
	SetPixelFormat (screen_info->root_dc, pixel_format, &pfd);

	screen_info->root_context = wglCreateContext (screen_info->root_dc);

	wglMakeCurrent (screen_info->root_dc, screen_info->root_context);
    } else {
	screen_info->root_context = NULL;
    }
}