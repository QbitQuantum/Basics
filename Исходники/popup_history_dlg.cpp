//subclass proc for the list view
BOOL CALLBACK PopupsListSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CONTEXTMENU:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			int selection;		
			
			HMENU hMenu = CreatePopupMenu();
			AppendMenu(hMenu, MF_STRING, POPUPMENU_TITLE, TranslateT("Copy title to clipboard"));
			AppendMenu(hMenu, MF_STRING, POPUPMENU_MESSAGE, TranslateT("Copy message to clipboard"));
			AppendMenu(hMenu, MF_STRING, POPUPMENU_TIMESTAMP, TranslateT("Copy timestamp to clipboard"));
			selection = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, x, y, 0, hWnd, NULL);
			DestroyMenu(hMenu);
			if (selection)
			{
				CopyPopupDataToClipboard(hWnd, selection);
			}
		
			break;
		}
		
		case WM_KEYUP:
		{
			switch (wParam)
			{
				case 'C':
				{
					if (GetKeyState(VK_CONTROL))
					{
						CopyPopupDataToClipboard(hWnd, POPUPMENU_MESSAGE);
					}
					
					break;
				}
				
				case VK_ESCAPE:
				{
					SendMessage(GetParent(hWnd), WM_CLOSE, 0, 0);
					
					break;
				}
				
			}
			 
			break;
		}
		
		case WM_SYSKEYDOWN:
		{
			if (wParam == 'X')
			{
				SendMessage(GetParent(hWnd), WM_CLOSE, 0, 0);
			}
			
			break;
		}
	}
	
	return CallWindowProc(oldPopupsListProc, hWnd, msg, wParam, lParam);
}