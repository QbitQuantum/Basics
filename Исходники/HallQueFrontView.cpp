void CHallQueFrontView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pt;
	GetCursorPos(&pt);
	
	int result = m_pTrackCtrl->Track( point,nFlags);
	if(result == TRACK_CTR_MIDORHANDLE)
	{
		OnEditctr();
	}
	else
	{
		int nFullWidth=GetSystemMetrics(SM_CXSCREEN);
		int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
		CRect inRect;
		inRect.left = nFullWidth - 300;
		inRect.top = nFullHeight - 200;
		inRect.right = nFullWidth;
		inRect.bottom = nFullHeight;
		if(inRect.PtInRect(pt))
		{
			if(!m_isManage)
			{
				CMenu menu;
				menu.LoadMenu(IDR_MENU_NOMANAGE);
				CMenu *pContentMenu=menu.GetSubMenu(0);
				pContentMenu->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this); //在指定位置显示弹出菜单
				pContentMenu->DestroyMenu();
			}
			else
			{
				CMenu menu;
				menu.LoadMenu(IDR_MENU_MANAGE);
				CMenu *pContentMenu=menu.GetSubMenu(0);
				pContentMenu->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this); //在指定位置显示弹出菜单
				pContentMenu->DestroyMenu();
			}
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
}