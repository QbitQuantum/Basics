INT_PTR CALLBACK TrackingUIProc(HWND hwndTrk, UINT message, WPARAM wParam, LPARAM lParam)
{ 	
	switch (message)
	{ 
    case WM_INITDIALOG:
		{
			g_hWndTrack = hwndTrk;
		
			LVCOLUMN column;
			column.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
			column.cx = 50;
			column.iSubItem = 0;
			column.pszText = L"ID";
			ListView_InsertColumn(GetControl(IDC_MODELS), 0, &column);
			column.cx = 400;
			column.iSubItem = 1;
			column.pszText = L"File";
			ListView_InsertColumn(GetControl(IDC_MODELS), 1, &column);
				
			HIMAGELIST imgList = ImageList_Create(16, 16, 0, 2, 0);
		
			HBITMAP trackingBmp	   = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TRACKING_OK));
			HBITMAP notTrackingBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NOT_TRACKING));
				
			ImageList_Add(imgList, notTrackingBmp, NULL);
			ImageList_Add(imgList, trackingBmp, NULL);

			TreeView_SetImageList(GetControl(IDC_MODELS), imgList, TVSIL_NORMAL);

			DeleteObject(trackingBmp);
			DeleteObject(notTrackingBmp);
		
			// Initialize combo tracking box	
			ComboBox_AddString(GetControl(IDC_TRACKINGTYPE), L"3D Tracking");
			ComboBox_SetItemData(GetControl(IDC_TRACKINGTYPE), 0, TRACKING_3D);
			ComboBox_AddString(GetControl(IDC_TRACKINGTYPE), L"2D Tracking");
			ComboBox_SetItemData(GetControl(IDC_TRACKINGTYPE), 1, TRACKING_2D);
			ComboBox_AddString(GetControl(IDC_TRACKINGTYPE), L"3D Instant");
			ComboBox_SetItemData(GetControl(IDC_TRACKINGTYPE), 2, TRACKING_INSTANT);
			ComboBox_SetCurSel(GetControl(IDC_TRACKINGTYPE), 0);
		
			return TRUE; 
		}

	case WM_COMMAND:
        switch (LOWORD(wParam))
		{		
		case IDC_LOADMODEL:
			AddTargetFile();
			return TRUE;
		case IDC_CLEARMODELS:
			ClearModelTree();
			return TRUE;
        }
		
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			HWND comboBox = (HWND) lParam;
			int selIndex = ComboBox_GetCurSel(comboBox);
			TrackingType type = (TrackingType) ComboBox_GetItemData(comboBox, selIndex);

			switch (type)
			{
			case TRACKING_2D:
				Button_Enable(GetControl(IDC_START), false);
				Button_Enable(GetControl(IDC_LOADMODEL), true);
				Button_Enable(GetControl(IDC_CLEARMODELS), false);
				Button_Enable(GetControl(IDC_ROI), false);
				Button_SetCheck(GetControl(IDC_ROI), false);
				ClearModelTree();
				return TRUE;		
			case TRACKING_3D:				
				Button_Enable(GetControl(IDC_START), false);
				Button_Enable(GetControl(IDC_LOADMODEL), true);
				Button_Enable(GetControl(IDC_CLEARMODELS), false);
				Button_Enable(GetControl(IDC_ROI), false);
				Button_SetCheck(GetControl(IDC_ROI), false);
				ClearModelTree();			
				return TRUE;
			case TRACKING_INSTANT:				
				ClearModelTree();
				Button_Enable(GetControl(IDC_START),true);
				Button_Enable(GetControl(IDC_LOADMODEL),false);
				Button_Enable(GetControl(IDC_CLEARMODELS), false);
				Button_Enable(GetControl(IDC_ROI), true);
				Button_SetCheck(GetControl(IDC_ROI), false);

				if (!showedMessage)
				{
					showedMessage = true;
					MessageBoxExW(GetParent(hwndTrk), L"Please be aware that instant tracking needs special scene/background setup. Refer to the reference manual for details.", L"Note", MB_OK | MB_ICONINFORMATION, 0);
				}
				return TRUE;
			}
		}
		break;
	case WM_NOTIFY:		
		switch ( ((LPNMHDR) lParam)->code)
		{
			case TVN_GETDISPINFO:
			{
				NMTVDISPINFO *dispInfo = (NMTVDISPINFO*) lParam;			
		
				if (dispInfo->item.mask & LVIF_IMAGE)
				{				
					int targetIndex = dispInfo->item.lParam & 0xFF;
					int cosIDIndex  = (dispInfo->item.lParam & 0xFF00) >> 8;

					if (g_targets[targetIndex].cosIDs[cosIDIndex].isTracking)
					{
						dispInfo->item.iImage = 1;
					}
					else
					{
						dispInfo->item.iImage = 0;
					}				
				}
				return TRUE;
			}			
		}
		break;	
    } 