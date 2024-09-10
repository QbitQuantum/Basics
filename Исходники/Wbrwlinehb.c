//-----------------------------------------------------------------------=
                                                        // ÚÄ1ra Col.a Pintar
                                                        // ³
static void near PaintTheLine( HDC hDC, RECT * rct, WORD wIndex,
                               PCLIPVAR pAtext, PCLIPVAR pAsizes,
                               HPEN hWhitePen, HPEN hGrayPen, BOOL bTree,
                               PCLIPVAR pAJustify, WORD wPressed,
                               BOOL bHeader, WORD nStyle,
                               WORD wFocus, BOOL bFocused,
                               PCLIPVAR pTextColor, PCLIPVAR pBkColor,
                               WORD wRowPos, WORD nHeightCtrl,
                               LONG nClrLine, BOOL bFooter,
                               BOOL bSelect, PCLIPVAR pFont,
                               BOOL bDrawFocusRect )
{
   RECT box, wholebox, rctadj;
   int iMaxRight = rct->right;

   WORD wLenJust = 0 ;
   #ifndef __HARBOUR__
   WORD wLen     = _VARRAYLEN( pAtext );
   CLV_WORD lJustify;
   #else
   WORD wLen     = hb_arrayLen( pAtext );
   PHB_ITEM uElem = hb_itemNew( NULL );
   #endif
   WORD wType, wcLen;
   LONG lValue;
   char * cValue;
   HPEN hOldPen, hPen;
   BITMAP bmp;
   WORD wRow, wCol;
   LONG lColor ;
   HBRUSH hBrush;
   LONG lTextColorOld = -1 ; // CeSoTech
   LONG lBkColorOld   = -1 ; // CeSoTech
   PCLIPVAR pEvalOld ;
   HFONT hFont ; // CeSoTech
   WORD wAlign ; // CeSoTech

   // CeSoTech
   LONG nClrLineC = ( nStyle == 2 || nStyle == 6 || nStyle == 8 ||
                      nStyle == 10 ) ? GetSysColor( COLOR_BTNSHADOW ) : 0 ;

   // CeSoTech
   if ( nClrLine >= 0 )   // Desde Clipper manda color especifico linea
      nClrLineC = nClrLine ;

   if ( ! bDrawHeaders )
      bHeader = FALSE ;

   if ( bFooter )
      bHeader = TRUE ; //-> Para que lo pinte con similar aspecto

   //CeSoTech
   // Si es un estilo sin separadores horizontales, pintar uno mas arriba
   //CeSoTech para que que bien completa el area !!!
   if ( ! (bHeader) && (nStyle == 0 || nStyle == 5 || nStyle == 6 ||
                        nStyle == 9 || nStyle == 10) )
      rct->top--       ;

   wholebox.top    = rct->top+1;
   wholebox.left   = rct->left;
   wholebox.bottom = rct->bottom;
   wholebox.right  = rct->right;

   rct->right  = 0;

   box.top    = rct->top ;
   box.bottom = rct->bottom - 1;

   if( !wIndex | wIndex > wLen )
       wIndex = 1;

   if ( pAJustify )
      #ifndef __HARBOUR__
         wLenJust = _VARRAYLEN( pAJustify );
      #else
         wLenJust = hb_arrayLen( pAJustify );
      #endif

   while( wIndex <= wLen )
   {

        rct->left   = rct->right;

        rct->right  = ( wIndex == wLen ? iMaxRight
                                      : rct->left + GetInt( pAsizes, wIndex ) );
        // CeSoTech // Cuando estoy estoy en la ultima celda, NO pintar hasta
                    // el final si no existe ajuste de ultima columna.
        if ( ( wIndex == wLen ) && ( ! bAdjLastCol )  )
        {
           rct->right  = rct->left + GetInt( pAsizes, wIndex ) +(bHeader ? 1: 0) ;
           if ( !bAdjBrowse )
              wholebox.right = rct->right ; // Tambien ajusto el borde focus

        }
        // CeSoTech //


        wAlign = HA_LEFT | VA_CENTER ;  // Alineacion por defecto
        wcLen = 0;
        ///////// INICIO Toma de datos celda !!!

        #ifndef __HARBOUR__
           if ( wIndex <= wLenJust )
           {
             _cAt( pAJustify, wIndex, 0xFFFF, ( PCLIPVAR ) &lJustify );
             wAlign = lJustify.wWord ;
           }
           _cAt( pAtext, wIndex, 0xFFFF, ++_tos );
           wType = _tos->wType;
           if ( wType & NUMERIC )
              lValue = (LONG) _tos->pPointer1;
           if ( wType & CHARACTER )
           {
              cValue = _VSTR( _tos );
              wcLen = _tos->w2;
           }
        #else

           if ( wIndex <= wLenJust )
           {
              hb_arrayGet( pAJustify, wIndex, uElem );
              if ( ( hb_itemType( uElem ) & LOGICAL ) && hb_itemGetL( uElem ) )
                 wAlign = HA_RIGHT | VA_CENTER ;
              else
                 wAlign = hb_itemGetNL( uElem );

			        hb_itemClear( uElem );
           }

           // uElem.type = HB_IT_NIL;
           hb_arrayGet( pAtext, wIndex, uElem );
           wType = hb_itemType( uElem );
           if ( wType & NUMERIC )
              lValue = hb_itemGetNL( uElem );
           if ( wType & CHARACTER )
           {
//              cValue = hb_itemGetC( uElem );
				cValue = hb_itemGetCPtr( uElem );
                wcLen = strlen( cValue );
           }

        #endif
        ///////// FIN Toma de datos celda !!!



        if( wFocus > 0 && wIndex != wFocus )
        {
           #ifndef __HARBOUR__
              _tos--;
           #endif

           if( rct->right >= iMaxRight )
           {
               wIndex = wLen + 1;   // ya no pintamos m s
           }
           else
              ++wIndex;
           continue;
        }

        if( bTree ||
            (GetInt( pAsizes, wIndex ) > 0) ) //Si NO es columna oculta (x Freeze)
        {                                     //(Es lo mismo no hacer esto,
                                              // pero es para evitar hacer trabajar
                                              // al codigo sin sentido !!! )

           if( (wType & NUMERIC) && bTree )
           {
               if( lValue )
               {
                  FillRect( hDC, rct, hBrush = CreateSolidBrush( GetPixel( hDC, rct->left, rct->top ) ) );
                  DrawMasked( hDC, (HBITMAP) lValue, rct->top, rct->left );
                  DeleteObject( hBrush );
               }

           }
           else  // Si es Numerico Bmp no Tree, o , es Character !!!!
           {

               if ( pBkColor )  // Bloque de Color Fondo Celda
               {
                  _PutSym( _SymEval );
                  _xPushM( pBkColor );
                  _PutLN( wRowPos );
                  _PutLN( wIndex );
                  _PutLN( bFooter ? 2 : ( bHeader ? 1 : ( bSelect ? 3 : 0 ) ) );
                  _xEval( 3 ) ;
                  if ( _parinfo( -1 ) & NUMERIC )
                    lBkColorOld = SetBkColor( hDC, _parnl( - 1 ) ) ;
               }

               if( pTextColor ) // Bloque de Color Texto Celda
               {
                  _PutSym( _SymEval );
                  _xPushM( pTextColor );
                  _PutLN( wRowPos );
                  _PutLN( wIndex );
                  _PutLN( bFooter ? 2 : ( bHeader ? 1 : ( bSelect ? 3 : 0 ) ) );
                  _xEval( 3 ) ;
                  if ( _parinfo( -1 ) & NUMERIC )
                    lTextColorOld = SetTextColor( hDC, _parnl( - 1 ) ) ;
               }

               hFont = 0 ;
               if( pFont )      // Bloque de Font Celda
               {
                  _PutSym( _SymEval );
                  _xPushM( pFont );
                  _PutLN( wRowPos );
                  _PutLN( wIndex );
                  _PutLN( bFooter ? 2 : ( bHeader ? 1 : ( bSelect ? 3 : 0 ) ) );
                  _xEval( 3 ) ;
                  if ( _parinfo( -1 ) & NUMERIC )
                     hFont = (HFONT) _parnl( - 1 ) ;
               }


               /////// CeSoTech ///////
               if (!bHeader) rct->top ++;


               if( wType & NUMERIC )   // Es un BitMap
               {
                  FW_DrawBitmapCenter( hDC, (HBITMAP) lValue, rct, nStyle, bSelect );
               }
               else                    // Es una Cadena
               {
                  FW_DrawText( hDC, rct,
                               ( wType & CHARACTER ) ? cValue : "",
                               wAlign, wcLen, hFont, bHeader ) ;
               }


               /////// CeSoTech restauracion de colores //////
               if ( lTextColorOld >= 0 )
               {
                  SetTextColor( hDC, lTextColorOld ) ;
                  lTextColorOld = -1 ;
               }
               if ( lBkColorOld >= 0 )
               {
                  SetBkColor( hDC, lBkColorOld ) ;
                  lBkColorOld = -1 ;
               }


               /// CeSoTech ///
               // Si hay modalidad ajustar el Browse y no hay ajuste de ultima
               // columna, deber‚ pintar hasta el final hasta cubrir toda
               // el area, hasta llegar a la derecha del control. (Col.Ficticia)
               if ( bAdjBrowse && wIndex == wLen && !bAdjLastCol &&
                    rct->right <= iMaxRight )
               {
                  rctadj.top    = rct->top;
                  rctadj.left   = rct->right ;
                  rctadj.bottom = rct->bottom;
                  rctadj.right  = wholebox.right  ;

                  if ( nStyle == 3 )
                     rctadj.top--;

                  if ( wFocus == 0 )  // Si No es CellStyle (Pinto hasta final)
                     ExtTextOut( hDC, 0, rct->top, ETO_OPAQUE, &rctadj, "", 0, 0 );

                  if ( bHeader && nStyle==3 ) // Pinto Bordes Header Falso
                   {
                      rctadj.right  = wholebox.right - 2  ;
                      rctadj.bottom = rctadj.bottom - 2 ;
                      WndDrawBox( hDC, &rctadj, hWhitePen, hGrayPen );
                      rctadj.bottom++  ;
                      rctadj.right++  ;
                      WndDrawBox( hDC, &rctadj, hWhitePen, GetStockObject( BLACK_PEN ) );

                      if ( bFooter ) // Si es Footer (Linea Negra de Arriba Foot)
                      {
                        hPen = GetStockObject( BLACK_PEN );
                        hOldPen = SelectObject( hDC, hPen );
                        MoveTo( hDC, rctadj.left-1, rctadj.top-1 );
                        LineTo( hDC, rctadj.right+1, rctadj.top-1 );
                        SelectObject( hDC, hOldPen );
                      }

                  }

               }
               /// CeSoTech Fin ///

               if (!bHeader) rct->top --;
           }

           box.left   = rct->left;

           box.right  = ( wIndex < wLen && rct->right <= iMaxRight ?
                                                        rct->right - 1 :
                                                        iMaxRight - 1 );

           // CeSoTech // El Borde derecho de Box de la ultima columna,
                       // no estirarlo cuando no exista ajuste de ultima columna
                       // PERO cuando nLineStyle (nStyle) es 7/8 (Lineas Horiz)
                       // queda anti-estetico cortar los renglones, cuando no hay
                       // ajuste ult.col. y hay ajuste de browse. Por ello
                       // se verificara que para cortar el borde no se de esta
                       // condicion.
           if ( ( wIndex == wLen ) && ( ! bAdjLastCol ) )
           {
              if (! (!bHeader && (nStyle==7 || nStyle==8) && !bAdjLastCol && bAdjBrowse) )
               box.right  = rct->left + GetInt( pAsizes, wIndex ) - 1 ;
           }
           // CeSoTech //



           if( ! bTree )
           {
              if( wPressed && ( wIndex == wPressed ) )
              {
                WndDrawBox( hDC, &box, hGrayPen, hWhitePen );
              }
              else
/////////////  if(!bHeader)
               if(!bHeader || (bHeader && nStyle!=3) )
               {
                  switch( nStyle )
                  {
                     case 0:
                        break;
                     case 1:
                    //  hOldPen = SelectObject( hDC, GetStockObject( BLACK_PEN ) );
                        hPen = CreatePen(PS_SOLID, 0, nClrLineC );
                        hOldPen = SelectObject( hDC, hPen);
                        MoveTo( hDC, box.left, box.bottom+1 );
                        LineTo( hDC, box.left, box.top );
                        LineTo( hDC, box.right+1, box.top );
                        LineTo( hDC, box.right+1,  box.bottom+1 );
                        LineTo( hDC, box.left, box.bottom+1 );
                        SelectObject( hDC, hOldPen );
                        DeleteObject( hPen);
                        break;
                     case 2:
                        hPen = CreatePen(PS_SOLID, 0, nClrLineC );
                        hOldPen = SelectObject( hDC, hPen);
                        MoveTo( hDC, box.left, box.bottom+1 );
                        LineTo( hDC, box.left, box.top );
                        LineTo( hDC, box.right+1, box.top );
                        LineTo( hDC, box.right+1,  box.bottom+1 );
                        LineTo( hDC, box.left, box.bottom+1 );
                        SelectObject( hDC, hOldPen );
                        DeleteObject( hPen);
                        break;
                     case 3:
                        WndDrawBox( hDC, &box, hWhitePen, hGrayPen );
                        break;
                     case 4:
                        box.bottom ++;
                        box.right ++;
                        FrameDot( hDC, &box );
                        box.bottom --;
                        box.right --;
                        break;
                     case 7:
                     case 8:
                        hPen = CreatePen(PS_SOLID, 0, nClrLineC );
                        hOldPen = SelectObject( hDC, hPen);
                        MoveTo( hDC, box.left, box.top );
                        LineTo( hDC, box.right+1, box.top );
                        MoveTo( hDC, box.right+1,  box.bottom+1 );
                        LineTo( hDC, box.left, box.bottom+1 );
                        SelectObject( hDC, hOldPen );
                        DeleteObject( hPen);
                        break;
                     case 5:
                     case 6:
                     case 9:
                     case 10:
                        hPen = CreatePen(PS_SOLID, 0, nClrLineC);
                        hOldPen = SelectObject( hDC, hPen);
                        if (box.left>1)
                        {
                           MoveTo( hDC, box.left, box.bottom+1 );
                           LineTo( hDC, box.left, box.top );
                        }
                        MoveTo( hDC, box.right+1, box.top );

                        if ( bDrawFooters && nStyle >= 9 )
                        {
                        LineTo( hDC, box.right+1,
                                     nHeightCtrl - (wFooterHeight+1) ) ;
                        } else {
                          LineTo( hDC, box.right+1,
                                     nStyle < 9 ? box.bottom+1 : nHeightCtrl );
                        }

                        SelectObject( hDC, hOldPen );
                        DeleteObject( hPen);
                        break;
                  }
               }
               else  // Box para Headers !!!
               {
                  box.left ++;

                  // CeSoTech
                  if ( bFooter ) // Linea negra sobre el Footer
                  {
                    hPen = GetStockObject( BLACK_PEN );
                    hOldPen = SelectObject( hDC, hPen );
                    MoveTo( hDC, box.left-1, box.top-1 );
                    LineTo( hDC, box.right+1, box.top-1 );
                    SelectObject( hDC, hOldPen );
                  }

                  box.right--  ;
                  box.bottom-- ;
                  WndDrawBox( hDC, &box, hWhitePen, hGrayPen );
                  box.bottom++  ;
                  box.right++  ;
                  WndDrawBox( hDC, &box, hWhitePen, GetStockObject( BLACK_PEN ) );

                  box.left --;

               }
           }
           else
           {
              if( ! ( wType & NUMERIC ) )
              {
                 box.left -= 16;
              }
           }

          // CeSoTech if( bFocused && wFocus > 0 && wIndex == wFocus )
           if( bDrawFocusRect && bFocused && wFocus > 0 &&
               wIndex == wFocus && nStyle != 3)
           {
            rct->left++;
            rct->top++;
            DrawFocusRect( hDC, rct );
            rct->left--;
            rct->top--;
           }

        }

        #ifndef __HARBOUR__
           _tos--;
        #endif

        if( rct->right >= iMaxRight )
        {
            wIndex = wLen + 1;   // ya no pintamos m s
        }
        else
           ++wIndex;


   }

   if (bDrawFocusRect && !bTree && bFocused && wFocus==0 && nStyle!=3) // CeSoTech
      DrawFocusRect( hDC, &wholebox );

  hb_itemRelease( uElem );
}