	INT_PTR CALLBACK sqlCmdWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_INITDIALOG:
			{
				return (INT_PTR)TRUE;
			}
		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
				case IDCLOSE:
					EndDialog(hWnd, 0);
					break;
				case IDC_CLEAR:
					SetDlgItemText(hWnd, IDC_SCRIPT, 0);
					break;
				case IDC_EXECUTE:
					{
						SetDlgItemText(hWnd, IDC_RESULT, 0);

						int len = GetWindowTextLengthW(GetDlgItem(hWnd, IDC_SCRIPT));
						wchar_t* sql = new wchar_t[len+2];
						GetDlgItemTextW(hWnd, IDC_SCRIPT, sql, len+1);
						utfstring str(sql);
						PluginController::getInstance().dtb->executeSQL(str.toUTF8(), sqlQueryCallback, GetDlgItem(hWnd, IDC_RESULT));
						delete [] sql;
					}
					break;
				}
				return (INT_PTR)TRUE;
			}
		}
		return (INT_PTR)FALSE;
	}