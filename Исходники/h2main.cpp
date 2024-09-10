MRESULT EXPENTRY ClientWndProc ( HWND hwndWnd, ULONG ulMsg, MPARAM mpParm1, MPARAM mpParm2 )
{
   switch ( ulMsg )
   {
   // For HELP debugging
   #if 0
      case HM_ERROR:
         {
            CHAR     szTempBuffer[256];

            sprintf( szTempBuffer, "Received HM_ERROR message, mp1=0X%8.8X", (ULONG)mpParm1 );
            WinMessageBox ( HWND_DESKTOP, HWND_DESKTOP, szTempBuffer, "HM_ERROR", 0, MB_OK );
         }
         break;

      case HM_EXT_HELP_UNDEFINED:
         WinMessageBox ( HWND_DESKTOP, HWND_DESKTOP, "Received HM_EXT_HELP_UNDEFINED message", "HM_EXT_HELP_UNDEFINED", 0, MB_OK );
         break;

      case HM_HELPSUBITEM_NOT_FOUND:
         WinMessageBox ( HWND_DESKTOP, HWND_DESKTOP, "Received HM_HELPSUBITEM_NOT_FOUND message", "HM_HELPSUBITEM_NOT_FOUND", 0, MB_OK );
         break;
   #endif

      case HM_QUERY_KEYS_HELP:
         return (MRESULT)IDP_KEYS_INFO;
         break;

      case WM_BUTTON1CLICK:
         MoveCursorToPointer( hwndWnd, (*(POINTS *)&mpParm1).x, (*(POINTS *)&mpParm1).y );
         break;

   #if 0
      case WM_BUTTON2CLICK:
         {
            HPS      hpsClient;
            POINTL   ptl;
            INT      xC, yC;


            xC = ( ( (*(POINTS *)&mpParm1).x - cxChar) / cxChar );
            yC = ( ( cyClient - (*(POINTS *)&mpParm1).y ) / cyChar );

            hpsClient = WinGetPS( hwndWnd );
            GpiSetColor( hpsClient, CLR_PALEGRAY );
            if ( xC < 10 )
               GpiSetMix( hpsClient, FM_XOR );
            else if ( xC < 20 )
               GpiSetMix( hpsClient, FM_INVERT );
            else if ( xC < 30 )
               GpiSetMix( hpsClient, FM_NOTXORSRC );
            else if ( xC < 40 )
               GpiSetMix( hpsClient, FM_NOTMASKSRC );
            else if ( xC < 50 )
               GpiSetMix( hpsClient, FM_SUBTRACT );
///            GpiSetBackColor( hpsClient, CLR_PALEGRAY );
///            GpiSetBackMix( hpsClient, BM_OVERPAINT );
///            ptl.x = ( ( (*(POINTS *)&mpParm1).x - cxChar ) / cxChar ) * cxChar + cxChar;
///            ptl.y = ( ( (*(POINTS *)&mpParm1).y - cyClient ) / cyChar - 1 ) * cyChar + cyClient;
            ptl.x = cxChar + ( xC * cxChar );
            ptl.y = cyClient - ( ( yC + 1) * cyChar );
            GpiMove( hpsClient, &ptl );
            ptl.x += cxChar;
            ptl.y += cyChar;
            if ( yC < 5 )
               GpiBox( hpsClient, DRO_FILL, &ptl, 0, 0 );
            else
               GpiBox( hpsClient, DRO_OUTLINE, &ptl, 0, 0 );
///            GpiSetBackColor( hpsClient, CLR_BACKGROUND );
///            GpiSetMix( hpsClient, FM_DEFAULT );
            WinReleasePS( hpsClient );
         }
         break;
   #endif

      case WM_CHAR:
         if ( !( CHARMSG(&ulMsg)->fs & KC_KEYUP ) )
         {
            if ( CHARMSG(&ulMsg)->fs & KC_CHAR )
            {
               ProcessCharMsg( hwndWnd, ulMsg, mpParm1, mpParm2 );
            }
            else if ( CHARMSG(&ulMsg)->fs & KC_VIRTUALKEY )
            {
               if ( !ProcessCursorMsg( hwndWnd, ulMsg, mpParm1, mpParm2 ) )
               {
                  return WinDefWindowProc( hwndWnd, ulMsg, mpParm1, mpParm2 );
               }
            }
         }
         break;

      case WM_CLOSE:
         if ( QueryAbandonChanges( hwndWnd ) )
            return WinDefWindowProc ( hwndWnd, ulMsg, mpParm1, mpParm2 );
         break;

      case WM_COMMAND:
         return ProcessCommandMsg( hwndWnd, ulMsg, mpParm1, mpParm2 );
         break;

      case WM_CREATE:
         hwndMenu = WinWindowFromID( WinQueryWindow( hwndWnd, QW_PARENT ), FID_MENU );
         hwndHScroll = WinWindowFromID( WinQueryWindow( hwndWnd, QW_PARENT ), FID_HORZSCROLL );
         hwndVScroll = WinWindowFromID( WinQueryWindow( hwndWnd, QW_PARENT ), FID_VERTSCROLL );
         SetWindowTitle( hwndWnd );
         break;

      case WM_DESTROY:
         ClearFile( hwndWnd );
         break;

      case WM_ERASEBACKGROUND:
         return MRFROMSHORT ( TRUE ) ;

      case WM_HELP:
         ProcessHelpMessage( hwndWnd, mpParm1, mpParm2 );
         break;

      case WM_HSCROLL:
         if ( !ProcessHScrollMsg( hwndWnd, ulMsg, mpParm1, mpParm2 ) )
            return WinDefWindowProc( hwndWnd, ulMsg, mpParm1, mpParm2 );
         break;

      case WM_PAINT:
         PaintScreen( hwndWnd );
         break;

      case WM_SAVEAPPLICATION:
         SaveSettings( hwndWnd, habAnchor );
         return WinDefWindowProc( hwndWnd, ulMsg, mpParm1, mpParm2 );
         break;

      case WM_SETFOCUS:
         if ( SHORT1FROMMP( mpParm2 ) )
            CreateCursor( hwndWnd );
         else
            DestroyCursor( hwndWnd );
         break;

      case WM_SIZE:
         UpdateWindowSize( hwndWnd, SHORT1FROMMP( mpParm2), SHORT2FROMMP( mpParm2 ) );
         if ( hwndWnd == WinQueryFocus( HWND_DESKTOP ) )
         {
            DestroyCursor( hwndWnd );
            CreateCursor( hwndWnd );
         }
         break;

      case WM_VSCROLL:
         if ( !ProcessVScrollMsg( hwndWnd, ulMsg, mpParm1, mpParm2 ) )
            return WinDefWindowProc( hwndWnd, ulMsg, mpParm1, mpParm2 );
         break;

      default:
         return WinDefWindowProc( hwndWnd, ulMsg, mpParm1, mpParm2 );
         break;
   }

   return MRFROMSHORT ( FALSE ) ;
}