BOOL CALLBACK AP_Win32Dialog_Stylist::s_treeProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{		
	if (msg == WM_LBUTTONDBLCLK)
	{
		// The user has double clicked on a tree item
		AP_Win32Dialog_Stylist * pThis = (AP_Win32Dialog_Stylist *)GetWindowLongPtrW(hWnd,GWLP_USERDATA);
		if (pThis->_styleClicked())
			pThis->Apply();
		return 1;
	}

	return CallWindowProcW(hTreeProc, hWnd, msg, wParam, lParam);
}