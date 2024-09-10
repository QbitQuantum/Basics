static BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		{
			HINSTANCE hInst = GetModuleHandle(NULL);
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
			SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
		}
		break;
	case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
	case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255,255,255));
			//if you leave this line off the background will be filled in with the brush you specify, 
			//but when the control draws the text it will get written over with the default background 
			//color! Setting the text drawing mode to transparent fixes this problem. The other option 
			//would be to SetBkColor() to the same color as our background brush, but I like this solution better.
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)g_hbrBackground;
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON1: //fill random text
				//IDC_EDIT1
				SetDlgItemText(hwnd, IDC_EDIT1, L"Hello how are you?");
				break;
			case IDC_BUTTON2: // get text
				{
					int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT1));
					if (len > 0)
					{
						wchar_t* buf;
						//NOTE: len+1 because GetWindowTextLength returns number of characters (not including NULL). 
						buf = (wchar_t*)GlobalAlloc(GPTR, (len+1)*sizeof(wchar_t));
						//returns number of characters (not including NULL). 
						GetDlgItemText(hwnd, IDC_EDIT1, buf, len+1);

						MessageBox(hwnd, buf, L"Notice", MB_OK);

						GlobalFree((HANDLE)buf);
					}
				}
				break;
			case IDC_BUTTON4: // get number
				{
					//last param: signed
					BOOL translated;
					int num = GetDlgItemInt(hwnd, IDC_EDIT1, &translated, TRUE);
					if (translated)
					{
						std::wostringstream wostr;
						wostr << L"the number is " << num;
						MessageBox(hwnd, wostr.str().data(), L"Notice", MB_OK);
					}
					else
					{
						MessageBox(hwnd, L"not a number", L"Notice", MB_OK);
					}
				}
				break;
			case IDC_BUTTON5:
				{
					int index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)L"Hi there!");
				}
				break;
			case IDC_LIST1:
				{
					switch(HIWORD(wParam))
					{
					case LBN_SELCHANGE:
						//Selection changed, do stuff here
						MessageBox(hwnd, L"sel changed", L"Notice", MB_OK);
						break;
					}
				}
				break;
			case IDC_BUTTON6:
				{
					HWND hList = GetDlgItem(hwnd, IDC_LIST1);
					int index = SendMessage(hList, LB_GETCURSEL, 0,0);
					std::cout << index;
					//Note that static controls are all given a default ID of IDC_STATIC (-1) by the resource editor, 
					//so if you want to be able to tell them apart you'll need to assign them new IDs.
					SetDlgItemInt(hwnd, IDC_STATIC1, index, TRUE);
				}
				break;
			case IDOK:
				EndDialog(hwnd, IDOK);
				break;
			case IDCANCEL:
				EndDialog(hwnd, IDCANCEL);
				break;
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}