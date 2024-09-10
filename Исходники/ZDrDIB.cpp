/////////////////////////////////////////////////////////////////////////////
//
// Create the palette.  Use halftone palette for hi-color bitmaps.
//
/////////////////////////////////////////////////////////////////////////////
zBOOL
ZDib::CreatePalette( CPalette& pal )
{
   // Should not already have palette
   ASSERT( pal.m_hObject == 0 );

   zBOOL bRC = FALSE;
   RGBQUAD *colors = new RGBQUAD[ MAXPALCOLORS ];
   UINT nColors = GetColorTable( colors, MAXPALCOLORS );
   if ( nColors > 0 )
   {
      // Allocate memory for logical palette.
      int nLth = sizeof( LOGPALETTE ) + sizeof( PALETTEENTRY ) * nColors;
      LOGPALETTE *pLogPal = (LOGPALETTE *) new char[ nLth ];
      if ( pLogPal == 0 )
         return( 0 );

      // Set version and number of palette entries.
      pLogPal->palVersion = PALVERSION;
      pLogPal->palNumEntries = nColors;

      // Copy color entries.
      for ( UINT k = 0; k < nColors; k++ )
      {
         pLogPal->palPalEntry[ k ].peRed   = colors[ k ].rgbRed;
         pLogPal->palPalEntry[ k ].peGreen = colors[ k ].rgbGreen;
         pLogPal->palPalEntry[ k ].peBlue  = colors[ k ].rgbBlue;
         pLogPal->palPalEntry[ k ].peFlags = 0;
      }

      // Create the palette and destroy LOGPAL.
      bRC = pal.CreatePalette( pLogPal );
      delete [] (zPCHAR) pLogPal;
   }
   else
   {
      CWindowDC dcScreen( 0 );
      bRC = pal.CreateHalftonePalette( &dcScreen );
   }

   delete [] colors;
   return( bRC );
}