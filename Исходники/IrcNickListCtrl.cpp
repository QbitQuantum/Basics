void CIrcNickListCtrl::OnContextMenu(CWnd*, CPoint point)
{
	int iCurSel = GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (iCurSel == -1)
	{
		return;
	}
	Nick* pNick = (Nick*)GetItemData(iCurSel);
	if( !pNick )
	{
		return;
	}

	CTitleMenu menuNick;
	menuNick.CreatePopupMenu();
	menuNick.AddMenuTitle(GetResString(IDS_IRC_NICK) + _T(" : ") + pNick->m_sNick);
	menuNick.AppendMenu(MF_STRING, Irc_Priv, GetResString(IDS_IRC_PRIVMESSAGE));
	menuNick.AppendMenu(MF_STRING, Irc_AddFriend, GetResString(IDS_IRC_ADDTOFRIENDLIST));
	if (!m_pParent->GetSendFileString().IsEmpty())
		menuNick.AppendMenu(MF_STRING, Irc_SendLink, GetResString(IDS_IRC_SENDLINK) + m_pParent->GetSendFileString());
	else
		menuNick.AppendMenu(MF_STRING, Irc_SendLink, GetResString(IDS_IRC_SENDLINK) + GetResString(IDS_IRC_NOSFS));
	menuNick.AppendMenu(MF_STRING, Irc_Kick, GetResString(IDS_IRC_KICK));
	menuNick.AppendMenu(MF_STRING, Irc_Ban, _T("Ban"));
	//Ban currently uses chanserv to ban which seems to kick also.. May change this later..
	//	menuNick.AppendMenu(MF_STRING, Irc_KB, _T("Kick/Ban"));
	menuNick.AppendMenu(MF_STRING, Irc_Slap, GetResString(IDS_IRC_SLAP));
	int iLength = m_sUserModeSettings.GetLength();
	if( iLength > 0 )
	{
		CString sMode, sModeSymbol;
		for( int iIndex = 0; iIndex < iLength; iIndex++)
		{
			sMode = m_sUserModeSettings.Mid(iIndex,1);
			sModeSymbol = m_sUserModeSymbols.Mid(iIndex,1);
			if( pNick->m_sModes.Find(sModeSymbol[0]) == -1 )
				menuNick.AppendMenu(MF_STRING, Irc_OpCommands+iIndex, _T("Set +") + sMode + _T(" ( Add ") + sModeSymbol + _T(" )") );
			else
				menuNick.AppendMenu(MF_STRING, Irc_OpCommands+iIndex+25, _T("Set -") + sMode + _T(" ( Remove ") + sModeSymbol + _T(" )") );
		}
	}
	GetPopupMenuPos(*this, point);
	menuNick.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	VERIFY( menuNick.DestroyMenu() );
}