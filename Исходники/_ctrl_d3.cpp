/*------------------------------------------------------------------------------*
| <<< ダイアログのイベント処理 >>>
*------------------------------------------------------------------------------*/
static	BOOL	CALLBACK	D3CtrlProc(HWND	hWnd, UINT msg,	WPARAM wParam, LPARAM lParam)
{
#ifdef	IDC_ADAPTER_COMBO
	switch(msg)
	{
	case WM_INITDIALOG:
		//static	bool	isLocked = false;		// 初期化時にはスイッチの動作を抑制
		//isLocked = true;
		CTRL_WINDOW_RECT_SET(hWnd);					// ウィンドウの中央へ
		hDialog	   = hWnd;
		d3.bWindow = true;							// 起動時は強制時にウィンドウとする
		CtrlSet(d3.bWindow);
		//isLocked	 = false;
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_ADAPTER_COMBO:				// アダプター
		case IDC_ADAPTERFORMAT_COMBO:		// アダプターの画像フォーマット
		case IDC_RESOLUTION_COMBO:			// 描画サイズ
		//case IDC_VERTEXPROCESSING_COMBO:	// 頂点の計算方法
			if(CBN_SELCHANGE ==	HIWORD(wParam))
			{
				ComboSet(LOWORD(wParam));	
				CtrlSet(IsDlgButtonChecked(hWnd, IDC_WINDOW) ==	BST_CHECKED);
			}
			break;
		case IDC_WINDOW:
			d3.fmtBackBuffer = d3.fmtDisplay = d3.deskTopDisplayMode.Format;
			ComboSet(LOWORD(wParam));
			CtrlSet(true);
			EnableWindow(GetDlgItem(hWnd, IDC_ADAPTERFORMAT_COMBO),	false);
			CheckRadioButton(hWnd, IDC_WINDOW, IDC_FULLSCREEN, IDC_WINDOW);
			break;
		case IDC_FULLSCREEN:
			d3.fmtBackBuffer = d3.fmtDisplay = d3.deskTopDisplayMode.Format;
			ComboSet(LOWORD(wParam));
			CtrlSet(false);
			EnableWindow(GetDlgItem(hWnd, IDC_ADAPTERFORMAT_COMBO),	true);
			CheckRadioButton(hWnd, IDC_WINDOW, IDC_FULLSCREEN, IDC_FULLSCREEN);
			break;
		case IDOK:							// OK ボタンを押した
			ChangeSet();
			SendMessage(hDialog, WM_CLOSE, 0, 0L);
			break;
		case IDCANCEL:						// CANCEL を押した
			memcpy(&d3,	&d3_bak, sizeof(D3_WORK));
			SendMessage(hDialog, WM_CLOSE, 0, 0L);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDialog, IDOK);
		hDialog	= NULL;
		break;
	default:
		return FALSE;
	}
#endif
	return TRUE;
}