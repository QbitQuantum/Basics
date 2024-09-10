LRESULT CALLBACK MainWndProc ( HWND hWnd, UINT message,
                               WPARAM wParam, LPARAM lParam )
{
   HDC            hDC;
   PAINTSTRUCT    ps;
   DLGPROC        dlgProcAbout;
   int            i;
   int            j;
   short          y;


   switch ( message )
   {
      case WM_CREATE:
         hDC = GetDC ( hWnd );

         GetTextMetrics ( hDC, &tm );
         cxChar = tm.tmAveCharWidth;
         cyChar = tm.tmHeight + tm.tmExternalLeading;

         ReleaseDC ( hWnd, hDC );

         lpDdeProc = MakeProcInstance ( (FARPROC) DDECallback, hInst );
         if ( DdeInitialize ( (LPDWORD)&idInst, (PFNCALLBACK)lpDdeProc,
                              APPCMD_CLIENTONLY, 0L ) )
         {
            HandleOutput ( "Client DDE initialization failure." );
            return ( FALSE );
         }

         hszService = DdeCreateStringHandle ( idInst, "Borland", CP_WINANSI );
         hszTopic = DdeCreateStringHandle ( idInst, "DDEExample", CP_WINANSI );
         hszItem = DdeCreateStringHandle ( idInst, "DDEData", CP_WINANSI );

         cCurrentLine = 0;
         cTotalLines = 0;

         strcpy ( szDDEString, "Client application message number:  " );
         break;

      case WM_COMMAND:
         switch ( wParam )
         {
            case IDM_EXIT:
               DestroyWindow ( hWnd );
               break;

            case IDM_CONNECT_SERVER:
               if ( hConv == NULL )
               {
                  hConv = DdeConnect ( idInst, hszService, hszTopic,
                                       (PCONVCONTEXT) NULL );
                  if ( hConv == NULL )
                  {
                     HandleError ( DdeGetLastError ( idInst ) );
                     HandleOutput ( "Unsuccessful connection." );
                  }
                  else
                     HandleOutput ( "Successful connection." );
               }
               else
                  HandleOutput ( "Already connected to DDE Server." );

               break;

            case IDM_DISCONNECT_SERVER:
               if ( hConv != NULL )
               {
                  DdeDisconnect ( hConv );
                  hConv = NULL;
                  HandleOutput ( "Disconnected from server." );
               }
               else
                  HandleOutput ( "Must be connected before disconnecting." );

               break;

            case IDM_MSG_TO_SERVER:
               if ( hConv != NULL )
               {
                  iClientCount ++;
                  sprintf ( tbuf, "%3d.", iClientCount );
                  strncpy ( &szDDEString[36], tbuf, 5 );

                  hData = DdeCreateDataHandle ( idInst, &szDDEString,
                           sizeof ( szDDEString ), 0L, hszItem, wFmt, 0 );

                  if ( hData != NULL )
            		  hData = DdeClientTransaction ( (LPBYTE)hData, -1, hConv,
                               hszItem, wFmt, XTYP_POKE, 1000, &dwResult );
                  else
                     HandleOutput ( "Could not create data handle." );
               }
               else
                  HandleOutput ( "A connection to a DDE Server has not been established." );

               break;

            case IDM_MSG_FROM_SERVER:
               if ( hConv != NULL )
               {
                  hData = DdeClientTransaction ( NULL, 0, hConv,
                               hszItem, wFmt, XTYP_REQUEST, 1000, &dwResult );

                  if ( dwResult == DDE_FNOTPROCESSED )
                     HandleOutput ( "Data not available from server." );
                  else
                  {
                     DdeGetData ( hData, (LPBYTE) szDDEData, 80L, 0L );

                     if ( szDDEData != NULL )
                        HandleOutput ( szDDEData );
                     else
                        HandleOutput ( "Message from server is null." );
                  }
               }
               else
                  HandleOutput ( "A connection to a DDE Server has not been established." );

               break;

            case IDM_ABOUT:
               dlgProcAbout = (DLGPROC) MakeProcInstance ( (FARPROC)About, hInst );
               DialogBox ( hInst, "AboutBox", hWnd, dlgProcAbout );
               FreeProcInstance ( (FARPROC) dlgProcAbout );
               break;

            default:
               return ( DefWindowProc ( hWnd, message, wParam, lParam ) );
         }
         break;

      case WM_PAINT:
         hDC = BeginPaint ( hWnd, &ps );

         y = 0;

         for ( i = 0; i < cTotalLines; i ++ )
         {
            if ( cTotalLines == 8 )
               j = ( (cCurrentLine + 1 + i) % 9 );
            else
               j = i;         // can't do this if we clear window and start in middle of array

            TextOut ( hDC, 0, y, (LPSTR)(szScreenText[j]),
                                 lstrlen ( szScreenText[j] ) );
            y = y + cyChar;
         }

         EndPaint ( hWnd, &ps );
         break;

      case WM_DESTROY:
         if ( hConv != NULL )
         {
            DdeDisconnect ( hConv );
            hConv = NULL;
         }

         DdeFreeStringHandle ( idInst, hszService );
         DdeFreeStringHandle ( idInst, hszTopic );
         DdeFreeStringHandle ( idInst, hszItem );

         FreeProcInstance ( lpDdeProc );

         PostQuitMessage ( 0 );
         break;

      default:
         return ( DefWindowProc ( hWnd, message, wParam, lParam ) );
   }

   return ( FALSE );
}