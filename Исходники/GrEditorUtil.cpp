/*func*------------------------------------------------------------------------
  create the color palette with the in GR used colors
  (bitmaps and elements for screen and printer)
  in :-
  out:-
-----------------------------------------------------------------------------*/
void GDIHelper::CreatePalette(void)
{
   LPBITMAPINFO   lpbi;
   int            i, j, k, iColBm, iCol;
   HANDLE         hPal;
   LPLOGPALETTE   lpPal;
   HRSRC          hRsrc;
   HGLOBAL        hGlobal;
   
   if( ((hRsrc = FindResource(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_GR_ICONVARFB), RT_BITMAP)) != NULL) &&
      ((hGlobal = LoadResource(::GetModuleHandle(NULL), hRsrc)) != NULL) )
   {
      if( (lpbi = (LPBITMAPINFO)LockResource(hGlobal)) == NULL )
      {
         UnlockResource(hGlobal);
         ASSERT(FALSE);
         return;
      }
      
      if (lpbi->bmiHeader.biBitCount <= 8)
      {
         iColBm = (1 << lpbi->bmiHeader.biBitCount);
      } else {
         iColBm = 0;  // No palette needed for 24 BPP DIB
      }
      
      if (lpbi->bmiHeader.biClrUsed > 0)
      {
         iColBm = lpbi->bmiHeader.biClrUsed;  // Use biClrUsed
      }

      iCol = iColBm + CO_LAST;
      if (iCol)
      {
         hPal = GlobalAlloc (GHND, sizeof (LOGPALETTE) +
            sizeof (PALETTEENTRY) * (iCol));
         if( hPal != NULL )
         {
            lpPal = (LPLOGPALETTE) GlobalLock (hPal);
            if (lpPal != NULL )
            {
               for( k=0; k<=1; k++ )
               {
                  // load colors of the GR elements for printer [0] and screen [1]
                  for( i=0; i<CO_LAST; i++ )
                  {
                     lpPal->palPalEntry[i].peRed   = GetRValue(ulColor[k][i]);
                     lpPal->palPalEntry[i].peGreen = GetGValue(ulColor[k][i]);
                     lpPal->palPalEntry[i].peBlue  = GetBValue(ulColor[k][i]);
                     lpPal->palPalEntry[i].peFlags = 0;
                  }
                  // load colors of the bitmaps for printer [0] and screen [1]
                  for( j=0; i<iCol; i++, j++ )
                  {
                     lpPal->palPalEntry[i].peRed   = lpbi->bmiColors[j].rgbRed;
                     lpPal->palPalEntry[i].peGreen = lpbi->bmiColors[j].rgbGreen;
                     lpPal->palPalEntry[i].peBlue  = lpbi->bmiColors[j].rgbBlue;
                     lpPal->palPalEntry[i].peFlags = 0;
                  }
                  lpPal->palVersion    = 0x300;
                  lpPal->palNumEntries = (short)i;
                  
                  pColPal[k] = new CPalette;
                  bPalRealized[k] = false;
                  ASSERT(pColPal[k]);
                  if( pColPal[k] ) pColPal[k]->CreatePalette(lpPal);
               }
               
               GlobalUnlock (hPal);
            }
            GlobalFree (hPal);
         }
      }
      UnlockResource (hGlobal);
      FreeResource (hGlobal);
   }
}