BOOL createRGBPalette(HDC hDC)
{
  
   PIXELFORMATDESCRIPTOR pfd;
   LOGPALETTE* pPal;
   HPALETTE hPal;
   int i,j,n;

   /* Check to see if we need a palette */
   n = GetPixelFormat(hDC);
   DescribePixelFormat(hDC, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
   if (!(pfd.dwFlags & PFD_NEED_PALETTE)) return FALSE ; 

   /* Allocate a log pal and fill it with the color table info */
   pPal = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));
   pPal->palVersion = 0x300; /* Windows 3.0 */
   pPal->palNumEntries = 256; /* table size */

   /*/ Create palette */
   n = 1 << pfd.cColorBits;
   for (i=0; i<n; i++)
   {
      pPal->palPalEntry[i].peRed =
	     ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
      pPal->palPalEntry[i].peGreen =
	     ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
      pPal->palPalEntry[i].peBlue =
	     ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
      pPal->palPalEntry[i].peFlags = 0;
   }

   if ((pfd.cColorBits == 8)			       &&
       (pfd.cRedBits   == 3) && (pfd.cRedShift	 == 0) &&
       (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
       (pfd.cBlueBits  == 2) && (pfd.cBlueShift	 == 6))
   {
      for (j = 1 ; j <= 12 ; j++)
	  pPal->palPalEntry[m_defaultOverride[j]] = m_defaultPalEntry[j];
   }


   hPal = CreatePalette(pPal);
   SelectPalette(hDC,hPal,FALSE);
   

   return TRUE;
}