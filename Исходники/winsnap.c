/*
 * highlightWindowFrame
 *
 * Highlight (or unhighlight) the specified
 * window handle's frame.
 */
static void
highlightWindowFrame(HWND hWnd)
{
  HDC     hdc;
  RECT    rc;

  if (!IsWindow(hWnd))
    return;

  hdc = GetWindowDC(hWnd);
  GetWindowRect(hWnd, &rc);
  OffsetRect(&rc, -rc.left, -rc.top);

  if (!IsRectEmpty(&rc)) {
    PatBlt(hdc, rc.left, rc.top, rc.right-rc.left, DINV, DSTINVERT);
    PatBlt(hdc, rc.left, rc.bottom-DINV, DINV, -(rc.bottom-rc.top-2*DINV),
	   DSTINVERT);
    PatBlt(hdc, rc.right-DINV, rc.top+DINV, DINV, rc.bottom-rc.top-2*DINV,
	   DSTINVERT);
    PatBlt(hdc, rc.right, rc.bottom-DINV, -(rc.right-rc.left), DINV,
	   DSTINVERT);
  }

  ReleaseDC(hWnd, hdc);
  UpdateWindow(hWnd);
}