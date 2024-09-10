BOOL CPageAdvanced::DlgProcInternal(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_NOTIFY:
		{
			// Property Sheet notifications

			switch (((LPPSHNOTIFY)lparam)->hdr.code)
			{
			case PSN_SETACTIVE:
				// About to become the active page
				m_PropertySheetHelper.SetLastPage(m_Page);
				InitOptions(hWnd);
				break;
			case PSN_KILLACTIVE:
				SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);			// Changes are valid
				break;
			case PSN_APPLY:
				DlgOK(hWnd);
				SetWindowLong(hWnd, DWL_MSGRESULT, PSNRET_NOERROR);	// Changes are valid
				break;
			case PSN_QUERYCANCEL:
				// Can use this to ask user to confirm cancel
				break;
			case PSN_RESET:
				DlgCANCEL(hWnd);
				break;
			}
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDC_SAVESTATE_FILENAME:
			break;
		case IDC_SAVESTATE_BROWSE:
			if(m_PropertySheetHelper.SaveStateSelectImage(hWnd, TEXT("Select Save State file"), false))
				SendDlgItemMessage(hWnd, IDC_SAVESTATE_FILENAME, WM_SETTEXT, 0, (LPARAM)m_PropertySheetHelper.GetSSNewFilename());
			break;
		case IDC_PRINTER_DUMP_FILENAME_BROWSE:
			{				
				std::string strPrinterDumpLoc = m_PropertySheetHelper.BrowseToFile(hWnd, TEXT("Select printer dump file"), REGVALUE_PRINTER_FILENAME, TEXT("Text files (*.txt)\0*.txt\0") TEXT("All Files\0*.*\0"));
				SendDlgItemMessage(hWnd, IDC_PRINTER_DUMP_FILENAME, WM_SETTEXT, 0, (LPARAM)strPrinterDumpLoc.c_str());
			}
			break;
		case IDC_SAVESTATE_ON_EXIT:
			break;
		case IDC_SAVESTATE:
			m_PropertySheetHelper.GetConfigNew().m_uSaveLoadStateMsg = WM_USER_SAVESTATE;
			break;
		case IDC_LOADSTATE:
			m_PropertySheetHelper.GetConfigNew().m_uSaveLoadStateMsg = WM_USER_LOADSTATE;
			break;

		//

		case IDC_THE_FREEZES_F8_ROM_FW:
			{
				const UINT uNewState = IsDlgButtonChecked(hWnd, IDC_THE_FREEZES_F8_ROM_FW) ? 1 : 0;
				m_PropertySheetHelper.GetConfigNew().m_bEnableTheFreezesF8Rom = uNewState;
			}
			break;

		case IDC_CLONETYPE:
			if(HIWORD(wparam) == CBN_SELCHANGE)
			{
				const DWORD NewCloneMenuItem = (DWORD) SendDlgItemMessage(hWnd, IDC_CLONETYPE, CB_GETCURSEL, 0, 0);
				const eApple2Type NewCloneType = GetCloneType(NewCloneMenuItem);
				m_PropertySheetHelper.GetConfigNew().m_Apple2Type = NewCloneType;
			}
			break;
		}
		break;

	case WM_INITDIALOG:
		{
			SendDlgItemMessage(hWnd,IDC_SAVESTATE_FILENAME,WM_SETTEXT,0,(LPARAM)Snapshot_GetFilename());

			CheckDlgButton(hWnd, IDC_SAVESTATE_ON_EXIT, g_bSaveStateOnExit ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hWnd, IDC_DUMPTOPRINTER, g_bDumpToPrinter ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hWnd, IDC_PRINTER_CONVERT_ENCODING, g_bConvertEncoding ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hWnd, IDC_PRINTER_FILTER_UNPRINTABLE, g_bFilterUnprintable ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hWnd, IDC_PRINTER_APPEND, g_bPrinterAppend ? BST_CHECKED : BST_UNCHECKED);
			SendDlgItemMessage(hWnd, IDC_SPIN_PRINTER_IDLE, UDM_SETRANGE, 0, MAKELONG(999,0));
			SendDlgItemMessage(hWnd, IDC_SPIN_PRINTER_IDLE, UDM_SETPOS, 0, MAKELONG(Printer_GetIdleLimit (),0));
			SendDlgItemMessage(hWnd, IDC_PRINTER_DUMP_FILENAME, WM_SETTEXT, 0, (LPARAM)Printer_GetFilename());

			InitOptions(hWnd);

			m_PropertySheetHelper.ClearSSNewDirectory();

			// Need to specify cmd-line switch: -printer-real to enable this control
			EnableWindow(GetDlgItem(hWnd, IDC_DUMPTOPRINTER), g_bEnableDumpToRealPrinter ? TRUE : FALSE);

			break;
		}
	}

	return FALSE;
}