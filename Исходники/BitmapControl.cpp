void BitmapControl::OnDraw(CDC* dc)
{
  RECT r;
  GetClientRect(&r);
  int w1 = r.right - r.left;
  int h1 = r.bottom - r.top;
  CDC memDC;
  memDC.CreateCompatibleDC(dc);
  if(!stretch) {
    if(w > w1)
      w1 = w;
    if(h > h1)
      h1 = h;
  }
  CBitmap bitmap, *pOldBitmap;
  bitmap.CreateCompatibleBitmap(dc, w1, h1);
  pOldBitmap = memDC.SelectObject(&bitmap);
  if(stretch) {
    bmpInfo->bmiHeader.biWidth = w;
    bmpInfo->bmiHeader.biHeight = -h;

    StretchDIBits(memDC.GetSafeHdc(),
                  0,
                  0,
                  w1,
                  h1,
                  0,
                  0,
                  w,
                  h,
                  data,
                  bmpInfo,
                  DIB_RGB_COLORS,
                  SRCCOPY);
  } else {
    FillOutsideRect(&memDC, CBrush::FromHandle(GetSysColorBrush(COLOR_BTNFACE)));

    bmpInfo->bmiHeader.biWidth = w;
    bmpInfo->bmiHeader.biHeight = -h;
    SetDIBitsToDevice(memDC.GetSafeHdc(),
                      0,
                      0,
                      w,
                      h,
                      0,
                      0,
                      0,
                      h,
                      data,
                      bmpInfo,
                      DIB_RGB_COLORS);
  }

  dc->BitBlt(0,0,w1,h1,
             &memDC,0,0,SRCCOPY);
  memDC.SelectObject(pOldBitmap);

  bitmap.DeleteObject();
  memDC.DeleteDC();
}