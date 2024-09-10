void CRichEditWnd::OnItemActive(TNotifyUI& msg)
{
	CAnimationTabLayoutUI* pTabControl = static_cast<CAnimationTabLayoutUI*>(GetPaintMgr()->FindControl(_T("TAB_MAIN")));
	if (pTabControl != NULL)
	{
		if (pTabControl->GetCurSel() == 1)
		{
			CFriendsUI* pFriendsList = static_cast<CFriendsUI*>(GetPaintMgr()->FindControl(_T("LIST_FRIEND")));
			if ((pFriendsList != NULL) && pFriendsList->GetItemIndex(msg.pSender) != -1)
			{
				if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
				{
					Node* node = (Node*)msg.pSender->GetTag();

					CControlUI* background = GetPaintMgr()->FindControl(_T("bg"));
					if (!pFriendsList->CanExpand(node) && (background != NULL))
					{
						FriendListItemInfo friend_info;

						for (std::vector<FriendListItemInfo>::const_iterator citer = friends_.begin(); citer != friends_.end(); ++citer)
						{
							if (_tcsicmp(citer->id, node->data().value) == 0)
							{
								friend_info = *citer;
								break;
							}
						}

						ChatDialog* pChatDialog = new ChatDialog(background->GetBkImage(), background->GetBkColor(), myself_info_, friend_info);
						if (pChatDialog == NULL)
							return;
#if defined(WIN32) && !defined(UNDER_CE)
						pChatDialog->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
#else
						pChatDialog->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
#endif

						pChatDialog->CenterWindow();
						::ShowWindow(*pChatDialog, SW_SHOW);
					}
				}
			}
		}
	}
}