/* ‘ункци¤ рисовани¤ глаза.
 * ј–√”ћ≈Ќ“џ:
 *   - дескриптор окна:
 *       HWND hWnd;
 *   - контекст устройства:
 *       HDC hDC;
 *   - координаты центра:
 *       INT X, Y;
 *   - радиусы:
 *       INT R, R1;
 * ¬ќ«¬–јўј≈ћќ≈ «Ќј„≈Ќ»≈: Ќет.
 */
VOID DrawEye( HWND hWnd, HDC hDC, INT X, INT Y, INT R, INT R1 )
{
  INT px, py, len2;
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(255, 0, 0));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(255, 255, 0));

  Ellipse(hDC, X - R, Y - R, X + R, Y + R);
  px = pt.x;
  py = pt.y;
  SetDCPenColor(hDC, RGB(255, 0, 255));
  SetDCBrushColor(hDC, RGB(0, 0, 0));

  len2 = sqrt((px - X) * (px - X) + (py - Y) * (py - Y));
  if (len2 < (R - R1))
    len2 = (R - R1);
  px = (px - X) * (R - R1) / len2 + X;
  py = (py - Y) * (R - R1) / len2 + Y;

  Ellipse(hDC, px - R1, py - R1, px + R1, py + R1);
} /* End of 'DrawEye' function */