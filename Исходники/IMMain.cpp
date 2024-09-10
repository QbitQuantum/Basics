//激活信息窗口
CShortMessage * CIMMain::ActiveShortWnd(long int dwUserID, char* pNickName, bool bCreate)
{
	//变量定义
	INT_PTR iCloseIndex=-1,iHideIndex=-1;
	UserItemStruct stUserItem;

	ZeroMemory(&stUserItem, sizeof(stUserItem));
	stUserItem.GameUserInfo.dwUserID = dwUserID;
	stUserItem.GameUserInfo.dwAccID = 0;
	strcpy(stUserItem.GameUserInfo.nickName, pNickName);

	//寻找敏合窗口
	for (INT_PTR i=0;i<m_ShortMessage.GetCount();i++)
	{
		CShortMessage * pShortMessageWnd=(CShortMessage *)m_ShortMessage.GetAt(i);
		ASSERT(pShortMessageWnd!=NULL);
		if (pShortMessageWnd!= NULL)
		{
			if (dwUserID==pShortMessageWnd->m_dwTargetUserID)
			{
				if (pShortMessageWnd->GetSafeHwnd()==NULL)
				{
					AfxSetResourceHandle(GetModuleHandle(NULL));
					pShortMessageWnd->Create(IDD_SHORT_MESSAGE,GetDesktopWindow());
					pShortMessageWnd->CenterWindow();
				}
				pShortMessageWnd->ShowWindow(SW_SHOWNOACTIVATE);
				return pShortMessageWnd;
			}
		}
		else
		{
			m_ShortMessage.RemoveAt(i);
		}
		if (bCreate==true)
		{
			if ((iCloseIndex==-1)&&(pShortMessageWnd->GetSafeHwnd()==NULL))
				iCloseIndex=i;
			if ((iHideIndex==-1)&&(pShortMessageWnd->GetSafeHwnd()!=NULL)&&(pShortMessageWnd->IsWindowVisible()==FALSE)) iHideIndex=i;
		}
	}

	//使用关闭的窗口
	if ((bCreate==true)&&(iCloseIndex>=0))
	{
		CShortMessage * pShortMessageWnd=(CShortMessage *)m_ShortMessage.GetAt(iCloseIndex);
		ASSERT(pShortMessageWnd!=NULL);
		if (pShortMessageWnd->GetSafeHwnd()==NULL)
		{
			AfxSetResourceHandle(GetModuleHandle(NULL));
			pShortMessageWnd->Create(IDD_SHORT_MESSAGE,GetDesktopWindow());
			pShortMessageWnd->CenterWindow();
		}
		SendMsgUserStruct user;
		pShortMessageWnd->TransUserInfo(&stUserItem, &user);
		pShortMessageWnd->SetTalkInfo(&user,GetMainRoom()->m_PlaceUserInfo.dwGamePower,"大厅");
		pShortMessageWnd->ShowWindow(SW_SHOWNOACTIVATE);
		return pShortMessageWnd;
	}

	//使用隐藏窗口
	if ((bCreate==true)&&(iHideIndex>=0))
	{
		CShortMessage * pShortMessageWnd=(CShortMessage *)m_ShortMessage.GetAt(iHideIndex);
		ASSERT(pShortMessageWnd!=NULL);
		SendMsgUserStruct user;
		pShortMessageWnd->TransUserInfo(&stUserItem, &user);
		pShortMessageWnd->SetTalkInfo(&user,GetMainRoom()->m_PlaceUserInfo.dwGamePower,"大厅");
		pShortMessageWnd->ShowWindow(SW_SHOWNOACTIVATE);
		return pShortMessageWnd;
	}

	//建立新窗口
	if ((bCreate==true)&&(m_ShortMessage.GetCount()<m_iMaxShortWnd))
	{
		try
		{
			CShortMessage * pShortMessageWnd=new CShortMessage(this);
			AfxSetResourceHandle(GetModuleHandle(NULL));
			pShortMessageWnd->m_bIsInRoom = false;
			SendMsgUserStruct user;
			pShortMessageWnd->TransUserInfo(&stUserItem, &user);
			pShortMessageWnd->SetTalkInfo(&user,GetMainRoom()->m_PlaceUserInfo.dwGamePower,"大厅");
			pShortMessageWnd->Create(IDD_SHORT_MESSAGE,GetDesktopWindow());
			pShortMessageWnd->CenterWindow();
			pShortMessageWnd->ShowWindow(SW_SHOWNOACTIVATE);
			m_ShortMessage.Add(pShortMessageWnd);
			return pShortMessageWnd;
		}
		catch (...) { return NULL; }
	}

	return NULL;
}