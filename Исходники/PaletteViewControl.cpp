void PaletteViewControl::OnPaint() 
{
  CPaintDC dc(this); // device context for painting
  
  RECT rect;
  GetClientRect(&rect);
  int w = rect.right - rect.left;
  int h = rect.bottom - rect.top;
  
  CDC memDC;
  memDC.CreateCompatibleDC(&dc);
  CBitmap bitmap, *pOldBitmap;
  bitmap.CreateCompatibleBitmap(&dc, w, h);
  pOldBitmap = memDC.SelectObject(&bitmap);
  
  StretchDIBits(memDC.GetSafeHdc(),
                0,
                0,
                w,
                h,
                0,
                0,
                this->w,
                this->h,
                data,
                &bmpInfo,
                DIB_RGB_COLORS,
                SRCCOPY);
  int sw = this->w / 16;
  int sh = this->h / 16;
  int mult  = w / sw;
  int multY = h / sh;
  CPen pen;
  pen.CreatePen(PS_SOLID, 1, RGB(192,192,192));
  CPen *old = memDC.SelectObject(&pen);
  int i;
  for(i = 1; i < sh; i++) {
    memDC.MoveTo(0, i * multY);
    memDC.LineTo(w, i * multY);
  }
  for(i = 1; i < sw; i++) {
    memDC.MoveTo(i * mult, 0);
    memDC.LineTo(i * mult, h);
  }
  memDC.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
  memDC.SelectObject(old);
  pen.DeleteObject();

  if(selected != -1) {
    pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    old = memDC.SelectObject(&pen);

    int startX = (selected & (sw-1))*mult+1;
    int startY = (selected / sw)*multY+1;
    int endX = startX + mult-2;
    int endY = startY + multY-2;
    
    memDC.MoveTo(startX, startY);
    memDC.LineTo(endX, startY);
    memDC.LineTo(endX, endY);
    memDC.LineTo(startX, endY);
    memDC.LineTo(startX, startY-1);

    memDC.SelectObject(old);
    pen.DeleteObject();
  }
  
  dc.BitBlt(0,0,w,h,
            &memDC,0,0,SRCCOPY);

  memDC.SelectObject(pOldBitmap);
  bitmap.DeleteObject();
  memDC.DeleteDC();
}