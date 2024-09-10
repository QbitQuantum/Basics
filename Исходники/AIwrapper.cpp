static void vprint(int x, int y, int w, char *format, va_list va)
{
  HDC dc = GetDC(wnd);
  RECT rc;
  rc.top = y;
  rc.bottom = y+16;
  rc.left = x - w/2;
  rc.right = rc.left + w;
  char buf[128];
  int n = vsprintf(buf, format, va);
  SetTextAlign(dc, TA_CENTER);
  ExtTextOutA(dc, x, y, ETO_OPAQUE, &rc, buf, n, 0);
  ReleaseDC(wnd, dc);
}