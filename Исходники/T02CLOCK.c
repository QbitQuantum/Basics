/* Draw figure function */
VOID Draw( HDC hDC, INT X, INT Y, DOUBLE A )
{
  INT i;
  DOUBLE rad = A * 3.14159265358979323 / 180, si = sin(rad), co = cos(rad);
  static POINT pt[] =
  {
    {-10, 0}, {-10, 50}, {0, 59 * 3}, {10, 50}, {10, 0}
  };
  POINT pt1[sizeof(pt) / sizeof(pt[0])];

  for (i = 0; i < sizeof(pt) / sizeof(pt[0]); i++)
  {
    pt1[i].x = X + pt[i].x * co - pt[i].y * si;
    pt1[i].y = Y - (pt[i].x * si + pt[i].y * co);
  }
  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDC, RGB(255, 0, 0));
  SetDCBrushColor(hDC, RGB(255, 220, 220));
  Polygon(hDC, pt1, sizeof(pt) / sizeof(pt[0]));
} /* End of 'Draw' function */