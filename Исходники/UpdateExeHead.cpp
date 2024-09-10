INT_PTR CALLBACK MainDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDCANCEL:
				if(g_bSuccess) RunLaunch();
				PostQuitMessage(0);
				break;
				
			case IDOK:
				HMENU hMenu = ::GetSystemMenu(hwndDlg, FALSE);
				::EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
				::EnableWindow(::GetDlgItem(hwndDlg, IDOK), FALSE);
				::EnableWindow(::GetDlgItem(hwndDlg, IDCANCEL), FALSE);
				if(g_hBeginHandle) SetEvent(g_hBeginHandle);
				break;
			}
		}
		break;

	case WM_MSG_ENTERFAULT:
		_enterFaultMode();
		break;

	case WM_MSG_SETPROGRESS:
		{
			UINT nPosOld = (UINT)::SendDlgItemMessage(hwndDlg, IDC_PROGRESS_MAIN, PBM_GETPOS, 
				0, 0);
			UINT nPosNow = (UINT)wParam;
			if(nPosNow != nPosOld)
			{
				::SendDlgItemMessage(hwndDlg, IDC_PROGRESS_MAIN, PBM_SETPOS, nPosNow, 0);
			}
		}
		break;

	case WM_MSG_SUCCESS:
		{
			HMENU hMenu = ::GetSystemMenu(hwndDlg, FALSE);
			::EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND|MF_ENABLED);
			::EnableWindow(::GetDlgItem(hwndDlg, IDOK), FALSE);
			::EnableWindow(::GetDlgItem(hwndDlg, IDCANCEL), TRUE);
			::SetDlgItemText(hwndDlg, IDCANCEL, "确定");
			::CloseHandle(g_hBeginHandle); g_hBeginHandle=0;
			::SendDlgItemMessage(hwndDlg, IDC_PROGRESS_MAIN, PBM_SETPOS, 100, 0);

			char szTemp[MAX_PATH] = {0};
			_snprintf(szTemp, MAX_PATH, "《天龙八部》成功更新到%s!", g_szVersionTo);
			MessageBox(g_hMainWnd, szTemp, "《天龙八部》", MB_OK|MB_ICONINFORMATION);

			g_bSuccess = TRUE;
		}
		break;

	case WM_INITDIALOG:
		{
			g_hMainWnd = hwndDlg;

			//Center main window
			CenterDlg(hwndDlg);

			//设置图标
			HICON hMainIcon = LoadIcon(g_hInst, (LPCTSTR)IDD_DIALOG_MAIN);
			::SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)hMainIcon);
			::SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hMainIcon);

			//set status
			::SetDlgItemText(hwndDlg, IDC_STATIC_STATUS, "读取版本信息...");
			::SendDlgItemMessage(hwndDlg, IDC_PROGRESS_MAIN, PBM_SETRANGE, 
				0, MAKELPARAM(0, 100));

			g_hBeginHandle = ::CreateEvent(0, TRUE, FALSE, 0);
			::ResetEvent(g_hBeginHandle);

			//create work thread
			UINT nThreadID;
			g_hWorkThread = (HANDLE)::_beginthreadex(NULL, 0, _WorkThread, 0, CREATE_SUSPENDED|THREAD_QUERY_INFORMATION, &nThreadID );
			if(g_hWorkThread == NULL)
			{
				::SetDlgItemText(hwndDlg, IDC_STATIC_STATUS, "创建线程失败");
				_enterFaultMode();
				break;
			}

			//go!
			::ResumeThread(g_hWorkThread);
			//not care
			::CloseHandle(g_hWorkThread); g_hWorkThread=0;
		}
		break;

	case WM_CTLCOLORSTATIC:
		{
			HWND hStatic = (HWND)lParam;

			if(g_bFaultMode && hStatic == GetDlgItem(hwndDlg, IDC_STATIC_STATUS))
			{
				HBRUSH hBrush = (HBRUSH)(INT_PTR)::DefWindowProc(hwndDlg, WM_CTLCOLORSTATIC, wParam, lParam);

				SetTextColor((HDC)wParam, RGB(255, 0, 0));
				return (BOOL)(INT)(INT_PTR)hBrush;
			}
			else return FALSE;
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return FALSE;
}