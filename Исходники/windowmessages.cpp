//Invis Dialog
LRESULT CALLBACK InvisDialogProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT s_uTaskbarRestart;
    switch (message)                  /* handle the messages */
    {
        case WM_INITDIALOG:
            SetClassLong(hwnd,GCL_HICON,(long) LoadIcon(thisinstance,"A"));
            SetClassLong(hwnd,GCL_HICONSM,(long) LoadIcon(thisinstance,"A"));
            s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));
            
            return false;
            break;
        case WM_NOTIFYICON:
			if ((UINT)lParam == WM_RBUTTONUP){
            	POINT cord;
            	GetCursorPos(&cord);
            	HMENU menu;
            	menu = CreatePopupMenu();
            	AppendMenu(menu,MF_ENABLED|MF_STRING, ID_MENU_ABOUT,"&About");
				AppendMenu(menu,MF_ENABLED|MF_STRING, ID_MENU_HELP,"&Help");
            	AppendMenu(menu,MF_ENABLED|MF_STRING, ID_MENU_SETT,"Se&ttings");
            	AppendMenu(menu,MF_ENABLED|MF_STRING, ID_MENU_STATUS,"&Status");
            	AppendMenu(menu,MF_ENABLED|MF_STRING, ID_MENU_EXIT,"&Exit");
            	SetForegroundWindow(hwnd);
            	TrackPopupMenu(menu,TPM_RIGHTALIGN,cord.x,cord.y,0,hwnd,NULL);
            	DestroyMenu(menu);
            	PostMessage(hwnd, WM_NULL, 0, 0);
        	}
        	else if ((UINT)lParam == WM_LBUTTONDBLCLK)
        	{
				PostMessage(hwnd,WM_COMMAND,ID_MENU_STATUS,0);
			}    
            return 0;
            break;
        case WM_CLOSE:
        case WM_RQUIT:
			Windowlessquit = true;
			PostQuitMessage(0);
			break;
//			/*
		case WM_ENDSESSION:
			Windowlessquit = true;
			PostQuitMessage(0);
			return 0;
//			*/
		case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case ID_MENU_EXIT:
					Windowlessquit = true;
					PostQuitMessage (0);
                    break;
                case ID_MENU_STATUS:
					Stat.Create();
					break;
				case ID_MENU_SETT:
					Sett.Create();
					break;
				case ID_MENU_HELP:
                    WinHelp(hwnd,"HELP.HLP",HELP_FINDER,0);
                    break;
                case ID_MENU_ABOUT:
					if (!IsWindow(Aboutwnd)) 
                	{
                    	Aboutwnd = CreateDialog(thisinstance,MAKEINTRESOURCE(IDD_ABOUT),NULL,(DLGPROC)AboutDialogProcedure);
                    	ShowWindow(Aboutwnd,SW_SHOW);
                	}    
                	SetForegroundWindow(Aboutwnd);
                	break;
			}
			return 0;
            break;
        default:
			if( message == s_uTaskbarRestart)
			{
				hGlobalIcon->Remove();
				Sleep(500);
				hGlobalIcon->Add();
				break;
			}
            return false;
    }
    return 0;
}