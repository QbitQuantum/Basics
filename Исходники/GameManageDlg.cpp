void CGameManageDlg::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu PopMenu;
	CString strMenu;
	PopMenu.CreatePopupMenu();
	CPoint Point;
	GetCursorPos(&Point);
	m_GameDiskListCtrl.ScreenToClient(&Point);
	m_ListIndex1 = m_GameDiskListCtrl.HitTest(Point);

	if (0 <= m_ListIndex1 && m_ListIndex1 < m_wSocket.m_pRoomInfo->uDeskCount)
	{
		int flag = -1;
		int uesecount = 0;
		for (int j = 0; j < m_wSocket.m_UserManage.GetOnLineUserCount(); j++)
		{
			if (m_wSocket.m_UserManage.FindOnLineUserByIndex(j)->GameUserInfo.bDeskNO == m_ListIndex1)
			{
				uesecount++;
			}
		}
		if (uesecount == 0) flag = 0; 
		for (int i = 0; i < m_wSocket.m_DeskStation.vVirtuals.size(); i++)
		{
			if (m_ListIndex1 == m_wSocket.m_DeskStation.vVirtuals[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag != -1)
		{
			if (flag == 0)
				PopMenu.AppendMenu(0, MSG_CMD_GM_LOCK, TEXT("封桌"));
			else if (flag == 1)
				PopMenu.AppendMenu(0, MSG_CMD_GM_UNLOCK, TEXT("解封"));
			PopMenu.AppendMenu(0, MSG_CMD_GM_ALLLOCK, TEXT("批量封桌"));
			PopMenu.AppendMenu(0, MSG_CMD_GM_ALLUNLOCK, TEXT("批量解封"));
			//显示菜单

			GetCursorPos(&Point);
			//m_GameUeserListCtrl.ClientToScreen(&Point);
			PopMenu.TrackPopupMenu(TPM_RIGHTBUTTON, Point.x, Point.y, this);
			PopMenu.DestroyMenu();
		}
	}
	*pResult = 0;
}