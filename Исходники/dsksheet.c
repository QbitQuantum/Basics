//-------------------------------------------------------------
//	Message cracking functions
//.............................................................
void Cls_OnDiskCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
//	handles WM_COMMAND
{
	DWORD			bufSize,
					dwResult,
					dwCapacity,
//					dwCapBefore,
					dwFree, 
					dwPercent;
	int				ccode;
	TCHAR			str[256];
	TCHAR            title[128];
	TCHAR			buffer[512];
	PeripheralDisk	periphDisk;

	switch(codeNotify)
	{ 
		case LBN_DBLCLK:
			switch (id)
			{
			  case IDC_FONTLIST:
			  	FORWARD_WM_COMMAND(hwnd, IDC_FONT_DETAILS, GetDlgItem(hwnd, IDC_FONT_DETAILS), BN_CLICKED, SendMessage);
			  	break;
			}
			break;

		case BN_CLICKED:
			switch (id)
			{
			  case IDC_INITIALIZE:
				if ( oldWriteProtect IS WP_READ )
				{
					LoadString(hInstance, IDS_INIT_WRITE_PROTECT, str, SIZEOF_IN_CHAR(str));
					LoadString(hInstance, IDS_PRTR_TITLE, title, SIZEOF_IN_CHAR(title));
					ccode = MessageBox(GetParent(hDisk), str, title, MB_OK | MB_ICONEXCLAMATION);
					ccode = IDNO;
				}
				else if ( bDiskInitialized )
				{
					LoadString(hInstance, IDS_INIT_WARNING, str, SIZEOF_IN_CHAR(str));
					LoadString(hInstance, IDS_PRTR_TITLE, title, SIZEOF_IN_CHAR(title));
					ccode = MessageBox(GetParent(hDisk), str, title, MB_YESNO | MB_ICONQUESTION);
				}
				else
				{
					LoadString(hInstance, IDS_INIT_WARNING2, str, SIZEOF_IN_CHAR(str));
					LoadString(hInstance, IDS_PRTR_TITLE, title, SIZEOF_IN_CHAR(title));
					ccode = MessageBox(GetParent(hDisk), str, title, MB_YESNO | MB_ICONQUESTION);
				}
				if ( ccode IS IDYES )
				{ 	//  initialize disk
					HWND	hwndChild;
					periphDisk.flags = 0;
					periphDisk.flags |= SET_INITIALIZE;
					bufSize = sizeof(PeripheralDisk);
					dwResult = PALSetComponentObject(hPeripheral, hComponent, 
						OT_PERIPHERAL_DISK, 0, &periphDisk, &bufSize);
					if (dwResult IS RC_SUCCESS) {

						LoadString(hInstance, IDS_DISK_INIT_SUCCESS, str, SIZEOF_IN_CHAR(str));
						LoadString(hInstance, IDS_PRTR_TITLE, title, SIZEOF_IN_CHAR(title));
						ccode = MessageBox(GetParent(hDisk), str, title, MB_OK);

						if (hwndChild = GetDlgItem(hwnd, IDC_FONTLIST))
						{
							ListBox_ResetContent(hwndChild);
						}
						EnableWindow(GetDlgItem(hDisk, IDC_FONT_DETAILS), FALSE);
						EnableWindow(GetDlgItem(hDisk, IDC_FONT_DELETE), FALSE);
						
						bufSize = sizeof(PeripheralDisk);
						memset(&periphDisk, 0, (size_t)bufSize);
						dwResult = PALGetComponentObject(hPeripheral, hComponent, 
							OT_PERIPHERAL_DISK, 0, &periphDisk, &bufSize);
						if (dwResult IS RC_SUCCESS) {
							dwCapacity = (DWORD)(periphDisk.capacity / 1024L);
							dwFree = (DWORD)(periphDisk.freeSpace / 1024L);
							// the initialize may have been queued and the reported
							// free space may be the old (pre initialize) size.  If
							// so, assume that the file system takes 157 K bytes.
							if (dwFree < dwCapacity - 157) 
								dwFree = dwCapacity - 157;
							dwPercent = dwFree * 100 / dwCapacity;
							LoadString(hInstance, IDS_TOTAL_SIZE, str, SIZEOF_IN_CHAR(str));
							wsprintf(buffer, str, dwCapacity);
							SetDlgItemText(hDisk, IDC_TOTAL_SIZE, buffer);
							LoadString(hInstance, IDS_FREE_SPACE, str, SIZEOF_IN_CHAR(str));
							wsprintf(buffer, str, dwFree, dwPercent);
							SetDlgItemText(hDisk, IDC_FREE_SPACE, buffer);
							SetWindowWord(GetDlgItem(hDisk, IDC_FREE_SPACE), GWW_TRAYLEVEL, (WORD)dwPercent);
							CheckDlgButton(hDisk, IDC_FS_INITIALIZED, TRUE);
							// Set the init check box so that users cannot check/uncheck it
							EnableWindow(GetDlgItem(hDisk, IDC_FS_INITIALIZED), FALSE);
							bDiskInitialized = TRUE;
						}
					}
				}
				break;

			  // If Write Protected was checked and the disk is not write protected
			  // Disable or enable the initialize button
			  // If the disk was write protected leave button disabled until done.
			  case IDC_WRITE_PROTECT:
				if ( oldWriteProtect == WP_READ_WRITE )
				{
			      if ( IsDlgButtonChecked(hDisk, IDC_WRITE_PROTECT) )
			         EnableWindow(GetDlgItem(hDisk, IDC_INITIALIZE), FALSE);
			      else
			         EnableWindow(GetDlgItem(hDisk, IDC_INITIALIZE), TRUE);
				}
				break;


			  case IDC_FONT_DETAILS:
			  {
				DoFontDetails(hwnd,
				             str, sizeof(str),
				             title, sizeof(title));
				break;
			  } // case IDC_FONT_DETAILS:

			  case IDC_FONT_DELETE:
			  {
				DoFontDelete(hwnd,
				             str, sizeof(str),
				             title, sizeof(title));

				bufSize = sizeof(PeripheralDisk);
				memset(&periphDisk, 0, (size_t)bufSize);
				dwResult = PALGetComponentObject(hPeripheral, hComponent, OT_PERIPHERAL_DISK, 0, &periphDisk, &bufSize);
				if (dwResult IS RC_SUCCESS) {
					dwCapacity = (DWORD)(periphDisk.capacity / 1024L);
					dwFree = (DWORD)(periphDisk.freeSpace / 1024L);
					dwPercent = dwFree * 100 / dwCapacity;
					LoadString(hInstance, IDS_FREE_SPACE, str, SIZEOF_IN_CHAR(str));
					wsprintf(buffer, str, dwFree, dwPercent);
					SetDlgItemText(hDisk, IDC_FREE_SPACE, buffer);
					SetWindowWord(GetDlgItem(hDisk, IDC_FREE_SPACE), GWW_TRAYLEVEL, (WORD)dwPercent);
				}

				break;
			  } // case IDC_FONT_DELETE:
			} // case BN_CLICKED:  switch (id)
			break;
	} // switch(codeNotify)
}