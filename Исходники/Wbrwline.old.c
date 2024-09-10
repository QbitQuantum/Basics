CLIPPER WBrwRect( PARAMS ) // ( hWnd, nRow, aSizes, nFirstItem, nCol,
                           //   nLineStyle, nWidthVScroll )
{
   HWND hWnd        = ( HWND ) _parnl( 1 );

   HDC hDC          = GetDC( hWnd );
   WORD wRow        = _parni( 2 );
   WORD wHeight ;
   RECT rct;
   WORD nStyle = ISNUM( 6 ) ? _parni( 6 ) : -1 ; // CeSoTech


   #ifdef __CLIPPER__
      PCLIPVAR paSizes = _param( 3, 0x8000 );
      WORD wLen        = _VARRAYLEN( paSizes );
   #else
      #ifdef __HARBOUR__
         void * paSizes = ( void * ) _param( 3, IT_ARRAY );
         WORD wLen      = _parinfa( 3, 0 );
      #else
         void * paSizes = ( void * ) _param( 3, 0x8000 );
         WORD wLen      = _VARRAYLEN( paSizes );
      #endif
   #endif
   WORD wIndex      = _parni( 4 );
   WORD wCol        = _parni( 5 );
   WORD wMaxRight;
   LONG l;

   if( !wCol || wCol > wLen )
        return;


   GetWindowRect( hWnd, &rct );
   wMaxRight = rct.right - 2;

   wHeight = wLineHeight + 1 ;

   rct.top    = rct.top + ( bDrawHeaders ? wHeaderHeight+1 : 0 ) +
                (wHeight * (wRow-1) ) ;


   rct.bottom = rct.top + wHeight;
   rct.right  = rct.left;

   while( wIndex <= wCol )
   {
        rct.left   = rct.right;

        #ifndef __FLAT__

           rct.right  = ( wIndex == wLen && bAdjLastCol ? wMaxRight
                                         : rct.left + GetInt( paSizes, wIndex ) );

        #else
           #ifndef __HARBOUR__
              #define _parnl(x,y) PARNL(x,params,y);
           #endif
           l = _parnl( 3, wIndex );

           rct.right  = ( wIndex == wLen && bAdjLastCol ? wMaxRight
                                         : rct.left + l );

           #undef _parnl
        #endif

        if( rct.right >= wMaxRight )
        {
            wIndex = wCol + 1;   // ya no pintamos m s
            rct.right = wMaxRight;
        }
        else
            wIndex++;
   }



   ReleaseDC( hWnd, hDC );

   _reta( 4 );

   #ifdef __XPP__
      #define _storni( x, y, z ) STORNI( x, params, y, z )
   #endif


   // Si es un estilo sin separadores horizontales, pintar uno mas arriba
   //CeSoTech para que que bien completa el area !!!
   if (nStyle == 0 || nStyle == 5 || nStyle == 6 || nStyle == 9 || nStyle == 10)
      rct.top-- ;  // Las coord.de edicion deberan ser mas arriba tambien !!!


   _storni( rct.top,    -1, 1 );
   _storni( rct.left,   -1, 2 );
   _storni( rct.bottom, -1, 3 );
   _storni( ( wMaxRight <= rct.right ) ?
              wMaxRight - _parni( 7 ) : rct.right, -1, 4 );
}