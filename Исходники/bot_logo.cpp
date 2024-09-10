void RedrawClientArea(HWND hWnd, HDC hDC)
{
   HDC     hDCMem;

   if (hBitmap)
   {
      GetBitmapPosition(hWnd);

      hDCMem = CreateCompatibleDC(hDC);

      SelectObject (hDCMem, hBitmap);
      SetMapMode (hDCMem, GetMapMode(hDC));

      if (hPalette)
      {
         SelectPalette(hDC, hPalette, FALSE);
         RealizePalette(hDC);
         SelectPalette(hDCMem, hPalette, FALSE);
         RealizePalette(hDCMem);
      }
      
      BitBlt(hDC, offset_x, offset_y, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,
             hDCMem, 0, 0, SRCCOPY);

      DeleteDC(hDCMem);
   }

   return;
}