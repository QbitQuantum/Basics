// 参看：http://www.cnblogs.com/hcfalan/archive/2010/11/24/1886139.html
BOOL CDlgImageViewer::ContinueModal()
{
	if(m_ToolBar.IsWindowVisible())
	{
		CFrameWnd* pParent = (CFrameWnd*)m_ToolBar.GetParent();
		if(pParent)
			m_ToolBar.OnUpdateCmdUI(pParent, (WPARAM)TRUE);
	}
	CMenu* pMainMenu = GetMenu();
	CCmdUI cmdUI;
	if (pMainMenu != NULL)
	{
		for (int n = 0; n < pMainMenu->GetMenuItemCount(); ++n)
		{
			CMenu* pSubMenu = pMainMenu->GetSubMenu(n);
			cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
			for (int i = 0; i < cmdUI.m_nIndexMax; ++i)
			{
				cmdUI.m_nIndex = i;
				cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
				cmdUI.m_pMenu = pSubMenu;
				cmdUI.DoUpdate(this, FALSE);
			}
		}
	}
	return CDialogEx::ContinueModal();
}