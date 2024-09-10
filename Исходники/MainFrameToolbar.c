void Toolbar_UpdateUI(
  HWND hwnd)
  {
   HWND hwndFrame;
   HMENU hmenu;
   unsigned nCount;

   /*=======================================*/
   /* Get frame window (parent of toolbar). */
   /*=======================================*/
   
   hwndFrame = GetParent(hwnd);
   ASSERT(NULL != hwndFrame);

   /*===================================*/
   /* Get the main frame window's menu. */
   /*===================================*/
   
   hmenu = GetMenu(hwndFrame);
   //ASSERT (NULL != hmenu) ;

   if (NULL == hmenu)
     { return; }

   /*======================================*/
   /* Get count of buttons on the toolbar. */
   /*======================================*/
   
   nCount = Toolbar_ButtonCount(hwnd);

   /*===================================*/
   /* For each button on the toolbar... */
   /*===================================*/
   
   while (nCount > 0) 
     {
      BOOL bMenuEnabled, bButtonEnabled;
      TBBUTTON tbb;
      UINT uiState;

      /*===================================*/
      /* Get information about the button. */
      /*===================================*/
      
      VERIFY(Toolbar_GetButton(hwnd,--nCount,&tbb));

      /*==========================================*/
      /* If the button is a separator, ignore it. */
      /*==========================================*/
      
      if (tbb.fsStyle & TBSTYLE_SEP)
        { continue; }

      /*=========================================*/
      /* Get information about the corresponding */
      /* menu item, if any.                      */
      /*=========================================*/
      
      uiState = GetMenuState(hmenu,(unsigned) tbb.idCommand,MF_BYCOMMAND);
      if (0xFFFFFFFF == uiState)
        { bMenuEnabled = FALSE; }
      else
        { bMenuEnabled = 0 == (uiState & (MF_DISABLED | MF_GRAYED)); }

      bButtonEnabled = 0 != (tbb.fsState & TBSTATE_ENABLED);

      /*===========================================*/
      /* If button and menu are in the same state, */
      /* we need do nothing for this button.       */
      /*===========================================*/
      
      if (bMenuEnabled == bButtonEnabled)
        { continue; }

      /*=====================================*/
      /* Enable/Disable this toolbar button. */
      /*=====================================*/
      
      VERIFY(Toolbar_EnableButton(hwnd,tbb.idCommand,bMenuEnabled));
     }
  }