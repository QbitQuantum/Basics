LRESULT CALLBACK Explorerplusplus::TabSubclassProc(HWND hTab,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITMENU:
			OnInitTabMenu(wParam);
			SendMessage(m_hContainer,WM_INITMENU,wParam,lParam);
			break;

		case WM_MENUSELECT:
			/* Forward the message to the main window so it can
			handle menu help. */
			SendMessage(m_hContainer,WM_MENUSELECT,wParam,lParam);
			break;

		case WM_MEASUREITEM:
			SendMessage(m_hContainer,WM_MEASUREITEM,wParam,lParam);
			break;

		case WM_DRAWITEM:
			SendMessage(m_hContainer,WM_DRAWITEM,wParam,lParam);
			break;

		case WM_LBUTTONDOWN:
			OnTabCtrlLButtonDown(wParam,lParam);
			break;

		case WM_LBUTTONUP:
			OnTabCtrlLButtonUp();
			break;

		case WM_MOUSEMOVE:
			OnTabCtrlMouseMove(wParam,lParam);
			break;

		case WM_MBUTTONUP:
			SendMessage(m_hContainer,WM_APP_TABMCLICK,wParam,lParam);
			break;

		case WM_RBUTTONUP:
			OnTabCtrlRButtonUp(wParam,lParam);
			break;

		case WM_CAPTURECHANGED:
			{
				if((HWND)lParam != hTab)
					ReleaseCapture();

				m_bTabBeenDragged = FALSE;
			}
			break;

		case WM_LBUTTONDBLCLK:
			{
				TCHITTESTINFO info;
				int ItemNum;
				DWORD dwPos;
				POINT MousePos;

				dwPos = GetMessagePos();
				MousePos.x = GET_X_LPARAM(dwPos);
				MousePos.y = GET_Y_LPARAM(dwPos);
				ScreenToClient(hTab,&MousePos);

				/* The cursor position will be tested to see if
				there is a tab beneath it. */
				info.pt.x	= LOWORD(lParam);
				info.pt.y	= HIWORD(lParam);

				ItemNum = TabCtrl_HitTest(m_hTabCtrl,&info);

				if(info.flags != TCHT_NOWHERE && m_bDoubleClickTabClose)
				{
					CloseTab(ItemNum);
				}
			}
			break;

		case WM_NCDESTROY:
			RemoveWindowSubclass(m_hTabCtrl,TabSubclassProcStub,0);
			break;
	}

	return DefSubclassProc(hTab,msg,wParam,lParam);
}