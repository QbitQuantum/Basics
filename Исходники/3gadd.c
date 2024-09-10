static int Desktop(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	char cwd[MAX_PATH + 1];

        //DEB("-Desktop: \n ");

	switch (message) {
	case MSG_CREATE:
	{
                DEB("--MSG_CREATE\n ");	
                /*	
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_3G_NOW_LISTBOX_FILE,
			     10, 30, 100, 100,
			     hWnd,
			     0);
*/
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_3G_NOW_LISTBOX_FILE,
			     10, 30, 100, 100,
			     hWnd,
			     0);
			     
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_3G_ADD_LISTBOX_FILE,
			     110, 30, 100, 100,
			     hWnd,
			     0);

		CreateWindow(CTRL_STATIC,
			     MSG_PATH,
			     WS_VISIBLE | SS_SIMPLE,
			     IDC_FUN_MPLAYER_MUSICADD_STATIC_PATH,
			     10, 10, 130, 15,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_DOWNLOAD,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_MUSICADD_BUTTON_CHOOSE,
			     230, 50, 70, 25,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_CANCEL,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_MUSICADD_BUTTON_CANCEL,
			     230, 100, 50, 25,
			     hWnd,
			     0);

		SetNotificationCallback(GetDlgItem(hWnd, IDC_FUN_3G_NOW_LISTBOX_FILE), now_notif_proc);
		SetNotificationCallback(GetDlgItem(hWnd, IDC_FUN_3G_ADD_LISTBOX_FILE), file_notif_proc);
		fill_boxes(hWnd, getcwd(cwd, MAX_PATH));
	}
	break;

	case MSG_COMMAND:
	{
                DEB("--MSG_COMMAND hWnd=%d\n ,hWnd");	
		switch (wParam)	{
		case IDC_FUN_MPLAYER_MUSICADD_BUTTON_CHOOSE:
                        DEB("---IDC_FUN_MPLAYER_MUSICADD_BUTTON_CHOOSE\n ");		
			fn_3gFileSave(hWnd);
                                     	
			DEB("---SendNotifyMessage fWnd=%d\n ",fWnd);
			SendNotifyMessage(fWnd, MSG_MUSIC_ADD, 0, 0L);
			DEB("---SendNotifyMessage end\n ");			
			break;

		case IDC_FUN_MPLAYER_MUSICADD_BUTTON_CANCEL:
                        DEB("---IDC_FUN_MPLAYER_MUSICADD_BUTTON_CANCEL\n ");		
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			return 0;
		}
                DEB("--MSG_COMMAND END\n ");		
	}
	break;

	case MSG_CLOSE:
	{
                DEB("--MSG_CLOSE\n ");	
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
	}
	}
	
	
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}