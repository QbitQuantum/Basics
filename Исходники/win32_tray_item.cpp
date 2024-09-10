	/*static*/
	bool Win32TrayItem::MessageHandler(
		HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == trayClickedMessage)
		{
			UINT button = (UINT) lParam;
			int id = LOWORD(wParam);
			bool handled = false;

			for (size_t i = 0; i < trayItems.size(); i++)
			{
				AutoPtr<Win32TrayItem> item = trayItems[i];

				item->is_double_clicked = false;
				if(item->GetId() == id && button == WM_LBUTTONDBLCLK)
				{
					item->is_double_clicked = true;
					KillTimer(hWnd, 100);
					item->HandleDoubleLeftClick();
					handled = true;
				}
				if (item->GetId() == id && button == WM_LBUTTONDOWN)
				{
					SetTimer(hWnd, 100, GetDoubleClickTime(), (TIMERPROC)DoubleClickTimerProc); 
					handled = true;
				}
				else if (item->GetId() == id && button == WM_RBUTTONDOWN)
				{
					item->HandleRightClick();
					handled = true;
				}
			}
			return handled;
		}
		else if (message == WM_MENUCOMMAND)
		{
			HMENU nativeMenu = (HMENU) lParam;
			UINT position = (UINT) wParam;
			return Win32MenuItem::HandleClickEvent(nativeMenu, position);
		}
		else
		{
			// Not handled;
			return false;
		}
	}