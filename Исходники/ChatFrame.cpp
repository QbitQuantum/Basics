BOOL CChatFrame::OnShowPopupMenu (CBCGPopupMenu* pMenuPopup)
{
	clearIdleTime();

	//---------------------------------------------------------
	// Replace ID_VIEW_TOOLBARS menu item to the toolbars list:
	//---------------------------------------------------------
    CFrameWnd::OnShowPopupMenu (pMenuPopup);

    if (pMenuPopup != NULL &&
		pMenuPopup->GetMenuBar ()->CommandToIndex (ID_VIEW_TOOLBARS) >= 0)
    {
		if (CBCGToolBar::IsCustomizeMode ())
		{
			//----------------------------------------------------
			// Don't show toolbars list in the cuztomization mode!
			//----------------------------------------------------
			return FALSE;
		}

		pMenuPopup->RemoveAllItems ();

		CMenu menu;
		VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pMenuPopup->GetMenuBar ()->ImportFromMenu (*pPopup, TRUE);
    }
	
	if ( pMenuPopup != NULL && pMenuPopup->GetParentToolBar() == &m_wndTopChatBar )
	{
		if ( m_wndTopChatBar.GetButton( m_GameButton ) == pMenuPopup->GetParentButton() )
		{
			CWaitCursor wait;

			MetaClient & client = CGCQLApp::sm_MetaClient;
			if ( client.getGames( m_Games ) < 0 )
			{
				//MessageBox( "Failed to get game list." );
				return FALSE;
			}

			pMenuPopup->RemoveAllItems();

			CMenu gameMenu;
			gameMenu.CreatePopupMenu();

			for(int i=0;i<m_Games.size() && i < MAX_GAMES;i++)
				gameMenu.AppendMenu( MF_STRING, ID_GAMES_BEGIN + i, CString(m_Games[i].name) );

			pMenuPopup->GetMenuBar()->ImportFromMenu (gameMenu, TRUE);
		}
		if ( m_wndTopChatBar.GetButton( m_RoomsButton ) == pMenuPopup->GetParentButton() )
		{
			CWaitCursor wait;

			MetaClient & client = CGCQLApp::sm_MetaClient;
			if ( client.getRooms( m_Rooms ) < 0 )
				return FALSE;

			pMenuPopup->RemoveAllItems();

			CMenu roomMenu;
			roomMenu.CreatePopupMenu();
			roomMenu.AppendMenu( MF_STRING, ID_CHAT_CREATEROOM, _T("New Room") );
			roomMenu.AppendMenu( MF_SEPARATOR );

			for(int i=0;i<m_Rooms.size() && i < MAX_ROOMS;i++)
			{
				MetaClient::Room & room = m_Rooms[i];
				
				CString sName;
				sName.Format( _T("%s "), CString( room.name ) );
				if ( room.flags & MetaClient::FLAG_ROOM_MODERATED )
					sName += _T("[MODERATED]");
				if ( room.flags & MetaClient::FLAG_ROOM_PASSWORD )
					sName += _T("[PRIVATE]");
				if ( room.flags & MetaClient::FLAG_ROOM_PRIVATE )
					sName += _T("[HIDDEN]");

				CString sMembers;
				sMembers.Format( _T("\t%u"), room.members );

				sName += sMembers;

				roomMenu.AppendMenu( MF_STRING, ID_ROOM_BEGIN + i, sName );
			}

			pMenuPopup->GetMenuBar()->ImportFromMenu (roomMenu, TRUE);
		}
		if ( m_wndTopChatBar.GetButton( m_FriendsButton ) == pMenuPopup->GetParentButton() )
		{
			CWaitCursor wait;

			MetaClient & client = CGCQLApp::sm_MetaClient;
			if ( client.getFriends( m_Friends ) < 0 )
			{
				//MessageBox( "Failed to get room list." );
				return FALSE;
			}
			
			// let friends who are online appear on top of the list
			m_Friends.qsort( userOnlineSort );

			pMenuPopup->RemoveAllItems();

			CMenu friendsMenu;
			friendsMenu.CreatePopupMenu();

			for(int i=0;i<m_Friends.size() && i < MAX_FRIENDS;i++)
			{
				MetaClient::ShortProfile & profile = m_Friends[ i ];

				CString sFriend;
				sFriend.Format(_T("%s\t%s"), CString(profile.name), CString(profile.status) );

				CMenu friendMenu;
				friendMenu.CreateMenu();
				friendMenu.AppendMenu( MF_STRING, ID_FRIEND_MSG_BEGIN + i, _T("Message") );
				friendMenu.AppendMenu( MF_STRING, ID_FRIEND_DEL_BEGIN + i, _T("Delete") );
				friendsMenu.AppendMenu( MF_POPUP, (UINT)friendMenu.Detach(), sFriend );
			}

			pMenuPopup->GetMenuBar()->ImportFromMenu( friendsMenu, TRUE );
		}
		if ( m_wndTopChatBar.GetButton( m_StaffButton ) == pMenuPopup->GetParentButton() )
		{
			CWaitCursor wait;

			MetaClient & client = CGCQLApp::sm_MetaClient;
			if ( client.getStaffOnline( m_Staff ) < 0 )
				return FALSE;
			
			dword userId = client.profile().userId;
			for( int i = 0 ; i < m_Staff.size() ; i++ )
				if( m_Staff[ i ].userId == userId )
				{
					m_Staff.remove(i);
					break;
				}

			pMenuPopup->RemoveAllItems();

			CMenu staffMenu;
			staffMenu.CreatePopupMenu();

			for(int i=0;i<m_Staff.size() && i < MAX_STAFF;i++)
			{
				MetaClient::ShortProfile & profile = m_Staff[ i ];

				CString sType;
				if ( profile.flags & MetaClient::ADMINISTRATOR )
					sType = "[ADMIN]";
				else if ( profile.flags & MetaClient::MODERATOR )
					sType = "[MOD]";

				CString sName;
				sName = profile.name;
				CString sStaffMember;
				sStaffMember.Format( _T("%s: %s\t%s"), sType, sName, CString(profile.status) );

				CMenu stMenu;
				stMenu.CreateMenu();
				stMenu.AppendMenu( MF_STRING, ID_STAFF_MSG_BEGIN + i, _T("Message") );

				bool bInserted = false;
				for(unsigned int j=0;j<staffMenu.GetMenuItemCount() && !bInserted;j++)
				{
					CString sCompare;
					staffMenu.GetMenuString( j, sCompare, MF_BYPOSITION );

					if ( _tcscmp( sCompare, sName ) > 0 )
					{
						staffMenu.InsertMenu( j, MF_BYPOSITION|MF_POPUP, (UINT)stMenu.Detach(), sStaffMember ) ? true : false;
						bInserted = true;
					}
				}

				if (!bInserted )
					staffMenu.AppendMenu( MF_POPUP, (UINT)stMenu.Detach(), sStaffMember );
			}

			pMenuPopup->GetMenuBar()->ImportFromMenu( staffMenu, TRUE );
		}
		if ( m_wndTopChatBar.GetButton( m_ClanButton ) == pMenuPopup->GetParentButton() )
		{
			CWaitCursor wait;

			pMenuPopup->RemoveAllItems();

			MetaClient & client = CGCQLApp::sm_MetaClient;

			CMenu clanMenu;
			clanMenu.CreatePopupMenu();
			//clanMenu.AppendMenu( MF_STRING, ID_GAMEBAR_CLAN, _T("Fleet Home") );

			dword clanId = client.profile().clanId;
			if ( clanId != 0 )
			{
				clanMenu.AppendMenu( MF_SEPARATOR );
				if ( client.getClan( clanId, m_Clan ) < 0 )
				{
					//MessageBox( "Failed to get clan members" );
					return FALSE;
				}
				
				// Remove self from clanlist
				for( int i = 0 ; i < m_Clan.size() ; i++ )
					if( m_Clan[i].userId == client.profile().userId )
					{
						m_Clan.remove(i);
						break;
					}

				// let members who are online appear on top of the list
				m_Clan.qsort( userOnlineSort );

				for( int i = 0 ; i < m_Clan.size() && i < MAX_CLAN ; i++ )
				{
					MetaClient::ShortProfile & profile = m_Clan[ i ];

					CString sClanMember;
					sClanMember.Format( _T("%s\t%s"), CString(profile.name), CString(profile.status) );

					CMenu subMenu;
					subMenu.CreateMenu();
					subMenu.AppendMenu( MF_STRING, ID_CLAN_MSG_BEGIN + i, _T("Message") );

					clanMenu.AppendMenu( MF_POPUP, (UINT)subMenu.Detach(), sClanMember );
				}
			}

			pMenuPopup->GetMenuBar()->ImportFromMenu( clanMenu, TRUE );
		}

	}

	return TRUE;
}