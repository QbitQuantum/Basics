LRESULT APIENTRY ProToolsProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LONG_PTR				action = 0, command = 0, hitArea = 0, styleChg = 0;
	pLL					currentLink, prevLink;
	RECT				rect,	clientRect, workingAreaRect;
	LONG_PTR				x = 0, y = 0, xFrame, yFrame;
	INT_PTR					mnuItemCount, i;
	HMENU				hMenu;
	BOOL				bFuncReturn;
	LPMINMAXINFO		lpmmi; //01/18/03
	static LONG_PTR			InCommand = 0; // 01/18/03
	POINT				pt; // 01/19/03
	LPWINDOWPOS			lpwp;
	LPNCCALCSIZE_PARAMS	lpcalcsize;
	static HWND			currentChildMaxed = NULL, prevChildMaxed = NULL;
	//char*				minimizedWindows[32];
	char				title[128];
	INT_PTR					n = 0, err = 0;
	INT_PTR					minimizedPerRow; // REB 8/11/08 #16207

	currentLink = NULL;
	prevLink = NULL;

	if (toolBarRestrictions.toolBarOnDeck == 1) { // 01/17/03

		xFrame = GetSystemMetrics(SM_CXSIZEFRAME);
		yFrame = GetSystemMetrics(SM_CYSIZEFRAME);
		// REB 8/11/08 #16207
		minimizedPerRow = ((GetSystemMetrics(SM_CXVIRTUALSCREEN) - (toolBarRestrictions.clientOffsetx + toolBarRestrictions.left + toolBarRestrictions.right)) / GetSystemMetrics(SM_CXMINSPACING));
		//err = GetWindowText(hwnd, title , 128); //**DEBUG**
		switch (uMsg)
		{
			case WM_SYSCOMMAND : //this tells a subsequent WM_GETMINMAXINFO command
				// that it is okay to proceed if we are in the process of a maximize command.
				command = wParam & 0xFFF0;
				if (SC_MAXIMIZE == command) {
					InCommand = IN_SYSCOMMAND_MAX;
					GetWindowRect(hwnd, &toolBarRestrictions.origWindowRect);
					GetWindowRect(windowHandles.MDIhWnd, &rect);
					toolBarRestrictions.clientOffsetx = rect.left;
					toolBarRestrictions.clientOffsety = rect.top;
					currentChildMaxed = hwnd;
					if (IsZoomed(hwnd) == 0){ // REB 8/11/08 #16207
						//minimizePositions[toolBarRestrictions.numMinimized] = 0;		
						err = GetWindowText(hwnd, title , 128);				
						for (n=0; n < SMLBUF; n++) {
							if(strcmp(toolBarRestrictions.minimizedWindows[n], title) == 0){
								strcpy(toolBarRestrictions.minimizedWindows[n], "");
								//break;
							}
						}
					}
				}
				// REB 8/11/08 #16207
				if  (SC_MINIMIZE == command) {
					InCommand = IN_SYSCOMMAND_MIN;
					GetWindowRect(hwnd, &toolBarRestrictions.origWindowRect);
					GetWindowRect(windowHandles.MDIhWnd, &rect);

					//Debug
					//GetWindowRect(windowHandles.MDIs_4DhWnd, &rect);
					//GetWindowRect(windowHandles.fourDhWnd, &rect);
					//End Debug

					toolBarRestrictions.clientOffsetx = rect.left;
					toolBarRestrictions.clientOffsety = rect.top;					
				}

				if (SC_RESTORE == command) { //|| (toolBarRestrictions.appBeingMaxed > 0)) {
					InCommand = IN_SYSCOMMAND_RESTORE;
					if (IsZoomed(hwnd) != 0){ // REB 8/11/08 #16207 Only clear these if we are restoring a window that was already maximized.
						currentChildMaxed = NULL;
						// REB 3/26/10 #22878 Move the previous window back.
						MoveWindow(prevChildMaxed, toolBarRestrictions.previousWindowRect.left, toolBarRestrictions.previousWindowRect.top, (toolBarRestrictions.previousWindowRect.right - toolBarRestrictions.previousWindowRect.left), (toolBarRestrictions.previousWindowRect.bottom - toolBarRestrictions.previousWindowRect.top), 1);
						prevChildMaxed = NULL;
					}else{
						err = GetWindowText(hwnd, title , 128);				
						for (n=0; n < SMLBUF; n++) {
							if(strcmp(toolBarRestrictions.minimizedWindows[n], title) == 0){
								strcpy(toolBarRestrictions.minimizedWindows[n], "");
								//break;
							}
						}
					}
					toolBarRestrictions.appBeingMaxed = 0;
				}
				//if (SC_NEXTWINDOW == command) {
					//toolBarRestrictions.appBeingMaxed = XCHANGING_MAX_WINDOWS;
				//}


				if (SC_CLOSE == command) {
					if (IsZoomed(hwnd) == 0){ // REB 8/11/08 #16207	
						err = GetWindowText(hwnd, title , 128);				
						for (n=0; n < SMLBUF; n++) {
							if(strcmp(toolBarRestrictions.minimizedWindows[n], title) == 0){
								strcpy(toolBarRestrictions.minimizedWindows[n], "");
								//break;
							}
						}
					}
					break;
				};

				break;

			case WM_WINDOWPOSCHANGING :

				lpwp = (LPWINDOWPOS)lParam;

				GetWindowRect(windowHandles.MDIhWnd, &rect);

				if  ((InCommand == IN_SYSCOMMAND_MAX) && (toolBarRestrictions.appWindowState == APP_MAXIMIZED)) {

					lpwp->x = lpwp->x - toolBarRestrictions.clientOffsetx - toolBarRestrictions.left;
					lpwp->y = lpwp->y - toolBarRestrictions.clientOffsety - toolBarRestrictions.top - yFrame;
					lpwp->cx = toolBarRestrictions.origWindowRect.right - toolBarRestrictions.origWindowRect.left;
					lpwp->cy = toolBarRestrictions.origWindowRect.bottom - toolBarRestrictions.origWindowRect.top;
					return 0;
				}
				// REB 8/11/08 #16207
				if  ((InCommand == IN_SYSCOMMAND_MIN) ){  // Minimizing the windows
					err = GetWindowText(hwnd, title , 128);				
					for (n=0; n < SMLBUF; n++) {
						if((strcmp(toolBarRestrictions.minimizedWindows[n], "") == 0) || (strcmp(toolBarRestrictions.minimizedWindows[n], title) == 0)){
							strcpy(toolBarRestrictions.minimizedWindows[n], title);
							break;
						}
					}

					lpwp->x = toolBarRestrictions.clientOffsetx + toolBarRestrictions.left + ((n % minimizedPerRow)  * GetSystemMetrics(SM_CXMINSPACING));
				
					SystemParametersInfo(SPI_GETWORKAREA, 0, &workingAreaRect, 0);
					lpwp->y = workingAreaRect.bottom - yFrame - toolBarRestrictions.clientOffsety - toolBarRestrictions.bottom - (((n  / (minimizedPerRow) ) + 1) * GetSystemMetrics(SM_CYMINSPACING));
					
					return 0;
				}

				if  ((toolBarRestrictions.appBeingMaxed == APP_MAXIMIZING) ||
						 (toolBarRestrictions.appBeingMaxed == APP_RESTORING) ||
						 (toolBarRestrictions.appBeingMaxed == APP_SIZING_W_CHLDMAX)) {
					
					lpwp->x = toolBarRestrictions.left - xFrame;
					lpwp->y = toolBarRestrictions.top - yFrame;
					lpwp->cx = rect.right - rect.left + (2 * xFrame) - toolBarRestrictions.left - toolBarRestrictions.right;
					lpwp->cy = rect.bottom - rect.top + (2 * yFrame) - toolBarRestrictions.top - toolBarRestrictions.bottom;
					return 0;
				}

				if (currentChildMaxed == hwnd) { //(toolBarRestrictions.appBeingMaxed == (LONG_PTR)hwnd) {
					lpwp->x = toolBarRestrictions.left - xFrame;
					lpwp->y = toolBarRestrictions.top - yFrame;
					lpwp->cx = rect.right - rect.left + (2 * xFrame) - toolBarRestrictions.left - toolBarRestrictions.right;
					lpwp->cy = rect.bottom - rect.top + (2 * yFrame) - toolBarRestrictions.top - toolBarRestrictions.bottom;
					return 0;
				}
				break;

			case WM_GETMINMAXINFO :
				if ((InCommand == IN_SYSCOMMAND_MAX) || (toolBarRestrictions.appBeingMaxed > 0) ||
						(currentChildMaxed == hwnd) ) {
						
					lpmmi = (LPMINMAXINFO) lParam;
						
					lpmmi->ptMaxSize.x = lpmmi->ptMaxSize.x - toolBarRestrictions.left - toolBarRestrictions.right;
					lpmmi->ptMaxSize.y = lpmmi->ptMaxSize.y - toolBarRestrictions.top - toolBarRestrictions.bottom;
					lpmmi->ptMaxPosition.x  = - xFrame + toolBarRestrictions.left; // maxPosition x&y seem to be static values -- hmmm!
					lpmmi->ptMaxPosition.y  = - yFrame + toolBarRestrictions.top;
					lpmmi->ptMaxTrackSize.x = lpmmi->ptMaxTrackSize.x - toolBarRestrictions.left - toolBarRestrictions.right;
					lpmmi->ptMaxTrackSize.y = lpmmi->ptMaxTrackSize.y - toolBarRestrictions.top - toolBarRestrictions.bottom;
						
					return 0; // return 0 telling OS that we have processed this command
				} // end if 
				break;

			case WM_NCCALCSIZE :
				if ( ((currentChildMaxed != NULL) || (prevChildMaxed != NULL)) && ((BOOL)wParam == TRUE) ) {
					lpcalcsize = (LPNCCALCSIZE_PARAMS)lParam;
					lpwp = lpcalcsize->lppos;
					rect = lpcalcsize->rgrc[0];
					clientRect = lpcalcsize->rgrc[1];
					toolBarRestrictions.appBeingMaxed = 0; //new
				}
				break;

			case WM_NCACTIVATE :
				if ((currentChildMaxed != NULL) && (currentChildMaxed != hwnd)) {
					//bFuncReturn = IsZoomed(currentChildMaxed);
					// REB 3/26/10 #22878 Here we need to capture the size of the newly activated window before it's resized to the max.
					// This window will become the new original window and we'll save the previous window position to be resized later.
					if (wParam){ 
						toolBarRestrictions.previousWindowRect = toolBarRestrictions.origWindowRect;
						GetWindowRect(hwnd, &toolBarRestrictions.origWindowRect);
						prevChildMaxed = currentChildMaxed;
						currentChildMaxed = hwnd;
					}
					toolBarRestrictions.appBeingMaxed = (LONG_PTR)currentChildMaxed; //was XCHANGING_MAX_WINDOWS
				}
				break;

			case WM_SETFOCUS : // msg received by window getting focus
					//if (prevChildMaxed == (HWND)wParam) { 
					//use the following in lieu of XCHANGING.. to restore all on window change
					//SendMessage((HWND)wParam, WM_SYSCOMMAND, SC_RESTORE, 0L);
					//use this to keep maxed window when using CRTL-TAB.  But 4D has an ugy bug in window
					//  resize when called from a menu (Bring to Front).
					//toolBarRestrictions.appBeingMaxed = XCHANGING_MAX_WINDOWS;	
				break;


			case WM_SIZE :
					if (toolBarRestrictions.appBeingMaxed != APP_SIZING_W_CHLDMAX) {
						toolBarRestrictions.appBeingMaxed = 0;
					}
					InCommand = 0;
				break;


			case WM_SIZING : 
			case WM_MOVING : // restrict sizing or moving to prevent
				GetClientRect(windowHandles.MDIhWnd, &clientRect);
				//clientRect.right contains width of client area
				//clientRect.bottom contains height of client area
				//convert this rect to screen coordinates for comparison to movingRect
				pt.x = clientRect.left;
				pt.y = clientRect.top;
				ClientToScreen(windowHandles.MDIhWnd, &pt);
				clientRect.left = pt.x;
				clientRect.top = pt.y;
				pt.x = clientRect.right;
				pt.y = clientRect.bottom;
				ClientToScreen(windowHandles.MDIhWnd, &pt);
				clientRect.right = pt.x;
				clientRect.bottom = pt.y;
				
				clientRect.left += toolBarRestrictions.left;
				if (toolBarRestrictions.trackingRestriction == 0) {
					clientRect.top += toolBarRestrictions.top;
				} else {
					clientRect.top += toolBarRestrictions.trackingRestriction;
				}
				clientRect.right -= toolBarRestrictions.right;
				clientRect.bottom -= toolBarRestrictions.bottom;
				ClipCursor(&clientRect);
				break;


			case WM_EXITSIZEMOVE :
				rect.left		= 0;
				rect.top		= 0;
				rect.right	= GetSystemMetrics(SM_CXVIRTUALSCREEN);// REB 6/6/08 #16838 (Fix Provided by Keith White)
				rect.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);// REB 6/6/08 #16838 (Fix Provided by Keith White)
				ClipCursor(&rect);
				break;
			default :
				if((uMsg!=WM_ERASEBKGND)&&(uMsg!=WM_NCPAINT)&&(uMsg!=WM_PAINT)&&(uMsg!=WM_IME_SETCONTEXT)&&(uMsg!=WM_IME_NOTIFY)&&(uMsg!=WM_SETFOCUS)&&(uMsg!=WM_NCACTIVATE)&&(uMsg!=WM_KILLFOCUS)&&(uMsg!=WM_GETTEXT)){
					break;
				};
		} // end switch (uMsg)
	} // end if (toolBarRestrictions.toolBarOnDeck == 1)



	if (startOfList != NULL) {

		if ((uMsg == WM_SYSCOMMAND) || (uMsg == WM_NCHITTEST) || (uMsg == WM_INITMENU)) {

			if (search_list( &startOfList, &currentLink, &prevLink, LL_hWnd, LL_Restrict, (LONG_PTR *) &hwnd)) {
		
				action = currentLink->dataLong1;

				switch (uMsg)
				{
					case (WM_SYSCOMMAND) :
						command = wParam & 0xFFF0;
						switch (command)
						{
							case (SC_SIZE) :
								if (RW_NO_SIZE == (action & RW_NO_SIZE)) {
									wParam = 0x000F;
								}
								break;

							case (SC_MOVE) :
								if (RW_NO_MOVE == (action & RW_NO_MOVE)) {
									wParam = 0x000F;
								}
								break;

							case (SC_MINIMIZE) :
								if (RW_NO_MIN == (action & RW_NO_MIN)) {
									wParam = 0x000F;
								}
								break;

							case (SC_MAXIMIZE) :
								if (RW_NO_MAX == (action & RW_NO_MAX)) {
									wParam = 0x000F;
								}
								break;
						}  // end switch

						break;

					case (WM_NCHITTEST) :
						if (RW_NO_SIZE == (action & RW_NO_SIZE)) {
							hitArea = DefWindowProc(hwnd, uMsg, wParam, lParam);
							if ((hitArea >= HTLEFT) && (hitArea <= HTBOTTOMRIGHT)) {
								uMsg = HTNOWHERE;
							} else {
								// test for coordinates of lower right 
								GetWindowRect(hwnd, &rect);
								x = LOWORD (lParam);
								y = HIWORD (lParam);
								if ((x <= rect.right) && (x >= (rect.right - 25 )) &&
									(y <= rect.bottom) && (y >= (rect.bottom - 25))) {
									uMsg = HTNOWHERE;
								}
							}
						}
						break;

					case (WM_INITMENU):

						hMenu = GetSystemMenu(hwnd, FALSE);

						if (RW_NO_SIZE == (action & RW_NO_SIZE)) {
							bFuncReturn = EnableMenuItem(hMenu, SC_SIZE, MF_BYCOMMAND | MF_GRAYED);
						}
						if (RW_NO_MOVE == (action & RW_NO_MOVE)) {
							bFuncReturn = EnableMenuItem(hMenu, SC_MOVE, MF_BYCOMMAND | MF_GRAYED);
						}
						if (RW_NO_MIN == (action & RW_NO_MIN)) {
							bFuncReturn = EnableMenuItem(hMenu, SC_MINIMIZE, MF_BYCOMMAND | MF_GRAYED);
						}
						if (RW_NO_MAX == (action & RW_NO_MAX)) {
							bFuncReturn = EnableMenuItem(hMenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED);
						}
						if (RW_NO_NEXT == (action & RW_NO_NEXT)) {
							mnuItemCount = GetMenuItemCount(hMenu);
							for (i = (mnuItemCount - 1); i >= 0; i--)
							{
								if (GetMenuItemID(hMenu, i) == SC_NEXTWINDOW) {
									bFuncReturn = DeleteMenu(hMenu, SC_NEXTWINDOW, MF_BYCOMMAND);
									// is next higher menu item a separator line?
									if (GetMenuItemID(hMenu, i - 1) == 0) {
										bFuncReturn = DeleteMenu(hMenu, i - 1, MF_BYPOSITION);	
									}
								} else if (GetMenuItemID(hMenu, i) == SC_PREVWINDOW) {
									bFuncReturn = DeleteMenu(hMenu, SC_PREVWINDOW, MF_BYCOMMAND);
									// is next higher menu item a separator line?
									if (GetMenuItemID(hMenu, i - 1) == 0) {
										bFuncReturn = DeleteMenu(hMenu, i - 1, MF_BYPOSITION);	
									}
								}
							}
						} // end if (RW_NO_NEXT == (action & RW_NO_NEXT))

						break;

					case (WM_DESTROY) :
						delete_list(&startOfList, LL_hWnd, LL_Restrict, (LONG_PTR *) &hwnd);
						break;

				} // end switch (uMsg)
			} // end if (search_list( &startOfList, &currentLink, &prevLink, LL_hWnd, LL_Restrict, (LONG_PTR *) &hwnd))
		} // end if ((uMsg == WM_SYSCOMMAND) || (uMsg == WM_NCHITTEST) || (uMsg == WM_INITMENU))
	} // end if (startOfList != NULL)
	

	return CallWindowProc(processHandles.wpProToolsOrigProc, hwnd, uMsg, wParam, lParam);

}