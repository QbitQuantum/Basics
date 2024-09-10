LRESULT CALLBACK Main_WndProc(HWND hWnd,
                              UINT uMessage,
                              WPARAM wParam,
                              LPARAM lParam)
{
switch (uMessage)
   {
   case WM_NCCREATE:
      SHGetMalloc(&g_pMalloc);
      break;

   case WM_CREATE:
      {
      HIMAGELIST  himlLarge;
      HIMAGELIST  himlSmall;
      HWND        hwndTree;
      HWND        hwndList;

      g_uPosition = 0;
      
      //get the system image lists
      himlLarge = Main_CreateImageList(TRUE);
      himlSmall = Main_CreateImageList(FALSE);

      // create the TreeView control
      hwndTree = Tree_Create(g_hInst, hWnd, himlSmall);

      // create the ListView control
      hwndList = List_Create(g_hInst, hWnd, himlLarge, himlSmall);
      
      //initialize the TreeView control
      Tree_Init(hwndTree);

      SetFocus(hwndTree);
      }
      break;

   case WM_NOTIFY:
      {
      LPNMHDR  pnmh = (LPNMHDR) lParam;

      switch(pnmh->idFrom)
         {
         case IDC_TREEVIEW:
            return Tree_Notify(hWnd, lParam);
         
         case IDC_LISTVIEW:
            return List_Notify(hWnd, lParam);
         }
      }
      return 0;
   
   case WM_SIZE:
      {
      Main_SizeChildren(hWnd);
      }
      break;
   
   case WM_LBUTTONDOWN:
      SetCapture(hWnd);
      return 0;

   case WM_LBUTTONUP:
      ReleaseCapture();
      return 0;

   case WM_MOUSEMOVE:
      //if the left button is down
      if(GetKeyState(VK_LBUTTON) & 0x8000)
         {
         RECT  rc;

         GetClientRect(hWnd, &rc);

         //don't do anything if we are already at the minimum size
         if((g_uPosition == MIN_SIZE) && (LOWORD(lParam) <= MIN_SIZE))
            break;
         
         //don't do anything if we are already at the maximum size
         if(((rc.right - g_uPosition) == MIN_SIZE) && (LOWORD(lParam) >= g_uPosition))
            break;
         
         g_uPosition = LOWORD(lParam);

         //check for min and max
         if(g_uPosition < MIN_SIZE)
            g_uPosition = MIN_SIZE;

         if((rc.right - g_uPosition) < MIN_SIZE)
            g_uPosition = rc.right - MIN_SIZE;
         
         Main_SizeChildren(hWnd);
         }
      break;

   case WM_COMMAND:
      return Main_OnCommand(hWnd, wParam, lParam);

   case WM_DESTROY:
      //tell the list to release its current folder
      List_ReleaseCurrentFolder();
      
      PostQuitMessage(0);
      break;

   case WM_NCDESTROY:
      g_pMalloc->Release();
      g_pMalloc = NULL;
      break;
   
   case WM_SYSCOLORCHANGE:
      {
      HBRUSH   hbr = GetSysColorBrush(COLOR_3DFACE);

      hbr = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbr);

      if(hbr)
         DeleteObject(hbr);
      }
      break;
   
   case WM_INITMENUPOPUP:
      Main_UpdateMenu(hWnd, (HMENU)wParam);
      //fall through
   
   case WM_DRAWITEM:
   case WM_MENUCHAR:
   case WM_MEASUREITEM:
      if(g_pcm2)
         {
         g_pcm2->HandleMenuMsg(uMessage, wParam, lParam);
         }
      break;

   case WM_CONTEXTMENU:
      {
      POINT ptScreen;
      POINT ptClient;

      ptScreen.x = GET_X_LPARAM(lParam);
      ptScreen.y = GET_Y_LPARAM(lParam);
      ptClient = ptScreen;
      ScreenToClient(hWnd, &ptClient);
      HWND  hwndOver = ChildWindowFromPoint(hWnd, ptClient);

      if(GetDlgItem(hWnd, IDC_TREEVIEW) == hwndOver)
         {
         Tree_DoContextMenu(hwndOver, &ptScreen);
         }
      else if(GetDlgItem(hWnd, IDC_LISTVIEW) == hwndOver)
         {
         List_DoContextMenu(hwndOver, &ptScreen);
         }
      }
      break;
   
   default:
      break;
   }
return DefWindowProc(hWnd, uMessage, wParam, lParam);
}