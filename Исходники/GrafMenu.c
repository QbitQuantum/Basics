HBITMAP StretchBitmap (HBITMAP hBitmap1)
{
     BITMAP     bm1, bm2 ;
     HBITMAP    hBitmap2 ;
     HDC        hdc, hdcMem1, hdcMem2 ;
     int        cxChar, cyChar ;

          // Get the width and height of a system font character

     cxChar = LOWORD (GetDialogBaseUnits ()) ;
     cyChar = HIWORD (GetDialogBaseUnits ()) ;

          // Create 2 memory DCs compatible with the display
     
     hdc = CreateIC (TEXT ("DISPLAY"), NULL, NULL, NULL) ;
     hdcMem1 = CreateCompatibleDC (hdc) ;
     hdcMem2 = CreateCompatibleDC (hdc) ;
     DeleteDC (hdc) ;

          // Get the dimensions of the bitmap to be stretched
     
     GetObject (hBitmap1, sizeof (BITMAP), (PTSTR) &bm1) ;

          // Scale these dimensions based on the system font size
     
     bm2 = bm1 ;
     bm2.bmWidth      = (cxChar * bm2.bmWidth)  / 4 ;
     bm2.bmHeight     = (cyChar * bm2.bmHeight) / 8 ;
     bm2.bmWidthBytes = ((bm2.bmWidth + 15) / 16) * 2 ;

          // Create a new bitmap of larger size
     
     hBitmap2 = CreateBitmapIndirect (&bm2) ;

          // Select the bitmaps in the memory DCs and do a StretchBlt
     
     SelectObject (hdcMem1, hBitmap1) ;
     SelectObject (hdcMem2, hBitmap2) ;
     
     StretchBlt (hdcMem2, 0, 0, bm2.bmWidth, bm2.bmHeight,
                 hdcMem1, 0, 0, bm1.bmWidth, bm1.bmHeight, SRCCOPY) ;

          // Clean up
     
     DeleteDC (hdcMem1) ;
     DeleteDC (hdcMem2) ;
     DeleteObject (hBitmap1) ;
     
     return hBitmap2 ;
}