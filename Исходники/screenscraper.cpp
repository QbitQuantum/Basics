static screenshot *take_screenshot_with_gdi(uint32_t x, uint32_t y,
    uint32_t width, uint32_t height) {
  HRESULT hr;
  int ir;
  BOOL r;
  // DWM causes screenshotting with GDI to be very slow. The only fix is to
  // disable DWM during the test. DWM will automatically be re-enabled when the
  // process exits. This API stops working on Windows 8 (though it returns
  // success regardless).
  if (!composition_disabled) {
    // HACK: DwmEnableComposition fails unless GetDC(NULL) has been called
    // first. Who knows why.
    HDC workaround = GetDC(NULL);
    int ir = ReleaseDC(NULL, workaround);
    assert(ir);
    hr = DwmEnableComposition(DWM_EC_DISABLECOMPOSITION);
    assert(hr == S_OK);
    // DWM takes a little while to repain the screen after being disabled.
    Sleep(1000);
    composition_disabled = true;
  }
  int virtual_x = ((int)x) - GetSystemMetrics(SM_XVIRTUALSCREEN);
  int virtual_y = ((int)y) - GetSystemMetrics(SM_YVIRTUALSCREEN);
  width = min(width, (uint32_t)GetSystemMetrics(SM_CXVIRTUALSCREEN));
  height = min(height, (uint32_t)GetSystemMetrics(SM_CYVIRTUALSCREEN));
  HDC screen_dc = GetDC(NULL);
  assert(screen_dc);
  HDC memory_dc = CreateCompatibleDC(screen_dc);
  assert(memory_dc);
  BITMAPINFO bitmap_info;
  memset(&bitmap_info, 0, sizeof(BITMAPINFO));
  bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bitmap_info.bmiHeader.biWidth = width;
  bitmap_info.bmiHeader.biHeight = -(int)height;
  bitmap_info.bmiHeader.biPlanes = 1;
  bitmap_info.bmiHeader.biBitCount = 32;
  bitmap_info.bmiHeader.biCompression = BI_RGB;
  uint8_t *pixels = NULL;
  HBITMAP hbitmap = CreateDIBSection(screen_dc, &bitmap_info, DIB_RGB_COLORS,
      (void **)&pixels, NULL, 0);
  assert(hbitmap);
  SelectObject(memory_dc, hbitmap);
  r = BitBlt(memory_dc, 0, 0, width, height, screen_dc, virtual_x, virtual_y,
      SRCCOPY);
  assert(r);
  ir = ReleaseDC(NULL, screen_dc);
  assert(ir);
  r = DeleteObject(memory_dc);
  assert(r);
  screenshot *shot = (screenshot *)malloc(sizeof(screenshot));
  shot->pixels = pixels;
  shot->width = width;
  shot->height = height;
  shot->stride = width * 4;
  shot->platform_specific_data = hbitmap;
  shot->time_nanoseconds = get_nanoseconds();
  return shot;
}