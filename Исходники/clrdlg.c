void _ColorHorizGradientRectangle
   ( 
   ChooseColorsStruct  *ccs,
   HDC                  hDC,
   const RECT *const    rect, 
   const COLORREF       color1,
   const COLORREF       color2
   )
   {
   TRIVERTEX      vertices[2];
   GRADIENT_RECT  gradient;
   HBRUSH         hBrush;
   RECT           rc;

      
   vertices[0].x     = rect->left + COLOR_CHANNEL_SLIDER_OFFSET;
   vertices[0].y     = rect->top;
   vertices[0].Red   = ( ( ( unsigned short )GetRValue( color1 ) ) << 8 );
   vertices[0].Green = ( ( ( unsigned short )GetGValue( color1 ) ) << 8 );
   vertices[0].Blue  = ( ( ( unsigned short )GetBValue( color1 ) ) << 8 );
   vertices[0].Alpha = 0;

   vertices[1].x     = rect->right - COLOR_CHANNEL_SLIDER_OFFSET;
   vertices[1].y     = rect->bottom;
   vertices[1].Red   = ( ( ( unsigned short )GetRValue( color2 ) ) << 8 );
   vertices[1].Green = ( ( ( unsigned short )GetGValue( color2 ) ) << 8 );
   vertices[1].Blue  = ( ( ( unsigned short )GetBValue( color2 ) ) << 8 );
   vertices[1].Alpha = 0;

   gradient.UpperLeft  = 0;
   gradient.LowerRight = 1;

   GradientFill( hDC, vertices, 2, &gradient, 1, GRADIENT_FILL_RECT_H );

   rc.top    = 0;
   rc.bottom = rect->bottom;

   hBrush = CreateSolidBrush( color1 );
   rc.left   = 0;
   rc.right  = COLOR_CHANNEL_SLIDER_OFFSET;
   FillRect( hDC, &rc, hBrush );
   DeleteObject( hBrush );

   hBrush = CreateSolidBrush( color2 );
   rc.left   = rect->right - COLOR_CHANNEL_SLIDER_OFFSET;
   rc.right  = rect->right;
   FillRect( hDC, &rc, hBrush );
   DeleteObject( hBrush );

   }/* _ColorHorizGradientRectangle() */