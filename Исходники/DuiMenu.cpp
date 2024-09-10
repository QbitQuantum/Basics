// 消息响应
LRESULT CDuiMenu::OnMessage(UINT uID, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if((Msg != MSG_BUTTON_UP) && (Msg != MSG_BUTTON_CHECK))
	{
		return 0;
	}

	CControlBase* pControl = GetControl(uID);
	if(pControl && !pControl->GetAction().IsEmpty())
	{
		// 如果菜单项设置了action，则添加到动作任务队列中，通过任务来执行
		CString strControlName = pControl->GetName();
		CString strAction = pControl->GetAction();
		//CDuiObject* pParent = pControl->GetParent();
		CDlgBase* pParentDlg = pControl->GetParentDialog();

		DuiSystem::Instance()->AddDuiActionTask(uID, Msg, wParam, lParam, strControlName, strAction, pParentDlg);
	}else
	{
		// 否则就调用Popup的函数
		__super::OnMessage(uID, Msg, wParam, lParam);

		/*tagMenuInfo* pMenuInfo = new tagMenuInfo;
		pMenuInfo->uMenuID = uID;
		pMenuInfo->bSelect = (bool)lParam;
		pMenuInfo->bDown = (bool)wParam;
	
		PostMessage(m_uMessageID, Msg, (LPARAM)pMenuInfo);*/
	}

	if(Msg == MSG_BUTTON_UP)
	{
		// 如果点击的是弹出菜单,则不用关闭
		if(pControl && pControl->IsClass(CMenuItem::GetClassName()) && ((CMenuItem*)pControl)->IsPopup())
		{
			return 0;
		}

		// 如果有父菜单,将父菜单关闭,不采用直接关闭的方法,而是设置自动关闭标识,并通过鼠标事件触发自动关闭
		CDuiMenu* pParentMenu = GetParentMenu();
		if(pParentMenu && !pParentMenu->IsAutoClose())
		{
			pParentMenu->SetAutoClose(TRUE);
			pParentMenu->SetForegroundWindow();
			pParentMenu->PostMessage(WM_LBUTTONDOWN, 0, 0);
		}
		// 关闭自身
		CloseWindow();
	}

	return 0;
}