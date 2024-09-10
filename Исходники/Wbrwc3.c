static void MaskRegion( HDC hdc, RECT * rct, COLORREF cTransparentColor,
                        COLORREF cBackgroundColor )

{
   HDC        hdcTemp, hdcObject, hdcBack, hdcMem;
   POINT      ptSize;
   COLORREF   cColor;
   HBITMAP    bmAndObject, bmAndBack, bmBackOld, bmObjectOld,
              bmAndTemp, bmTempOld, bmAndMem, bmMemOld;
   HBRUSH     hBrush, hBrOld;

   ptSize.x = rct->right - rct->left + 1;
   ptSize.y = rct->bottom - rct->top + 1;

   hBrush      = CreateSolidBrush(cBackgroundColor);

   hdcTemp     = CreateCompatibleDC(hdc);
   hdcObject   = CreateCompatibleDC(hdc);
   hdcBack     = CreateCompatibleDC(hdc);
   hdcMem      = CreateCompatibleDC(hdc);

   bmAndTemp   = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmTempOld   = SelectObject(hdcTemp, bmAndTemp);
   bmMemOld    = SelectObject(hdcMem, bmAndMem);
   bmBackOld   = SelectObject(hdcBack, bmAndBack);
   bmObjectOld = SelectObject(hdcObject, bmAndObject);

   hBrOld      = SelectObject(hdcMem, hBrush);

   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdc, rct->left, rct->top, SRCCOPY);

   SetMapMode(hdcTemp, GetMapMode(hdc));

   cColor = SetBkColor(hdcTemp, cTransparentColor);

   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   SetBkColor(hdcTemp, cColor);

   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
   PatBlt(hdcMem, 0,0, ptSize.x, ptSize.y, PATCOPY);
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);
   BitBlt(hdc, rct->left, rct->top, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);

   DeleteObject(SelectObject(hdcMem, hBrOld));
   DeleteObject(SelectObject(hdcTemp, bmTempOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcTemp);
}