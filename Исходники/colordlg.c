/***********************************************************************
 *                             CC_PaintUserColorArray         [internal]
 *               Paint the 16 user-selected colors
 */
static void CC_PaintUserColorArray( HWND hDlg, int rows, int cols, const COLORREF *lpcr )
{
 HWND hwnd = GetDlgItem(hDlg, 0x2d1);
 RECT rect, blockrect;
 HDC  hdc;
 HBRUSH hBrush;
 int dx, dy, i, j, k;
 LPCCPRIV lpp = GetPropW( hDlg, szColourDialogProp );

 GetClientRect(hwnd, &rect);

 dx = rect.right / cols;
 dy = rect.bottom / rows;
 k = rect.left;

 hdc = GetDC(hwnd);
 if (hdc)
 {
  hBrush = (HBRUSH)GetClassLongPtrW( hwnd, GCLP_HBRBACKGROUND);
  if (!hBrush) hBrush = GetSysColorBrush(COLOR_BTNFACE);
  FillRect( hdc, &rect, hBrush );
  for (j = 0; j < rows; j++)
  {
   for (i = 0; i < cols; i++)
   {
    hBrush = CreateSolidBrush(lpcr[i+j*cols]);
    if (hBrush)
    {
     blockrect.left = rect.left;
     blockrect.top = rect.top;
     blockrect.right = rect.left + dx - DISTANCE;
     blockrect.bottom = rect.top + dy - DISTANCE;
     FillRect(hdc, &blockrect, hBrush);
     DrawEdge(hdc, &blockrect, BDR_SUNKEN, BF_RECT);
     DeleteObject(hBrush);
    }
    rect.left += dx;
   }
   rect.top += dy;
   rect.left = k;
  }
  ReleaseDC(hwnd, hdc);
 }
 if (lpp->hwndFocus == hwnd)
   CC_DrawCurrentFocusRect(lpp);
}