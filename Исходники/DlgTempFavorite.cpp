//右键单击，弹出菜单
LRESULT CDlgTempFavorite::OnRightClickChannel(WPARAM wParam, LPARAM lParam)
{
	int iServerID = (int)wParam;	//窗口标识
	int iWinID = lParam / 0x100;
	int ich = lParam & 0xff;
		
	int iYTID = wParam % 0x1000;
	wParam = wParam / 0x1000;

	if (iServerID >= 4 || iServerID < 0)
		return 1;

	if (m_CurrentCh != (int)iServerID)
	{
		CRect rc;
		if (m_CurrentCh >= 0 && m_CurrentCh < 4)
		{
			DrawRect(m_CurrentCh, 0);
		}
		
		if ((iServerID >= 0) && (iServerID < 4))
			m_CurrentCh = iServerID;
		else
			m_CurrentCh = 0;
		
		DrawRect(m_CurrentCh, 1);
	}

	CMenu  popMenu;

	popMenu.LoadMenu(IDR_MENU_TEMPFAVORITE);
	CMenu *pMenu = popMenu.GetSubMenu(0); 

	CPoint posMouse;
	GetCursorPos(&posMouse);

	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_RIGHTALIGN,  posMouse.x, posMouse.y, this); 

	return 1;
}