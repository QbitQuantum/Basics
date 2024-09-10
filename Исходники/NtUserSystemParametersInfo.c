HWND
CreateTestWindow()
{
	WNDCLASSA wc;

	wc.style = 0;
	wc.lpfnWndProc = DefWindowProcA;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "testclass";

	RegisterClassA(&wc);
	return CreateWindowA("testclass",
	                     "testwnd",
	                     WS_VISIBLE,
	                     0,
	                     0,
	                     50,
	                     30,
	                     NULL,
	                     NULL,
	                     g_hInstance,
	                     0);
}