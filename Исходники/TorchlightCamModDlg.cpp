void CTorchlightCamModDlg::OnContextMenu(CWnd *pWnd, CPoint pos)
{
	bool bExit = false;
	CMenu menu, *pSubMenu;
	CWnd* pTarget = AfxGetMainWnd();

	if (!menu.LoadMenu(IDR_SYSTRAY_MENU)) bExit = true;
	if (!bExit)
	{
		if (!(pSubMenu = menu.GetSubMenu(0))) bExit = true;
		if (!bExit)
		{
			//CWnd* pTarget = AfxGetMainWnd();

			// Make chosen menu item the default (bold font)

			menu.EnableMenuItem(IDC_ST_RESTORE, MF_GRAYED);

			if (m_mnuStatus.StartAsMinimized) menu.CheckMenuItem(IDC_ST_STARTASMINIMIZED, MF_CHECKED);
			if (m_mnuStatus.SpeedHigh) menu.CheckMenuItem(IDC_ST_SPEED_HIGH, MF_CHECKED);
			if (m_mnuStatus.SpeedNormal) menu.CheckMenuItem(IDC_ST_SPEED_NORMAL, MF_CHECKED);
			if (m_mnuStatus.SpeedLow) menu.CheckMenuItem(IDC_ST_SPEED_LOW, MF_CHECKED);

			// Display and track the popup menu
			pTarget->SetForegroundWindow();
			::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, pTarget->GetSafeHwnd(), NULL);

			//    // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
			//pTarget->PostMessage(WM_NULL, 0, 0);
			menu.DestroyMenu();
		}
	}

}