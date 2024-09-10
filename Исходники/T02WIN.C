void DrawEye(HDC hDC, INT Xm, INT Ym, INT Xc, INT Yc, INT W, INT H, INT R)
{
  int xe, ye;
  double len = sqrt((Xc - Xm) * (Xc - Xm) + (Yc - Ym) * (Yc - Ym)), si, co;
  SelectObject(hDC, GetStockObject(NULL_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDC, RGB(255, 255, 255));
  SetDCBrushColor(hDC, RGB(255, 255, 255));
  

}