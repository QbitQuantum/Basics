BOOL ColorControl::OnEraseBkgnd(CDC* pDC) 
{
  int r = (color & 0x1f) << 3;
  int g = (color & 0x3e0) >> 2;
  int b = (color & 0x7c00) >> 7;

  CBrush br;
  br.CreateSolidBrush(RGB(r,g,b));

  RECT rect;
  GetClientRect(&rect);
  pDC->FillRect(&rect,&br);
  pDC->DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
  br.DeleteObject();
  return TRUE;
}