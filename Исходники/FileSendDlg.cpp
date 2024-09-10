INT_PTR CALLBACK DlgProcSendFile(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct FileDlgData *dat;

	dat=(struct FileDlgData*)GetWindowLongPtr(hwndDlg,GWLP_USERDATA);
	switch (msg) {
	case WM_INITDIALOG:
	{
		struct FileSendData *fsd=(struct FileSendData*)lParam;

		dat=(struct FileDlgData*)mir_calloc(sizeof(struct FileDlgData));
		SetWindowLongPtr(hwndDlg,GWLP_USERDATA,(LONG_PTR)dat);
		dat->hContact=fsd->hContact;
		dat->send=1;
		dat->hPreshutdownEvent=HookEventMessage(ME_SYSTEM_PRESHUTDOWN,hwndDlg,M_PRESHUTDOWN);
		dat->fs=NULL;
		dat->dwTicks=GetTickCount();

		TranslateDialogDefault(hwndDlg);
		EnumChildWindows(hwndDlg,ClipSiblingsChildEnumProc,0);
		OldSendEditProc=(WNDPROC)SetWindowLongPtr(GetDlgItem(hwndDlg,IDC_MSG),GWLP_WNDPROC,(LONG_PTR)SendEditSubclassProc);

		Window_SetIcon_IcoLib(hwndDlg, SKINICON_EVENT_FILE);
		Button_SetIcon_IcoLib(hwndDlg, IDC_DETAILS, SKINICON_OTHER_USERDETAILS, LPGEN("View User's Details"));
		Button_SetIcon_IcoLib(hwndDlg, IDC_HISTORY, SKINICON_OTHER_HISTORY, LPGEN("View User's History"));
		Button_SetIcon_IcoLib(hwndDlg, IDC_USERMENU, SKINICON_OTHER_DOWNARROW, LPGEN("User Menu"));

        EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);

		if(fsd->ppFiles!=NULL && fsd->ppFiles[0]!=NULL) {
			int totalCount,i;
			for(totalCount=0;fsd->ppFiles[totalCount];totalCount++);
			dat->files = ( TCHAR** )mir_alloc( sizeof(TCHAR*)*(totalCount+1)); // Leaks
			for(i=0;i<totalCount;i++)
				dat->files[i] = mir_tstrdup( fsd->ppFiles[i] );
			dat->files[totalCount]=NULL;
			SetFileListAndSizeControls(hwndDlg,dat);
		}
		{
			char *szProto;
			TCHAR* contactName = cli.pfnGetContactDisplayName( dat->hContact, 0 );
			SetDlgItemText(hwndDlg,IDC_TO,contactName);

			szProto=(char*)CallService(MS_PROTO_GETCONTACTBASEPROTO,(WPARAM)dat->hContact,0);
			if (szProto) {
				CONTACTINFO ci;
				int hasName = 0;
				char buf[128];
				ZeroMemory(&ci,sizeof(ci));

				ci.cbSize = sizeof(ci);
				ci.hContact = dat->hContact;
				ci.szProto = szProto;
				ci.dwFlag = CNF_UNIQUEID;
				if (!CallService(MS_CONTACT_GETCONTACTINFO,0,(LPARAM)&ci)) {
					switch(ci.type) {
						case CNFT_ASCIIZ:
							hasName = 1;
							mir_snprintf(buf, SIZEOF(buf), "%s", ci.pszVal);
							mir_free(ci.pszVal);
							break;
						case CNFT_DWORD:
							hasName = 1;
							mir_snprintf(buf, SIZEOF(buf),"%u",ci.dVal);
							break;
				}	}

				if ( hasName )
					SetDlgItemTextA(hwndDlg,IDC_NAME,buf);
				else
					SetDlgItemText(hwndDlg,IDC_NAME,contactName);
		}	}

		if ( fsd->ppFiles == NULL ) {
       		EnableWindow(hwndDlg, FALSE);
			dat->closeIfFileChooseCancelled=1;
			PostMessage(hwndDlg,WM_COMMAND,MAKEWPARAM(IDC_CHOOSE,BN_CLICKED),(LPARAM)GetDlgItem(hwndDlg,IDC_CHOOSE));
		}
		return TRUE;
	}

	case WM_MEASUREITEM:
		return CallService(MS_CLIST_MENUMEASUREITEM,wParam,lParam);

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT dis=(LPDRAWITEMSTRUCT)lParam;
			if(dis->hwndItem==GetDlgItem(hwndDlg, IDC_PROTOCOL)) {
				char *szProto;

				szProto=(char*)CallService(MS_PROTO_GETCONTACTBASEPROTO,(WPARAM)dat->hContact,0);
				if (szProto) {
					HICON hIcon = (HICON)CallProtoService(szProto,PS_LOADICON,PLI_PROTOCOL|PLIF_SMALL,0);
					if (hIcon) {
						DrawIconEx(dis->hDC,dis->rcItem.left,dis->rcItem.top,hIcon,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0,NULL,DI_NORMAL);
						DestroyIcon(hIcon);
		}	}	}	}
		return CallService(MS_CLIST_MENUDRAWITEM,wParam,lParam);
		
	case M_FILECHOOSEDONE:
		if( lParam != 0 ) {
			FilenameToFileList( hwndDlg, dat, ( TCHAR* )lParam );
			mir_free(( TCHAR* )lParam );
			dat->closeIfFileChooseCancelled = 0;
		}
		else if(dat->closeIfFileChooseCancelled) DestroyWindow(hwndDlg);
		EnableWindow(hwndDlg,TRUE);
		break;

	case WM_COMMAND:
		if(CallService(MS_CLIST_MENUPROCESSCOMMAND,MAKEWPARAM(LOWORD(wParam),MPCF_CONTACTMENU),(LPARAM)dat->hContact))
			break;
		switch (LOWORD(wParam))
		{
			case IDC_CHOOSE:
				EnableWindow(hwndDlg,FALSE);
				//GetOpenFileName() creates its own message queue which prevents any incoming events being processed
				forkthread(ChooseFilesThread,0,hwndDlg);
				break;
			case IDOK:
				EnableWindow(GetDlgItem(hwndDlg,IDC_FILENAME),FALSE);
				EnableWindow(GetDlgItem(hwndDlg,IDC_MSG),FALSE);
				EnableWindow(GetDlgItem(hwndDlg,IDC_CHOOSE),FALSE);

				GetDlgItemText(hwndDlg,IDC_FILEDIR,dat->szSavePath,SIZEOF(dat->szSavePath));
				GetDlgItemText(hwndDlg,IDC_FILE,dat->szFilenames,SIZEOF(dat->szFilenames));
				GetDlgItemText(hwndDlg,IDC_MSG,dat->szMsg,SIZEOF(dat->szMsg));
				dat->hwndTransfer = FtMgr_AddTransfer(dat);
				SetWindowLongPtr( hwndDlg, GWLP_USERDATA, 0);
				DestroyWindow(hwndDlg);
				return TRUE;

			case IDCANCEL:
				DestroyWindow(hwndDlg);
				return TRUE;

			case IDC_USERMENU:
			{	RECT rc;
				HMENU hMenu=(HMENU)CallService(MS_CLIST_MENUBUILDCONTACT,(WPARAM)dat->hContact,0);
				GetWindowRect((HWND)lParam,&rc);
				TrackPopupMenu(hMenu,0,rc.left,rc.bottom,0,hwndDlg,NULL);
				DestroyMenu(hMenu);
				break;
			}
			case IDC_DETAILS:
				CallService(MS_USERINFO_SHOWDIALOG,(WPARAM)dat->hContact,0);
				return TRUE;
			case IDC_HISTORY:
				CallService(MS_HISTORY_SHOWCONTACTHISTORY,(WPARAM)dat->hContact,0);
				return TRUE;
		}
		break;

	case WM_DESTROY:
		Window_FreeIcon_IcoLib(hwndDlg);
		Button_FreeIcon_IcoLib(hwndDlg,IDC_DETAILS);
		Button_FreeIcon_IcoLib(hwndDlg,IDC_HISTORY);
		Button_FreeIcon_IcoLib(hwndDlg,IDC_USERMENU);

		if ( dat )
			FreeFileDlgData( dat );
		
		SetWindowLongPtr(GetDlgItem(hwndDlg,IDC_MSG),GWLP_WNDPROC,(LONG_PTR)OldSendEditProc);
		return TRUE;
	}
	return FALSE;
}