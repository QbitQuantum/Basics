DWORD PrintABand (HDC hDC,
               LPRECT lpRectOut,
               LPRECT lpRectClip,
                 BOOL fDoText,
                 BOOL fDoGraphics,
                LPSTR lpDIBHdr,
                LPSTR lpDIBBits)
{
   int    nxLogPix, nyLogPix;
   RECT   rect;
   double dblXScaling, dblYScaling;
   DWORD  dwError = ERR_PRN_NONE;


   if (fDoGraphics)
      {
      nxLogPix = GetDeviceCaps (hDC, LOGPIXELSX);
      nyLogPix = GetDeviceCaps (hDC, LOGPIXELSY);

      dblXScaling = ((double) lpRectOut->right - lpRectOut->left) /
                     DIBWidth (lpDIBHdr);
      dblYScaling = ((double) lpRectOut->bottom - lpRectOut->top) /
                     DIBHeight (lpDIBHdr);


         // Now we set up a temporary rectangle -- this rectangle
         //  holds the coordinates on the paper where our bitmap
         //  WILL be output.  We can intersect this rectangle with
         //  the lpClipRect to see what we NEED to output to this
         //  band.  Then, we determine the coordinates in the DIB
         //  to which this rectangle corresponds (using dbl?Scaling).

      IntersectRect (&rect, lpRectOut, lpRectClip);

      if (!IsRectEmpty (&rect))
         {
         RECT rectIn;
         int  nPct;

         rectIn.left   = (int) ((rect.left - lpRectOut->left) /
                                 dblXScaling + 0.5);
         rectIn.top    = (int) ((rect.top  - lpRectOut->top) /
                                 dblYScaling + 0.5);
         rectIn.right  = (int) (rectIn.left + (rect.right  - rect.left) /
                                 dblXScaling + 0.5);
         rectIn.bottom = (int) (rectIn.top  +  (rect.bottom - rect.top) /
                                 dblYScaling + 0.5);

            // Could just always call StretchDIBits() below, but
            //  we want to give SetDIBitsToDevice() a work out, too!

         if ((rect.right - rect.left == rectIn.right - rectIn.left) &&
             (rect.bottom - rect.top == rectIn.bottom - rectIn.top))
            {
            if (!SetDIBitsToDevice (hDC,                            // DestDC
                                    rect.left,                      // DestX
                                    rect.top,                  // DestY
                                    rect.right - rect.left,    // DestWidth
                                    rect.bottom - rect.top,    // DestHeight
                                    rectIn.left,               // SrcX
                                    (int) DIBHeight (lpDIBHdr)-// SrcY
                                       rectIn.top -
                                       (rectIn.bottom - rectIn.top),
                                    0,                         // nStartScan
                                    (int) DIBHeight (lpDIBHdr),// nNumScans
                                    lpDIBBits,                 // lpBits
                                    (LPBITMAPINFO) lpDIBHdr,   // lpBitInfo
                                    DIB_RGB_COLORS))           // wUsage
               dwError |= ERR_PRN_SETDIBITSTODEV;
            }
         else
            {
            if (!StretchDIBits (hDC,                           // DestDC
                                rect.left,                     // DestX
                                rect.top,                      // DestY
                                rect.right - rect.left,        // DestWidth
                                rect.bottom - rect.top,        // DestHeight
                                rectIn.left,                   // SrcX
                                (int) DIBHeight (lpDIBHdr) -   // SrcY
                                   rectIn.top -
                                   (rectIn.bottom - rectIn.top),
                                rectIn.right - rectIn.left,    // SrcWidth
                                rectIn.bottom - rectIn.top,    // SrcHeight
                                lpDIBBits,                     // lpBits
                                (LPBITMAPINFO) lpDIBHdr,       // lpBitInfo
                                DIB_RGB_COLORS,                // wUsage
                                SRCCOPY))                      // dwROP
               dwError |= ERR_PRN_STRETCHDIBITS;
            }


            // Change percentage of print shown in abort dialog.

         nPct = MulDiv (rect.bottom,
                        100,
                        lpRectOut->bottom);
         ChangePrintPercent (nPct);
         }
      }

	 I_UNUSED(nyLogPix);
	 I_UNUSED(nxLogPix);
	 I_UNUSED(fDoText);

   return dwError;
}