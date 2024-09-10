INT_PTR CDialogManage::CTabSettings::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_MANAGESETTINGS_LANGUAGE_COMBOBOX:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			int sel = ComboBox_GetCurSel((HWND)lParam);
			LCID lcid = (LCID)ComboBox_GetItemData((HWND)lParam, sel);
			if (lcid != Rainmeter->m_ResourceLCID)
			{
				WCHAR buffer[16];
				_ultow(lcid, buffer, 10);
				WritePrivateProfileString(L"Rainmeter", L"Language", buffer, Rainmeter->GetIniFile().c_str());

				std::wstring resource = Rainmeter->GetPath() + L"Languages\\";
				resource += buffer;
				resource += L".dll";
				FreeLibrary(Rainmeter->m_ResourceInstance);
				Rainmeter->m_ResourceInstance = LoadLibraryEx(resource.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES | LOAD_LIBRARY_AS_DATAFILE);
				Rainmeter->m_ResourceLCID = lcid;

				if (CDialogAbout::c_Dialog)
				{
					int sel = TabCtrl_GetCurSel(GetDlgItem(CDialogAbout::c_Dialog->GetWindow(), IDC_ABOUT_TAB));
					SendMessage(CDialogAbout::c_Dialog->GetWindow(), WM_DELAYED_CLOSE, 0, 0);
					if (sel == 0)
					{
						Rainmeter->DelayedExecuteCommand(L"!About");
					}
					else if (sel == 1)
					{
						Rainmeter->DelayedExecuteCommand(L"!About Skins");
					}
					else if (sel == 2)
					{
						Rainmeter->DelayedExecuteCommand(L"!About Plugins");
					}
					else //if (sel == 3)
					{
						Rainmeter->DelayedExecuteCommand(L"!About Version");
					}
				}

				SendMessage(c_Dialog->GetWindow(), WM_DELAYED_CLOSE, 0, 0);
				Rainmeter->DelayedExecuteCommand(L"!Manage Settings");
			}
		}
		break;

	case IDC_MANAGESETTINGS_CHECKUPDATES_CHECKBOX:
		Rainmeter->SetDisableVersionCheck(!Rainmeter->GetDisableVersionCheck());
		break;

	case IDC_MANAGESETTINGS_LOCKSKINS_CHECKBOX:
		Rainmeter->SetDisableDragging(!Rainmeter->GetDisableDragging());
		break;

	case IDC_MANAGESETTINGS_RESETSTATISTICS_BUTTON:
		Rainmeter->ResetStats();
		break;

	case IDC_MANAGESETTINGS_SHOWLOGFILE_BUTTON:
		Rainmeter->ShowLogFile();
		break;

	case IDC_MANAGESETTINGS_DELETELOGFILE_BUTTON:
		Rainmeter->DeleteLogFile();
		if (_waccess(Rainmeter->GetLogFile().c_str(), 0) == -1)
		{
			Button_SetCheck(GetDlgItem(m_Window, IDC_MANAGESETTINGS_LOGTOFILE_CHECKBOX), BST_UNCHECKED);
			EnableWindow(GetDlgItem(m_Window, IDC_MANAGESETTINGS_SHOWLOGFILE_BUTTON), FALSE);
			EnableWindow(GetDlgItem(m_Window, IDC_MANAGESETTINGS_DELETELOGFILE_BUTTON), FALSE);
		}
		break;

	case IDC_MANAGESETTINGS_LOGTOFILE_CHECKBOX:
		if (Rainmeter->GetLogging())
		{
			Rainmeter->StopLogging();
		}
		else
		{
			Rainmeter->StartLogging();
			if (_waccess(Rainmeter->GetLogFile().c_str(), 0) != -1)
			{
				EnableWindow(GetDlgItem(m_Window, IDC_MANAGESETTINGS_SHOWLOGFILE_BUTTON), TRUE);
				EnableWindow(GetDlgItem(m_Window, IDC_MANAGESETTINGS_DELETELOGFILE_BUTTON), TRUE);
			}
		}
		break;

	case IDC_MANAGESETTINGS_VERBOSELOGGING_CHECKBOX:
		Rainmeter->SetDebug(!Rainmeter->GetDebug());
		break;

	default:
		return 1;
	}

	return 0;
}