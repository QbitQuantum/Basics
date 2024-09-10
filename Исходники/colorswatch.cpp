void OnPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  BeginPaint(hwnd, &ps);
  RECT rc;
  GetClientRect(hwnd, &rc);
  COLORREF bg = (COLORREF)GetWindowLongPtr(hwnd, GWLP_USERDATA);
  SetDCBrushColor(ps.hdc, bg);
  FillRect(ps.hdc, &rc, GetStockBrush(DC_BRUSH));
  EndPaint(hwnd, &ps);
}