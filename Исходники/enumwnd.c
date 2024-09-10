int WINAPI
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine,
	int nCmdShow)
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  wc.lpszClassName = CLASS_NAME;
  wc.lpfnWndProc = MainWndProc;
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, (LPCTSTR)IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, (LPCTSTR)IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
  wc.lpszMenuName = NULL;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  if (RegisterClass(&wc) == 0)
    {
      _ftprintf ( stderr, _T("RegisterClass failed (last error 0x%lX)\n"),
	      GetLastError());
      return(1);
    }

  hWnd = CreateWindow(CLASS_NAME,
		      APP_NAME,
		      WS_OVERLAPPEDWINDOW,
		      0,
		      0,
		      CW_USEDEFAULT,
		      CW_USEDEFAULT,
		      NULL,
		      NULL,
		      hInstance,
		      NULL);
  if (hWnd == NULL)
    {
      _ftprintf ( stderr, _T("CreateWindow failed (last error 0x%lX)\n"),
	      GetLastError());
      return(1);
    }

  tf = CreateFont (14, 0, 0, TA_BASELINE, FW_NORMAL, FALSE, FALSE, FALSE,
		    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		    DEFAULT_QUALITY, FIXED_PITCH|FF_DONTCARE, _T("Timmons"));

  hbrBackground = CreateSolidBrush ( RGB(192,192,192) );

  ShowWindow ( hWnd, nCmdShow );

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  DeleteObject(hbrBackground);

  DeleteObject(tf);

  return msg.wParam;
}