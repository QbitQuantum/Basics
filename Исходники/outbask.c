/* This function creates the out-basket window.
 */
BOOL FASTCALL CreateOutBasket( HWND hwnd )
{
   DWORD dwState;
   RECT rc;

   /* If outbasket window already open, bring it to the front
    * and display it.
    */
   if( hwndOutBasket )
      {
      Adm_MakeMDIWindowActive( hwndOutBasket );
      return( TRUE );
      }

   /* Register the out-basket window class if we have
    * not already done so.
    */
   if( !fRegistered )
      {
      WNDCLASS wc;

      wc.style          = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc    = OutBasketWndProc;
      wc.hIcon          = LoadIcon( hRscLib, MAKEINTRESOURCE(IDI_OUTBASKET) );
      wc.hCursor        = LoadCursor( NULL, IDC_ARROW );
      wc.lpszMenuName   = NULL;
      wc.cbWndExtra     = MWE_EXTRA;
      wc.cbClsExtra     = 0;
      wc.hbrBackground  = NULL;
      wc.lpszClassName  = szOutBaskWndClass;
      wc.hInstance      = hInst;
      if( !RegisterClass( &wc ) )
         return( FALSE );
      fRegistered = TRUE;
      }

   /* The default position of the out-basket.
    */
   GetClientRect( hwndMDIClient, &rc );
   rc.left = rc.right / 3;
   InflateRect( &rc, -5, -5 );
   dwState = 0;

   /* Load the out-basket bitmaps.
    */
   hbmpOutBasket = LoadBitmap( hRscLib, MAKEINTRESOURCE(IDB_OUTBASKETBMPS) );

   /* Get the actual window size, position and state.
    */
   ReadProperWindowState( szOutBaskWndName, &rc, &dwState );

   if( hwndActive && IsMaximized( hwndActive ) )
      dwState = WS_MAXIMIZE;

         
   /* Create the window.
    */
   hwndOutBasket = Adm_CreateMDIWindow( szOutBaskWndName, szOutBaskWndClass, hInst, &rc, dwState, 0L );
   if( NULL == hwndOutBasket )
      return( FALSE );
   UpdateWindow( hwndOutBasket );

   /* Set the initial focus.
    */
   OutBasket_OnSetFocus( hwndOutBasket, NULL );
   UpdateOutBasketStatus();
   return( TRUE );

}