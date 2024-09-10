//右键弹出处理
void CComputerListView::OnContextMenu(CWnd*, CPoint point)
{
	m_SelectRows.RemoveAll();

	CMenu menu;

	CBCGPGridRow* pRow = GetGridCtrl()->GetCurSel();

	if (pRow != NULL)//存在选中的子行
	{
		CList<CBCGPGridItem*, CBCGPGridItem*> lstSelected;
		GetGridCtrl()->GetSelectedItems(lstSelected);//多重选择队列

		POSITION pos = lstSelected.GetHeadPosition();//第一个

		while (pos != NULL)
		{
			CBCGPGridItem* pItem = lstSelected.GetNext(pos);//下一个			
			m_SelectRows.Add((UINT)pItem->GetParentRow()->GetData());//保存选中的序号			
		}

		SendMessage(WM_LBUTTONUP);//弹起

		VERIFY(menu.LoadMenu(IDR_COMPUTER_MENU));//载入
		CMenu* pPopup = menu.GetSubMenu(0);//第一个子菜单
		ASSERT(pPopup != NULL);

#ifndef __USING_INTER_RESOURCE
		HMENU hTmp = pPopup->GetSubMenu(6)->GetSafeHmenu();
		pPopup->ModifyMenu((UINT_PTR)hTmp,MF_POPUP,(UINT_PTR)hTmp,LOAD_STRING(IDS_REMOTE_OPERATION));
#endif

		//弹出菜单
		theApp.GetContextMenuManager()->ShowPopupMenu(pPopup->Detach(), point.x, point.y, this, TRUE);
	}
	else
	{
		//扫描鼠标位置，点击在列栏上，才弹出此菜单
		CRect rect;
		m_pWndGridCtrl->GetClientRect(rect);
		rect.bottom = 21; //栏高度大概为21个像素
		ClientToScreen(rect);

		if (rect.PtInRect(point))//点击在栏上
		{
			VERIFY(menu.LoadMenu(IDR_MENU_COLUMN));//载入列菜单

			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			for (INT i = 0; i < GetGridCtrl()->GetColumnCount(); i++)//列枚举
			{//动态插入与列项有关的菜单
				pPopup->InsertMenu(i, MF_BYPOSITION, IDM_MINCOLUMNCMD + i, GetGridCtrl()->GetColumnName(i));
				pPopup->CheckMenuItem(i, MF_BYPOSITION | (GetGridCtrl()->GetColumnVisible(i) ? MF_CHECKED : MF_UNCHECKED));
			}

			theApp.GetContextMenuManager()->ShowPopupMenu(pPopup->Detach(), point.x, point.y, this, TRUE);
		}
	}
}