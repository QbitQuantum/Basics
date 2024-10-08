void CluiProtocolStatusChanged( int parStatus, const char* szProto )
{
	int protoCount,i;
	PROTOACCOUNT **accs;
	int *partWidths,partCount;
	int borders[3];
	int status;
	int toshow;
	wchar_t *szStatus = NULL;
	char *szMaxProto = NULL;
	int maxOnline = 0, onlineness = 0;
	WORD maxStatus = ID_STATUS_OFFLINE, wStatus = ID_STATUS_OFFLINE;
	DBVARIANT dbv = {0};
	int iIcon = 0;
	HICON hIcon = 0;
	int rdelta = Skin::metrics.cLeft + Skin::metrics.cRight;
	BYTE windowStyle;

	if (pcli->hwndStatus == 0 || cfg::shutDown)
		return;

	Proto_EnumAccounts( &protoCount, &accs );
	if (protoCount == 0)
		return;

	FreeProtocolData();
	cfg::maxStatus = ID_STATUS_OFFLINE;
	g_maxProto[0] = 0;

	SendMessage(pcli->hwndStatus,SB_GETBORDERS,0,(LPARAM)&borders);

	partWidths=(int*)_alloca(( protoCount+1)*sizeof(int));

	if (cfg::dat.bEqualSections) {
		RECT rc;
		int part;
		GetClientRect(pcli->hwndStatus,&rc);
		rc.right-=borders[0]*2;
		toshow=0;
		for ( i=0; i < protoCount; i++ )
			if ( pcli->pfnGetProtocolVisibility( accs[i]->szModuleName ))
				toshow++;

		if ( toshow > 0 ) {
			for ( part=0, i=0; i < protoCount; i++ ) {
				if ( !pcli->pfnGetProtocolVisibility( accs[i]->szModuleName ))
					continue;

				partWidths[ part ] = ((rc.right-rc.left-rdelta)/toshow)*(part+1) + Skin::metrics.cLeft;
				if ( part == toshow-1 )
					partWidths[ part ] += Skin::metrics.cRight;
				part++;
			}
		}
		partCount=toshow;
	}
	else {
		HDC hdc;
		SIZE textSize;
		BYTE showOpts = cfg::getByte("CLUI","SBarShow",1);
		int x;
		HFONT hofont;
		wchar_t szName[32];
		PROTOACCOUNT* pa;

		hdc=GetDC(NULL);
		hofont = reinterpret_cast<HFONT>(SelectObject(hdc,(HFONT)SendMessage(pcli->hwndStatus,WM_GETFONT,0,0)));

		for ( partCount=0,i=0; i < protoCount; i++ ) {      //count down since built in ones tend to go at the end
			int idx = pcli->pfnGetAccountIndexByPos( i );
			if ( idx == -1 )
				continue;

			pa = accs[idx];
			if ( !pcli->pfnGetProtocolVisibility( pa->szModuleName ))
				continue;

			x=2;
			if (showOpts & 1)
				x += 16;
			if (showOpts & 2) {
				lstrcpyn( szName, pa->tszAccountName, _countof(szName));
				szName[ _countof(szName)-1 ] = 0;
				if (( showOpts & 4 ) && lstrlen(szName) < sizeof(szName)-1 )
					lstrcat( szName, _T(" "));
				GetTextExtentPoint32( hdc, szName, lstrlen(szName), &textSize );
				x += textSize.cx + GetSystemMetrics(SM_CXBORDER) * 4; // The SB panel doesnt allocate enough room
			}
			if (showOpts & 4) {
				wchar_t* modeDescr = pcli->pfnGetStatusModeDescription( CallProtoService(accs[i]->szModuleName,PS_GETSTATUS,0,0 ), 0 );
				GetTextExtentPoint32(hdc, modeDescr, lstrlen(modeDescr), &textSize );
				x += textSize.cx + GetSystemMetrics(SM_CXBORDER) * 4; // The SB panel doesnt allocate enough room
			}
			partWidths[partCount]=(partCount?partWidths[partCount-1]:Skin::metrics.cLeft)+ x + 2;
			partCount++;
		}
		SelectObject(hdc,hofont);
		ReleaseDC(NULL,hdc);
	}
	if (partCount==0) {
		SendMessage(pcli->hwndStatus,SB_SIMPLE,TRUE,0);
		return;
	}
	SendMessage(pcli->hwndStatus,SB_SIMPLE,FALSE,0);

	partWidths[partCount-1]=-1;
	windowStyle = Skin::metrics.bWindowStyle;
	//SendMessage(pcli->hwndStatus,SB_SETMINHEIGHT, 12 + ((windowStyle == SETTING_WINDOWSTYLE_THINBORDER || windowStyle == SETTING_WINDOWSTYLE_NOBORDER) ? 3 : 0), 0);
	SendMessage(pcli->hwndStatus, SB_SETPARTS, partCount, (LPARAM)partWidths);

	for ( partCount=0, i=0; i < protoCount; i++ ) {      //count down since built in ones tend to go at the end
		ProtocolData *PD;
		PROTOACCOUNT *pa;
		int caps1, caps2;

		int idx = pcli->pfnGetAccountIndexByPos( i );
		if ( idx == -1 )
			continue;

		pa = accs[idx];
		if ( !pcli->pfnGetProtocolVisibility( pa->szModuleName ))
			continue;

		status = CallProtoService( pa->szModuleName,PS_GETSTATUS,0,0);
		PD = ( ProtocolData* )mir_alloc(sizeof(ProtocolData));
		PD->RealName = mir_strdup( pa->szModuleName );
		PD->protopos = partCount;
		{
			int flags;
			flags = SBT_OWNERDRAW;
			if ( cfg::getByte("CLUI","SBarBevel", 1)==0 )
				flags |= SBT_NOBORDERS;
			SendMessageA( pcli->hwndStatus, SB_SETTEXTA, partCount|flags,(LPARAM)PD );
		}
		caps2 = CallProtoService(pa->szModuleName, PS_GETCAPS, PFLAGNUM_2, 0);
		caps1 = CallProtoService(pa->szModuleName, PS_GETCAPS, PFLAGNUM_1, 0);
		if((caps1 & PF1_IM) && (caps2 & (PF2_LONGAWAY | PF2_SHORTAWAY))) {
			onlineness = CLC::getStatusOnlineness(status, false);
			if(onlineness > maxOnline) {
				maxStatus = status;
				maxOnline = onlineness;
				szMaxProto = pa->szModuleName;
			}
		}
		partCount++;
	}
	// update the clui button

	if (!db_get(NULL, "CList", "PrimaryStatus", &dbv)) {
		if (dbv.type == DBVT_ASCIIZ && lstrlenA(dbv.pszVal) > 1) {
			wStatus = (WORD) CallProtoService(dbv.pszVal, PS_GETSTATUS, 0, 0);
			iIcon = CLC::IconFromStatusMode(dbv.pszVal, (int) wStatus, 0, &hIcon);
		}
		mir_free(dbv.pszVal);
	} else {
		wStatus = maxStatus;
		iIcon = CLC::IconFromStatusMode((wStatus >= ID_STATUS_CONNECTING && wStatus < ID_STATUS_OFFLINE) ? szMaxProto : NULL, (int) wStatus, 0, &hIcon);
		cfg::maxStatus = (int)wStatus;
		if(szMaxProto) {
			lstrcpynA(g_maxProto, szMaxProto, 100);
			g_maxProto[99] = 0;
		}
	}
	/*
	* this is used globally (actually, by the clist control only) to determine if
	* any protocol is "in connection" state. If true, then the clist discards redraws
	* and uses timer based sort and redraw handling. This can improve performance
	* when connecting multiple protocols significantly.
	*/
	//g_isConnecting = (wStatus >= ID_STATUS_CONNECTING && wStatus < ID_STATUS_OFFLINE);

	szStatus = pcli->pfnGetStatusModeDescription(wStatus, 0);

	/*
	* set the global status icon and display the global (most online) status mode on the
	* status mode button
	*/

	if (szStatus) {
		if(pcli->hwndContactList && IsWindow(GetDlgItem(pcli->hwndContactList, IDC_TBGLOBALSTATUS)) && IsWindow(GetDlgItem(pcli->hwndContactList, IDC_TBTOPSTATUS))) {
			SendMessage(GetDlgItem(pcli->hwndContactList, IDC_TBGLOBALSTATUS), WM_SETTEXT, 0, (LPARAM) szStatus);
			if(!hIcon) {
				SendMessage(GetDlgItem(pcli->hwndContactList, IDC_TBGLOBALSTATUS), BM_SETIMLICON, (WPARAM) CLC::hClistImages, (LPARAM) iIcon);
                if(CLUI::buttonItems == NULL)
                    SendMessage(GetDlgItem(pcli->hwndContactList, IDC_TBTOPSTATUS), BM_SETIMLICON, (WPARAM) CLC::hClistImages, (LPARAM) iIcon);
			}
			else {
				SendMessage(GetDlgItem(pcli->hwndContactList, IDC_TBGLOBALSTATUS), BM_SETIMAGE, IMAGE_ICON, (LPARAM) hIcon);
                if(CLUI::buttonItems == NULL)
                    SendMessage(GetDlgItem(pcli->hwndContactList, IDC_TBTOPSTATUS), BM_SETIMAGE, IMAGE_ICON, (LPARAM) hIcon);
			}
			InvalidateRect(GetDlgItem(pcli->hwndContactList, IDC_TBGLOBALSTATUS), NULL, TRUE);
			InvalidateRect(GetDlgItem(pcli->hwndContactList, IDC_TBTOPSTATUS), NULL, TRUE);
			SFL_Update(hIcon, iIcon, CLC::hClistImages, szStatus, TRUE);
	}	}
    return;
}