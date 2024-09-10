  int
WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, PSTR szCmd, int iShow) {
  Nods.hHeap = GetProcessHeap();
  if (Nods.hHeap == NULL)
    repquit("Process memory error");
  signal(SIGINT, repsig);
  signal(SIGTERM, repsig);
  signal(SIGSEGV, repsig);
  InvalidateRect(0, 0, WM_ERASEBKGND);

  Nods.hwnd = GetDesktopWindow();
  const
   int waw = GetSystemMetrics(SM_CXSCREEN),
       wah = GetSystemMetrics(SM_CYSCREEN);

  Nods.source = GetDCEx(Nods.hwnd, NULL,
		   DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_CLIPCHILDREN);

  mknods(waw, wah);
  const int wah2 = Nods.nod_sum;                /* wah shrunk */
  Nods.context = CreateCompatibleDC(Nods.source);

  nod in,                                    /* plitka index */
      ips;                                   /* plitka size */
  int xpos, ypos;

  MSG msg;
  RECT Rect;
  unsigned char r, g, b, stdev;
  unsigned char const threshold = 15;
  HBRUSH hBrush;
  while (1) {
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT)
	break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      Sleep(5);
      in = Nods.nods_uniform[rand() % Nods.nod_sum_uniform];
      ips = Nods.nods[in];
      xpos = rand()%waw;
      xpos = xpos - xpos % ips;
      ypos = Nods.plitka_offset[in];
      SetRect(&Rect,
	      xpos,		ypos + (wah - wah2),
	      xpos + ips - 1,	ypos + ips + (wah - wah2) - 1);
      do {
	r = 0x55 + rand()%0xaa;
	g = 0x55 + rand()%0xaa;
	b = 0x55 + rand()%0xaa;
	stdev = (r + g + b) / 3;
      }
      while (
	     abs(r - stdev) <= threshold ||
	     abs(g - stdev) <= threshold ||
	     abs(b - stdev) <= threshold
	    );
      hBrush = CreateSolidBrush(RGB(r, g, b));
      FillRect(Nods.source, &Rect, hBrush);
      DeleteObject(hBrush);
    }
  }

  DeleteDC(Nods.context);
  DeleteDC(Nods.source);
  ReleaseDC(Nods.hwnd, Nods.source);
  xfree(Nods.nods);
  xfree(Nods.nods_uniform);
  xfree(Nods.plitka_offset);
  return 0;
}