//权限界面弹出菜单
VOID HsProcessPrivilegePopupMenu(CMyList *m_ListCtrl, CWnd* parent)
{
	CMenu	popup;
	popup.LoadMenu(IDR_MENU_PROCESS_PRIVILEGE);		//加载菜单资源
	CMenu*	pM = popup.GetSubMenu(0);				//获得菜单的子项
	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
	if (m_ListCtrl->GetSelectedCount() == 0)		//如果没有选中
	{ 
		for (int i = 0;i<count;i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED); //菜单全部变灰
		}
	}
	else
	{
		POSITION pos = m_ListCtrl->GetFirstSelectedItemPosition();

		while(pos)
		{
			int iItem = m_ListCtrl->GetNextSelectedItem(pos);

			if (_wcsnicmp(m_ListCtrl->GetItemText(iItem,2),L"Default Enabled",15) == 0)
			{
				for (int i = 1;i<count;i++)
				{
					pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED); //菜单全部变灰
				}
			}
			else if (_wcsnicmp(m_ListCtrl->GetItemText(iItem,2),L"Enabled",7) == 0)
			{
				pM->CheckMenuRadioItem(2,3,2, MF_BYPOSITION | MF_CHECKED);
			}
			else
			{
				pM->CheckMenuRadioItem(2,3,3, MF_BYPOSITION | MF_CHECKED);
			}
		}
	}
	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, parent);
}