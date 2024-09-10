void c_video::create(long width, long height, char *title, HINSTANCE hinst)
{
	WNDCLASSEX winclass;

	c_video::hinst = hinst;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = msg_proc;
	winclass.cbClsExtra	= 0;
	winclass.cbWndExtra	= 0;
	winclass.hInstance = hinst;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = "game";
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&winclass))
		throw c_error();		

	if(!(hwnd = CreateWindowEx(NULL, "game", title, WS_POPUP | WS_VISIBLE, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hinst, NULL)))
		throw c_error();
	
	if(FAILED(DirectDrawCreateEx(NULL, (void **)&direct_draw, IID_IDirectDraw7, NULL)))
		throw c_error("Could not create DirectDraw");

	if(FAILED(direct_draw->SetCooperativeLevel(hwnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX)))
		throw c_error("Could not set Cooperative Level");

	if(FAILED(direct_draw->SetDisplayMode(width, height, 8, 0, 0)))
		throw c_error("Could not create Video Mode: %ux%u 256 colours", width, height);

	DX_INIT_STRUCT(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	if(FAILED(direct_draw->CreateSurface(&ddsd, &display_mem, NULL)))
		throw c_error("Could not create Primary Display Buffer");

	c_image::create(width, height);
	c_image::header.create(width, height);

	c_pal::create(direct_draw);
	c_pal::set(display_mem);
}