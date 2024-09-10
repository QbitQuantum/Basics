INT_PTR CALLBACK ModifyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static size_w len;
    HWND hwndHV = GetActiveHexView(g_hwndMain);

	static BOOL fHexLength = FALSE;
	static int  nLastOperand   = 0;
	static int  nLastOperation = 0;
	static BOOL fBigEndian	   = FALSE;
	int basetype;

	static const int SearchTypeFromBaseType[] = 
	{
		SEARCHTYPE_BYTE, SEARCHTYPE_WORD, SEARCHTYPE_DWORD, SEARCHTYPE_QWORD,
		SEARCHTYPE_BYTE, SEARCHTYPE_WORD, SEARCHTYPE_DWORD, SEARCHTYPE_QWORD,
		SEARCHTYPE_FLOAT, SEARCHTYPE_DOUBLE, 
	};
		
	switch (iMsg)
	{
	case WM_INITDIALOG:

		AddComboStringList(GetDlgItem(hwnd, IDC_MODIFY_DATATYPE), szTypeList, 0);

		AddComboStringList(GetDlgItem(hwnd, IDC_MODIFY_OPERATION), szOpList, nLastOperation);
		SetDlgItemBaseInt(hwnd, IDC_MODIFY_OPERAND, nLastOperand, fHexLength ? 16 : 10, FALSE);

		CheckDlgButton(hwnd, IDC_HEX, fHexLength ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd, IDC_ENDIAN, fBigEndian ? BST_CHECKED : BST_UNCHECKED);

		//len = HexView_GetSelSize(hwndHV);
		//SetDlgItemBaseInt(hwnd, IDC_MODIFY_NUMBYTES, len, fHexLength ? 16 : 10, FALSE);
		

		CenterWindow(hwnd);
		return TRUE;
			
	case WM_CLOSE:
		EndDialog(hwnd, FALSE);
		return TRUE;
	
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_MODIFY_OPERATION:
		case IDC_MODIFY_OPERAND:
		case IDC_MODIFY_NUMBYTES:
			nLastOperation = (int)SendDlgItemMessage(hwnd, IDC_MODIFY_OPERATION, CB_GETCURSEL, 0, 0);
			nLastOperand   = (int)GetDlgItemBaseInt(hwnd, IDC_MODIFY_OPERAND, fHexLength ? 16 : 10);
			len            = GetDlgItemBaseInt(hwnd, IDC_MODIFY_NUMBYTES, fHexLength ? 16 : 10);
			return TRUE;

		case IDC_ENDIAN:
			fBigEndian	   = IsDlgButtonChecked(hwnd, IDC_ENDIAN);
			return TRUE;

		case IDC_HEX:
			fHexLength = IsDlgButtonChecked(hwnd, IDC_HEX);

		/*	len = HexView_GetSelSize(hwndHV);
			SetDlgItemBaseInt(hwnd, IDC_MODIFY_NUMBYTES, len, fHexLength ? 16 : 10, FALSE);
			*/
			
			SetDlgItemBaseInt(hwnd, IDC_MODIFY_OPERAND,  nLastOperand, fHexLength ? 16 : 10, FALSE);

			SendDlgItemMessage(hwnd, IDC_MODIFY_OPERAND, EM_SETSEL, 0, -1);
			SetDlgItemFocus(hwnd, IDC_MODIFY_OPERAND);
			return TRUE;

		case IDOK:
			
			// get the basetype we are using
			basetype = (int)SendDlgItemMessage(hwnd, IDC_INSERT_DATATYPE, CB_GETCURSEL, 0, 0);
			basetype = SearchTypeFromBaseType[basetype];

			// get the operand in raw-byte format, ensure it is always little-endian
			// as we must do these calculations using the native byte ordering format
			operandLen = sizeof(operandData);
			UpdateSearchData(GetDlgItem(hwnd, IDC_MODIFY_OPERAND), basetype, FALSE, operandData, &operandLen);

			HexView_GetSelSize(hwndHV, &len);
			ModifyHexViewData(hwndHV, nLastOperation, operandData, len, basetype, fBigEndian);
			EndDialog(hwnd, TRUE);
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, FALSE);
			return TRUE;

		default:
			return FALSE;
		}

	case WM_HELP: 
		return HandleContextHelp(hwnd, lParam, IDD_TRANSFORM);

	default:
		break;
	}
	return FALSE;

}