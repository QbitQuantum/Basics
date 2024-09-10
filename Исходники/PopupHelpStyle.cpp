int CPopupHelpStyle::WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_HELP)
	{
		helper::ShowContextHelp((HELPINFO *)lParam);
		return DONT_CALL_OLD_PROC;
	}
	// 用户按下鼠标右键就会弹出帮助框，
	// 调试模式会引发一个assertion: wincore.cpp 875
	//else if (msg == WM_RBUTTONUP)
	else if (0)
	{
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		
		HELPINFO hi = {sizeof(HELPINFO)};
		hi.dwContextId = HELPINFO_WINDOW;
		hi.MousePos = pt;
		m_pWnd->ScreenToClient(&pt);
		CWnd *pWnd = m_pWnd->ChildWindowFromPoint(pt);
		if (pWnd != NULL)
		{
			hi.hItemHandle = pWnd->m_hWnd;
			hi.iCtrlId = pWnd->GetDlgCtrlID();
			helper::ShowContextHelp(&hi);
			return DONT_CALL_OLD_PROC;
		}
	}

	return RETURN_DEFAULT;
}