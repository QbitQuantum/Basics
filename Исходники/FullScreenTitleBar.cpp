LRESULT CALLBACK CTitleBar::WndProc(HWND hwnd, UINT iMsg, 
					   WPARAM wParam, LPARAM lParam)
{
	// Added Jef Fix
    CTitleBar *TitleBarThis=NULL;
    TitleBarThis = helper::SafeGetWindowUserData<CTitleBar>(hwnd);

	switch (iMsg)
	{

	case WM_CREATE:
		return 0;

	case WM_PAINT:
			TitleBarThis->Draw();
			return 0;

	case WM_CLOSE:
		{
			HWND Window=TitleBarThis->GetSafeHwnd();
			TitleBarThis->FreePictures();
			DestroyWindow(Window);
//			vnclog.Print(0,_T(" Q6 \n"));
//			PostQuitMessage(0);
			return 0;
		}

	case WM_DESTROY:
			TitleBarThis->FreePictures();
//			vnclog.Print(0,_T(" Q7 \n"));
//			PostQuitMessage(0);
			return 0;

	case WM_DRAWITEM:
		{
			HDC hdcMem; 
			LPDRAWITEMSTRUCT lpdis; 

            lpdis = (LPDRAWITEMSTRUCT) lParam; 
            hdcMem = CreateCompatibleDC(lpdis->hDC); 
			HGDIOBJ hbrOld=NULL;
 
			if(lpdis->CtlID==tbIDC_CLOSE)
					hbrOld=SelectObject(hdcMem, TitleBarThis->hClose); 
			if(lpdis->CtlID==tbIDC_MAXIMIZE)
					hbrOld=SelectObject(hdcMem, TitleBarThis->hMaximize); 
			if(lpdis->CtlID==tbIDC_MINIMIZE)
					hbrOld=SelectObject(hdcMem, TitleBarThis->hMinimize); 
			
			if(lpdis->CtlID==tbIDC_PIN)
			{
				if(TitleBarThis->AutoHide==TRUE)
					hbrOld=SelectObject(hdcMem, TitleBarThis->hPinUp); 
				else
					hbrOld=SelectObject(hdcMem, TitleBarThis->hPinDown); 
			}

			BitBlt(lpdis->hDC,
					lpdis->rcItem.left,
					lpdis->rcItem.top,
	                lpdis->rcItem.right - lpdis->rcItem.left, 
					lpdis->rcItem.bottom - lpdis->rcItem.top, 
	                hdcMem,
					0,
					0,
					SRCCOPY);
			if (hbrOld) SelectObject(hdcMem,hbrOld);
            DeleteDC(hdcMem); 
            return TRUE; 
		}

	case WM_COMMAND: 
		if (HIWORD(wParam) == BN_CLICKED)
		{
			//Handle the Pin for holding the window
			if(LOWORD(wParam) == tbIDC_PIN)
			{
				if(TitleBarThis->AutoHide==TRUE)
				{
					TitleBarThis->AutoHide=FALSE;
					TitleBarThis->DisplayWindow(TRUE);
				}
				else
				{
					TitleBarThis->AutoHide=TRUE;
					TitleBarThis->DisplayWindow(FALSE);
				}

				//Redraw window to show the new gfx...
				::RedrawWindow(TitleBarThis->Pin, NULL, NULL, TRUE);
			}

			//If default = true we'll send usally showwindow and close messages
			if(tbDefault==TRUE)
			{
				if(LOWORD(wParam) == tbIDC_CLOSE)
					::SendMessage(TitleBarThis->Parent, WM_CLOSE, NULL, 0);
				if(LOWORD(wParam) == tbIDC_MAXIMIZE)
				{
					//if(::IsZoomed(TitleBarThis->Parent)==TRUE)
						ShowWindow(TitleBarThis->Parent, SW_RESTORE);
					/*else
						ShowWindow(TitleBarThis->Parent, SW_MAXIMIZE);*/
				}
				if(LOWORD(wParam) == tbIDC_MINIMIZE)
					ShowWindow(TitleBarThis->Parent, SW_MINIMIZE);
			}
			else //default = false - send custom message on buttons
			{
				if(LOWORD(wParam) == tbIDC_CLOSE)
					::SendMessage(TitleBarThis->Parent, tbWM_CLOSE, NULL, NULL);
				if(LOWORD(wParam) == tbIDC_MAXIMIZE)
					::SendMessage(TitleBarThis->Parent, tbWM_MAXIMIZE, NULL, NULL);
				if(LOWORD(wParam) == tbIDC_MINIMIZE)
					::SendMessage(TitleBarThis->Parent, tbWM_MINIMIZE, NULL, NULL);
			}
        }

		//Menu part starts here
		{
			UINT IDNum=LOWORD(wParam);
		
			if(IDNum>=tbWMCOMMANDIDStart&&IDNum<tbWMCOMMANDIDEnd) //The ID is in range for a menuclick
			{
				UINT Num=IDNum-tbWMCOMMANDIDStart;

				//When the close,minimize, maximize is not present just send! :)
				if(tbLastIsStandard==FALSE)
					::SendMessage(TitleBarThis->Parent, WM_USER+tbWMUSERID+Num, NULL,NULL);
				else //Handle close, minimize and maximize
				{
					HMENU Menu=LoadMenu(TitleBarThis->hInstance,MAKEINTRESOURCE (tbMENUID));
					HMENU SubMenu=GetSubMenu(Menu,0);;

					UINT Total=0;

					//Get the real number of entries (exluding seperators)
					for(int i=0;i<GetMenuItemCount(SubMenu);i++)
					{
						int res=::GetMenuString(SubMenu, i, NULL, 0, MF_BYPOSITION);
						if(res!=0)
							Total++;
					}

					if(Num==Total-1) //Close button
						::SendMessage(TitleBarThis->m_hWnd,WM_COMMAND,MAKEWPARAM(tbIDC_CLOSE,BN_CLICKED),NULL);
					else if(Num==Total-2) //Minimize button
						::SendMessage(TitleBarThis->m_hWnd,WM_COMMAND,MAKEWPARAM(tbIDC_MINIMIZE,BN_CLICKED),NULL);
					else if(Num==Total-3) //Maximize button
						::SendMessage(TitleBarThis->m_hWnd,WM_COMMAND,MAKEWPARAM(tbIDC_MAXIMIZE,BN_CLICKED),NULL);
					else
						::SendMessage(TitleBarThis->Parent, WM_USER+tbWMUSERID+Num, NULL,NULL);

					DestroyMenu (SubMenu);
					DestroyMenu (Menu);
				}
			}
		}

        break;
	
	case WM_MOUSEMOVE:
			if(TitleBarThis->HideAfterSlide==FALSE)
			{
				TitleBarThis->SlideDown=TRUE;
				::SetTimer(TitleBarThis->m_hWnd, tbScrollTimerID, 20, NULL);
			}
		break;

	case WM_LBUTTONDBLCLK:
			//If the default entries on the context menu is activated then doubleclick is restore :)
			if(tbLastIsStandard==TRUE)
				::SendMessage(TitleBarThis->m_hWnd,WM_COMMAND,MAKEWPARAM(tbIDC_MAXIMIZE,BN_CLICKED),NULL);
		break;

	case WM_RBUTTONDOWN:
		{
			HMENU Menu=LoadMenu(TitleBarThis->hInstance,MAKEINTRESOURCE (tbMENUID));
			HMENU SubMenu=GetSubMenu(Menu,0);;

			POINT  lpPoint;
			::GetCursorPos(&lpPoint);

			int Pos=0;

			//Set ID values to each item
			for(int i=0;i<GetMenuItemCount(SubMenu);i++)
			{
				TCHAR Text[MAX_PATH];
				ZeroMemory(Text,sizeof(Text));
				int res=::GetMenuString(SubMenu, i, Text, MAX_PATH, MF_BYPOSITION);
				
				if(res!=0)
				{
					::ModifyMenu(SubMenu,i,MF_BYPOSITION, tbWMCOMMANDIDStart+Pos,Text);
					Pos++;
				}
			}

			//Loop through each item from pos to set the default value on restore
			if(tbLastIsStandard==TRUE)
			{
				int RealPos=0;
				for(int i=0;i<GetMenuItemCount(SubMenu);i++)
				{
					TCHAR Text[MAX_PATH];
					ZeroMemory(Text,sizeof(Text));
					int res=::GetMenuString(SubMenu, i, Text, MAX_PATH, MF_BYPOSITION);
					
					if(res!=0)
					{
						RealPos++;

						if(RealPos==Pos-2)
						::SetMenuDefaultItem(SubMenu, i, TRUE);
					}
				}
			}

			TrackPopupMenu(SubMenu,TPM_LEFTALIGN, lpPoint.x, lpPoint.y, 0, TitleBarThis->m_hWnd, NULL);

			SetForegroundWindow (TitleBarThis->m_hWnd);
			DestroyMenu (SubMenu);
			DestroyMenu (Menu);

			break;
		}

	case WM_TIMER:
		{
			UINT TimerID=(UINT)wParam;
			
			if(TimerID==tbScrollTimerID)
			{
				RECT lpRect;
				::GetWindowRect(TitleBarThis->m_hWnd, &lpRect);

				if( ((lpRect.top==0)&&(TitleBarThis->SlideDown==TRUE))
					||
					((lpRect.top==-tbHeigth+1)&&(TitleBarThis->SlideDown==FALSE)))
				{
					KillTimer(TitleBarThis->m_hWnd, tbScrollTimerID);

					if(TitleBarThis->HideAfterSlide==TRUE)
					{
						TitleBarThis->HideAfterSlide=FALSE;
						ShowWindow(TitleBarThis->GetSafeHwnd(), SW_HIDE);
					}
					return 0;
				}

				if(TitleBarThis->SlideDown==TRUE)
				{
					lpRect.top++; lpRect.bottom++;
				}
				else
				{
					lpRect.top--; lpRect.bottom--;
				}

				::MoveWindow(TitleBarThis->m_hWnd, lpRect.left, lpRect.top, lpRect.right-lpRect.left, lpRect.bottom-lpRect.top, TRUE);
			}

			//Check mouse cordinates and hide if the mouse haven't been in the window for a few seconds
			if(TimerID==tbAutoScrollTimer)
			{
				RECT lpRect;
				POINT pt;
				::GetWindowRect(TitleBarThis->m_hWnd, &lpRect);
				::GetCursorPos(&pt);

				if(PtInRect(&lpRect, pt)==FALSE) 
				{
					TitleBarThis->IntAutoHideCounter++;

					if(TitleBarThis->IntAutoHideCounter==tbAutoScrollTime)
					{
						TitleBarThis->SlideDown=FALSE;
						::SetTimer(TitleBarThis->m_hWnd, tbScrollTimerID, tbScrollDelay, NULL);
					}
				}
				else
				{
					TitleBarThis->IntAutoHideCounter=0;
				}
			}

			break;
		}
	}//Case - end
	
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}