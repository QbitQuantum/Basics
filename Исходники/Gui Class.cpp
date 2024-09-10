DWORD CALLBACK AboutIniBoxProc (HWND hDlg, DWORD uMsg, DWORD wParam, DWORD /*lParam*/) 
{
	static wchar_t RDBHomePage[300], CHTHomePage[300], RDXHomePage[300];
	
	switch (uMsg) {
	case WM_INITDIALOG:
		{
			wchar_t String[200];
			
			//Title
			LONG_PTR originalWndProc = GetWindowLongPtrW(hDlg, GWLP_WNDPROC);
			SetWindowLongPtrW(hDlg, GWLP_WNDPROC, (LONG_PTR) DefWindowProcW);
			SetWindowTextW(hDlg, GS(INI_TITLE));
			SetWindowLongPtrW(hDlg, GWLP_WNDPROC, originalWndProc);

			//Language
			SetDlgItemTextW(hDlg,IDC_LAN,GS(INI_CURRENT_LANG));
			set_about_field(hDlg, IDC_LAN_AUTHOR, GS(INI_AUTHOR), GS(LANGUAGE_AUTHOR));
			set_about_field(hDlg, IDC_LAN_VERSION, GS(INI_VERSION), GS(LANGUAGE_VERSION));
			set_about_field(hDlg, IDC_LAN_DATE, GS(INI_DATE), GS(LANGUAGE_DATE));
			if (wcslen(GS(LANGUAGE_NAME)) == 0) 
            {
				EnableWindow(GetDlgItem(hDlg,IDC_LAN),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_LAN_AUTHOR),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_LAN_VERSION),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_LAN_DATE),FALSE);
			}
			
			//RDB
			CIniFile RdbIniFile(g_Settings->LoadString(SupportFile_RomDatabase).c_str());
			wcsncpy(String, RdbIniFile.GetString("Meta","Author","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			if (wcslen(String) == 0) 
            {
				EnableWindow(GetDlgItem(hDlg,IDC_RDB),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDB_AUTHOR),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDB_VERSION),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDB_DATE),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDB_HOME),FALSE);
			}

			set_about_field(hDlg, IDC_RDB_AUTHOR, GS(INI_AUTHOR), String);
			
			wcsncpy(String, RdbIniFile.GetString("Meta","Version","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			set_about_field(hDlg, IDC_RDB_VERSION, GS(INI_VERSION), String);
			wcsncpy(String, RdbIniFile.GetString("Meta","Date","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			set_about_field(hDlg, IDC_RDB_DATE, GS(INI_DATE), String);
			wcsncpy(RDBHomePage, RdbIniFile.GetString("Meta","Homepage","").ToUTF16().c_str(),sizeof(RDBHomePage) / sizeof(RDBHomePage[0]));
			SetDlgItemTextW(hDlg, IDC_RDB_HOME, GS(INI_HOMEPAGE));
			if (wcslen(RDBHomePage) == 0) 
			{
				EnableWindow(GetDlgItem(hDlg,IDC_RDB_HOME),FALSE);
			}
			
			//Cheat
			SetDlgItemTextW(hDlg,IDC_CHT,GS(INI_CURRENT_CHT));
			CIniFile CheatIniFile(g_Settings->LoadString(SupportFile_Cheats).c_str());
			wcsncpy(String, CheatIniFile.GetString("Meta","Author","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			if (wcslen(String) == 0) 
			{
				EnableWindow(GetDlgItem(hDlg,IDC_CHT),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_CHT_AUTHOR),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_CHT_VERSION),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_CHT_DATE),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_CHT_HOME),FALSE);
			}
			set_about_field(hDlg, IDC_CHT_AUTHOR, GS(INI_AUTHOR), String);
			wcsncpy(String, CheatIniFile.GetString("Meta","Version","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			set_about_field(hDlg, IDC_CHT_VERSION, GS(INI_VERSION), String);
			wcsncpy(String, CheatIniFile.GetString("Meta","Date","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			set_about_field(hDlg, IDC_CHT_DATE, GS(INI_DATE), String);
			wcsncpy(CHTHomePage, CheatIniFile.GetString("Meta","Homepage","").ToUTF16().c_str(),sizeof(CHTHomePage) / sizeof(CHTHomePage[0]));
			SetDlgItemTextW(hDlg, IDC_CHT_HOME, GS(INI_HOMEPAGE));
			if (wcslen(CHTHomePage) == 0)
            {
				EnableWindow(GetDlgItem(hDlg,IDC_CHT_HOME),FALSE);
			}
			
			//Extended Info
			SetDlgItemTextW(hDlg, IDC_RDX, GS(INI_CURRENT_RDX));
			CIniFile RdxIniFile(g_Settings->LoadString(SupportFile_ExtInfo).c_str());
			wcsncpy(String, RdxIniFile.GetString("Meta","Author","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			if (wcslen(String) == 0) 
			{
				EnableWindow(GetDlgItem(hDlg,IDC_RDX),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDX_AUTHOR),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDX_VERSION),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDX_DATE),FALSE);
				EnableWindow(GetDlgItem(hDlg,IDC_RDX_HOME),FALSE);
			}
			set_about_field(hDlg, IDC_RDX_AUTHOR, GS(INI_AUTHOR), String);
			wcsncpy(String, RdxIniFile.GetString("Meta","Version","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			set_about_field(hDlg, IDC_RDX_VERSION, GS(INI_VERSION), String);
			wcsncpy(String, RdxIniFile.GetString("Meta","Date","").ToUTF16().c_str(),sizeof(String) / sizeof(String[0]));
			set_about_field(hDlg, IDC_RDX_DATE, GS(INI_DATE), String);
			wcsncpy(RDXHomePage, RdxIniFile.GetString("Meta","Homepage","").ToUTF16().c_str(),sizeof(RDXHomePage) / sizeof(RDXHomePage[0]));
			SetDlgItemTextW(hDlg, IDC_RDX_HOME, GS(INI_HOMEPAGE));
			if (wcslen(RDXHomePage) == 0) 
            {
				EnableWindow(GetDlgItem(hDlg,IDC_RDX_HOME),FALSE);
			}
			SetDlgItemTextW(hDlg, IDOK, GS(CHEAT_OK));
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
        {
		case IDC_RDB_HOME: ShellExecuteW(NULL,L"open",RDBHomePage,NULL,NULL,SW_SHOWNORMAL); break;
		case IDC_CHT_HOME: ShellExecuteW(NULL,L"open",CHTHomePage,NULL,NULL,SW_SHOWNORMAL); break;
		case IDC_RDX_HOME: ShellExecuteW(NULL,L"open",RDXHomePage,NULL,NULL,SW_SHOWNORMAL); break;
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg,0);
			break;
		}
	default:
		return FALSE;
	}
	return TRUE;
}