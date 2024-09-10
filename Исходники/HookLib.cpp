int MyHideWindows()
{
	NOTIFYICONDATA nid; 
	/*if(sOP.bUseBKMouse == 1)
	{
		MoveWindow2BK();
		return 1;;
	}*/

	if (bHideWindows == 1)	
	{
		if (sOP.bDisableSound == 1)
		{
			waveOutGetVolume(0,&dwOldVolume);
			waveOutSetVolume(0,0);
		}
		EnableWindow(hAll,FALSE);
		EnableWindow(hLV,FALSE);


		//EnumWindows((WNDENUMPROC)EnumWindowsFunc,0);
		for(int i1 = 0;i1<iBaSW_dll;i1++)
		{
			if (sW_dll[i1].bReserved != 1)
			{

				ShowWindow(sW_dll[i1].hWnd,SW_HIDE);
				sW_dll[i1].bHide = 1;
				if(sW_dll[i1].iHasTrayIcon == 1)
				{
					nid.cbSize = sizeof(NOTIFYICONDATA);
					nid.hWnd = sW_dll[i1].trayicon.hwnd;
					nid.uID = sW_dll[i1].trayicon.uID;
					Shell_NotifyIcon(NIM_DELETE,&nid);

				}
			}
		}   

		bHideWindows = 0;
	}
	else if (bHideWindows == 0)
	{
		if (sOP.bUsePassword == 1)
		{
			if(hDlg_Validate != NULL && IsWindow(hDlg_Validate))
			{
				return 1;
			}
			if (DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG_VALIDATE),NULL,(DLGPROC)ValidateProc) == 0)
			{
				return 1;
			}
		}

		EnableWindow(hAll,TRUE);
		EnableWindow(hLV,TRUE);

		if (dwOldVolume != 0)
		{
			waveOutSetVolume(0,dwOldVolume);
			dwOldVolume = 0;
		}
		//2.2 method ///
		for (int i = 0;i < iBaSW_dll;i++)
		{
			ShowWindow(sW_dll[i].hWnd,SW_SHOW);
			if(sW_dll[i].iHasTrayIcon == 1 && sW_dll[i].bHide == 1)
			{
				nid.cbSize           = sizeof(NOTIFYICONDATA);
				nid.uFlags           = NIF_ICON|NIF_TIP|NIF_MESSAGE;
				nid.uID              = sW_dll[i].trayicon.uID;
				nid.hIcon            = sW_dll[i].trayicon.hIcon;
				nid.hWnd             = sW_dll[i].trayicon.hwnd;
				strcpy(nid.szTip,(const char *)sW_dll[i].cIconTip);
				//wcstombs(nid.szTip,sW_dll[i].cIconTip,1022);
				nid.uCallbackMessage = sW_dll[i].trayicon.uCallbackMessage;
				Shell_NotifyIcon(NIM_ADD,&nid);				
			}
			sW_dll[i].bHide = 0;
		}
		bHideWindows = 1;


 
		/*iWin --;
		while(iWin >= 0)
		{
			ShowWindow(WindowsArray[iWin],SW_SHOW);
			iWin --;
		}
		iWin = 0;
		//pFT1->psNID ->hIcon = pFT1->hIcon1;
		//strcpy(pFT1->psNID ->szTip,"隐身专家(未隐藏窗口)");
		//Shell_NotifyIcon(NIM_MODIFY,pFT1->psNID);*/
	}
	return 1;
}