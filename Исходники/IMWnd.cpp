//右击IM列表`
void CIMWnd::OnNMRclickIMList(NMHDR * pNMHDR, LRESULT * pResult)
{
	try
	{
		CBcfFile fMsg(CBcfFile::GetAppPath()+"ClientMessage.bcf");
		CPoint point;
		GetCursorPos(&point);
		m_IMList->ScreenToClient(&point);
		HTREEITEM hti=m_IMList->HitTest(point);
		if(!hti)
			return;
		int dwUserid=m_IMList->GetItemData(hti);
		if(dwUserid<1000)
			return;
		dwUserid-=1000;
		CString sname=m_IMList->GetItemText(hti);
		CMenu menu;
		menu.CreatePopupMenu();
		MENUINFO mi;
		menu.GetMenuInfo(&mi);
		mi.cbSize=sizeof(MENUINFO);
		mi.fMask=MIM_BACKGROUND; 
		mi.hbrBack = CreateSolidBrush(RGB(0xD1,0xF1,0xFF));
		menu.SetMenuInfo(&mi);

		if((m_IMList->GetParentItem(hti)==m_IMList->htiFamilier)
			||(m_IMList->GetParentItem(hti)==m_IMList->htiUnfamilier))
		{
			menu.AppendMenu(MF_STRING,10,fMsg.GetKeyVal("IMDlg","Chat","聊天"));
		}
		menu.AppendMenu(MF_STRING,11,fMsg.GetKeyVal("IMDlg","Delete","删除"));
		if(m_IMList->GetParentItem(hti)!=m_IMList->htiFamilier)
		{
			menu.AppendMenu(MF_STRING,21,fMsg.GetKeyVal("IMDlg","ToFriend","加入好友"));
		}
		if(m_IMList->GetParentItem(hti)!=m_IMList->htiBlack)
		{
			menu.AppendMenu(MF_STRING,22,fMsg.GetKeyVal("IMDlg","ToBadGuyList","加入黑名单"));
		}

		CPoint p; 
		::GetCursorPos(&p);
		int ret=menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RETURNCMD,p.x,p.y,this);

		switch(ret)
		{
		case 10:
			{
#ifndef MAINROOM_USE_SHORTMSG
				int nImg;
				m_IMList->GetItemImage(hti,nImg,nImg);
				CIMSession *imSession=m_IMList->openIMSession(dwUserid,sname);//
				if(imSession)
				{
					if(nImg==3 || nImg==5)
						imSession->setUserOnline(true);
					if(nImg==4 || nImg==6)
						imSession->setUserOnline(false);
					imSession->ShowWindow(SW_SHOW);
				}
#else
				m_IMList->openShortMsg(dwUserid,sname.GetBuffer(sname.GetLength()));
#endif
			}
			break;
		case 11:
			{
				//if(AFCMessageBox(fMsg.GetKeyVal("IMDlg","R_U_SureDelFriend","您确定要删除该好友吗？"),
				//	fMsg.GetKeyVal("IMDlg","Tip","提示"),AFC_YESNO)==IDOK)
				if(DUIMessageBox(m_hWnd,MB_YESNO|MB_ICONINFORMATION,fMsg.GetKeyVal("IMDlg","Tip","提示"),true,fMsg.GetKeyVal("IMDlg","R_U_SureDelFriend","您确定要删除该好友吗？"))==IDOK)
					m_IMList->SetUserGroup(dwUserid,NULL,0);
			}
			break;
		case 21:
			m_IMList->SetUser(dwUserid,"",true);
			break;
		case 22:
			{
				//if(AFCMessageBox(fMsg.GetKeyVal("IMDlg","MoveFriendToBadList","您确定要将该好友放到黑名单吗？"),
				//	fMsg.GetKeyVal("IMDlg","Tip","提示"),AFC_YESNO)==IDOK)
				if(DUIMessageBox(m_hWnd,MB_YESNO|MB_ICONINFORMATION,fMsg.GetKeyVal("IMDlg","Tip","提示"),true,fMsg.GetKeyVal("IMDlg","MoveFriendToBadList","您确定要将该好友放到黑名单吗？"))==IDYES)
				{
					m_IMList->SetUserGroup(dwUserid,NULL,3);
					CString szMsg;
					szMsg.Format(fMsg.GetKeyVal("IMDlg","MoveOneToBadList","玩家[%s]已经加入到你的黑名单中"), sname);
					AFCTimerMsgBox(5, szMsg);
				}
			}
			break;
		}

		DeleteObject(mi.hbrBack);
	}
	catch (...)
	{
		TCHAR smsg[1000]={0};
		wsprintf(smsg,"IM_TRY_CATCH : [%s]",__FUNCTION__);
	}


	*pResult = 0;
}