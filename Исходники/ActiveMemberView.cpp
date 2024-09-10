void CActiveMemberView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_ACTIVEMEMBER_MENU));//载入
	
	CBCGPGridRow* pRow = GetGridCtrl()->GetCurSel();

	if (pRow != NULL)//存在选中的子行
	{
		SendMessage(WM_LBUTTONUP);

		CMenu* pPopup = menu.GetSubMenu(0);//第一个子菜单

		if (pPopup)
		{
			// 2012/03/21-8238-gxx: 
			if (CNetBarConfig::GetInstance()->GetRealNamePassword() == 4 )
			{
				pPopup->RemoveMenu(IDM_CHECKIN, MF_BYCOMMAND);
			}

			theApp.GetContextMenuManager()->ShowPopupMenu(pPopup->Detach(), point.x, point.y, this, TRUE);
		}

		
	}
	else
	{
		CMenu* pPopup = menu.GetSubMenu(1);//第2个子菜单
		theApp.GetContextMenuManager()->ShowPopupMenu(pPopup->Detach(), point.x, point.y, this, TRUE);
	}
}