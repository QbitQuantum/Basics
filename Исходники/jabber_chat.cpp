int JabberGcMenuHook( WPARAM wParam, LPARAM lParam )
{
	GCMENUITEMS* gcmi= ( GCMENUITEMS* )lParam;
	if ( gcmi == NULL )
		return 0;

	if ( lstrcmpiA( gcmi->pszModule, jabberProtoName ))
		return 0;

	JABBER_LIST_ITEM* item = JabberListGetItemPtr( LIST_CHATROOM, gcmi->pszID );
	if ( item == NULL )
		return 0;

	JABBER_RESOURCE_STATUS *me = NULL, *him = NULL;
	for ( int i=0; i < item->resourceCount; i++ ) {
		JABBER_RESOURCE_STATUS& p = item->resource[i];
		if ( !lstrcmp( p.resourceName, item->nick   ))  me = &p;
		if ( !lstrcmp( p.resourceName, gcmi->pszUID ))  him = &p;
	}

	if ( gcmi->Type == MENU_ON_LOG ) {
		static struct gc_item sttLogListItems[] = {
			{ TranslateT( "&Leave chat session" ),    IDM_LEAVE,     MENU_ITEM, FALSE },
			{ TranslateT( "Add to Bookmarks" ),       IDM_BOOKMARKS, MENU_ITEM, TRUE },
			{ NULL, 0, MENU_SEPARATOR, FALSE },
			{ TranslateT( "&Voice List..." ),         IDM_VOICE,     MENU_ITEM, TRUE  },
			{ TranslateT( "&Ban List..." ),           IDM_BAN,       MENU_ITEM, TRUE  },
			{ NULL, 0, MENU_SEPARATOR, FALSE },
			{ TranslateT( "&Member List..." ),        IDM_MEMBER,    MENU_ITEM, TRUE  },
			{ TranslateT( "Mo&derator List..." ),     IDM_MODERATOR, MENU_ITEM, TRUE  },
			{ TranslateT( "&Admin List..." ),         IDM_ADMIN,     MENU_ITEM, TRUE  },
			{ TranslateT( "&Owner List..." ),         IDM_OWNER,     MENU_ITEM, TRUE  },
			{ NULL, 0, MENU_SEPARATOR, FALSE },
			{ TranslateT( "Change &Nickname..." ),    IDM_NICK,      MENU_ITEM, FALSE },
			{ TranslateT( "Set &Topic..." ),          IDM_TOPIC,     MENU_ITEM, FALSE },
			{ TranslateT( "&Invite a User..." ),      IDM_INVITE,    MENU_ITEM, FALSE },
			{ TranslateT( "Room Con&figuration..." ), IDM_CONFIG,    MENU_ITEM, TRUE  },
			{ NULL, 0, MENU_SEPARATOR, FALSE },
			{ TranslateT( "Destroy Room..." ),        IDM_DESTROY,   MENU_ITEM, TRUE  }};

		gcmi->nItems = sizeof( sttLogListItems ) / sizeof( sttLogListItems[0] );
		gcmi->Item = sttLogListItems;

		if ( me != NULL ) {
			if ( me->role == ROLE_MODERATOR )
				sttLogListItems[3].bDisabled = FALSE;

			if ( me->affiliation == AFFILIATION_ADMIN )
				sttLogListItems[4].bDisabled = sttLogListItems[6].bDisabled = sttLogListItems[7].bDisabled = FALSE;
			else if ( me->affiliation == AFFILIATION_OWNER )
				sttLogListItems[4].bDisabled = sttLogListItems[6].bDisabled =
				sttLogListItems[7].bDisabled = sttLogListItems[8].bDisabled =
				sttLogListItems[9].bDisabled = sttLogListItems[14].bDisabled =
				sttLogListItems[16].bDisabled = FALSE;
		}
		if ( jabberThreadInfo->caps & CAPS_BOOKMARK ) sttLogListItems[1].bDisabled = FALSE;
	}
	else if ( gcmi->Type == MENU_ON_NICKLIST ) {
		static struct gc_item sttListItems[] = {
			{ TranslateT( "&User Details" ),          IDM_VCARD,     MENU_ITEM, FALSE },
			{ TranslateT( "&Leave chat session" ),    IDM_LEAVE,     MENU_ITEM, FALSE },
			{ NULL, 0, MENU_SEPARATOR, FALSE },
			{ TranslateT( "Kick" ),                   IDM_KICK,      MENU_ITEM, TRUE },
			{ TranslateT( "Ban" ),                    IDM_BAN,       MENU_ITEM, TRUE },
			{ NULL, 0, MENU_SEPARATOR, FALSE },
			{ TranslateT( "Toggle &Voice" ),          IDM_VOICE,     MENU_ITEM, TRUE },
			{ TranslateT( "Toggle Moderator" ),       IDM_MODERATOR, MENU_ITEM, TRUE },
			{ TranslateT( "Toggle Admin" ),           IDM_ADMIN,     MENU_ITEM, TRUE },
			{ TranslateT( "Toggle Owner" ),           IDM_OWNER,     MENU_ITEM, TRUE }};

		gcmi->nItems = sizeof( sttListItems )/sizeof( sttListItems[0] );
		gcmi->Item = sttListItems;

		if ( me != NULL && him != NULL ) {
			if ( me->role == ROLE_MODERATOR )
				if ( him->affiliation != AFFILIATION_ADMIN && him->affiliation != AFFILIATION_OWNER )
					sttListItems[3].bDisabled = sttListItems[4].bDisabled = FALSE;

			if ( me->affiliation == AFFILIATION_ADMIN ) {
				if ( him->affiliation != AFFILIATION_ADMIN && him->affiliation != AFFILIATION_OWNER )
					sttListItems[6].bDisabled = sttListItems[7].bDisabled = FALSE;
			}
			else if ( me->affiliation == AFFILIATION_OWNER )
				sttListItems[6].bDisabled = sttListItems[7].bDisabled =
				sttListItems[8].bDisabled = sttListItems[9].bDisabled = FALSE;
	}	}

	return 0;
}