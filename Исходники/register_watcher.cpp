	// SingleRegWatcher
	INT_PTR CALLBACK SingleRegWatcher::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
		switch(uMsg){
		case WM_INITDIALOG:
		{
			// Create subclass of edit box function
			SetWindowSubclass(GetDlgItem(hWnd, IDC_REGVALUE), &EditSubclassProc, m_editSubclassID, NULL);
		}
			break;
		case WM_CLOSE:
		{
			RemoveWindowSubclass(GetDlgItem(hWnd, IDC_REGVALUE), &EditSubclassProc, m_editSubclassID);
			break;
		}
		case WM_ENABLE:
			EnableWindow(GetDlgItem(hWnd, IDC_REGVALUE), (BOOL)wParam);
			break;
		case H86_UPDATE_SYS_DATA:
		{
			Mutex sysMutex((void*)wParam);
			sys_state_ptr sysState=(sys_state_ptr)lParam;

			sysMutex.Lock();

			nsEmulator::Emulator* e=nsEmulator::Emulator::GetInstance();
			uint16 val=e->ReadReg(m_regNum);
			wchar_t data[5];
			_itow((uint32)val, data, 16);
			SetDlgItemText(hWnd, IDC_REGVALUE, data);

			sysMutex.Unlock();
		}
			break;
		case H86_USER_INPUT:
		{
			sys_state_ptr sysState=(sys_state_ptr)lParam;

			nsEmulator::Emulator* e=nsEmulator::Emulator::GetInstance();
			wchar_t data[5];
			GetDlgItemText(hWnd, IDC_REGVALUE, data, 5);
			uint16 val=wcstol(data, NULL, 16);
			e->WriteReg(m_regNum, val);
		}
			break;
		default:
			return 0;
		}
		return 0;
	}