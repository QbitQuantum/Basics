/* Window message handle function */
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  INT i;
  HDC hDC;
  PAINTSTRUCT ps;
  static INT w, h;
  static BITMAP bm;
  static HBITMAP hBm, hBmLogo;
  static HDC hMemDC, hMemDCLogo;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hBmLogo = LoadImage(NULL, "GLOBE.BMP", IMAGE_BITMAP, 0, 0,
        LR_LOADFROMFILE);
    GetObject(hBmLogo, sizeof(bm), &bm);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCLogo = CreateCompatibleDC(hDC);
    SelectObject(hMemDCLogo, hBmLogo);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    Rectangle(hMemDC, 0, 0, w + 1, h + 1);
    /*
    BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight,
      hMemDCLogo, 0, 0, SRCCOPY);
    */
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, 0, 0, w, h,
      hMemDCLogo, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    DrawEye(hWnd, hMemDC, 100, 100, 50, 15);
    DrawEye(hWnd, hMemDC, 300, 200, 150, 30);
    DrawEye(hWnd, hMemDC, 100, 200, 50, 30);
    DrawEye(hWnd, hMemDC, 400, 200, 130, 30);
    DrawEye(hWnd, hMemDC, w / 2, h / 2, 80, 15);

    srand(59);
    for (i = 0; i < 30; i++)
      DrawEye(hWnd, hMemDC, rand() % 800, rand() % 700, 30, 8);

    SetBkMode(hMemDC, TRANSPARENT);
    SetTextColor(hMemDC, RGB(255, 0, 0));
    TextOut(hMemDC, 30, 30, "30!", 3);
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWinFunc' function */