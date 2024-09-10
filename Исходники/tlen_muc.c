int TlenMUCRecvError(const char *from, XmlNode *errorNode)
{
	int errCode;
	char str[512];
	JABBER_LIST_ITEM *item;
	MUCCEVENT mucce;
	mucce.cbSize = sizeof(MUCCEVENT);
	mucce.iType = MUCC_EVENT_ERROR;
	mucce.pszID = from;
	mucce.pszModule = jabberProtoName;
	errCode = atoi(JabberXmlGetAttrValue(errorNode, "code"));
	switch (errCode) {
		case 403:
			sprintf(str, Translate("You cannot join this chat room, because you are banned."));
			break;
		case 404:
			sprintf(str, Translate("Chat room not found."));
			break;
		case 407:
			sprintf(str, Translate("This is a private chat room and you are not one of the members."));
			break;
		case 408:
			sprintf(str, Translate("You cannot send any message unless you join this chat room."));
			break;
		case 410:
			sprintf(str, Translate("Chat room with already created."));
			break;
		case 411:
			sprintf(str, Translate("Nickname '%s' is already registered."),
				JabberXmlGetAttrValue(errorNode, "n"));
			break;
		case 412:
			sprintf(str, Translate("Nickname already in use, please try another one. Hint: '%s' is free."),
				JabberXmlGetAttrValue(errorNode, "free"));
			break;
		case 413:
			sprintf(str, Translate("You cannot register more than %s nicknames."),
				JabberXmlGetAttrValue(errorNode, "num"));
			break;
		case 414:
			sprintf(str, Translate("You cannot create more than %s chat rooms."),
				JabberXmlGetAttrValue(errorNode, "num"));
			break;
		case 415:
			sprintf(str, Translate("You cannot join more than %s chat rooms."),
				JabberXmlGetAttrValue(errorNode, "num"));
			break;
		case 601:
			sprintf(str, Translate("Anonymous nicknames are not allowed in this chat room."));
			break;
		default:
			sprintf(str, Translate("Unknown error code : %d"), errCode);
			break;
	}
	mucce.pszText = str;
	CallService(MS_MUCC_EVENT, 0, (LPARAM) &mucce);
	if (jabberOnline) {
		switch (errCode) {
			case 412:
				item = JabberListGetItemPtr(LIST_CHATROOM, from);
				if (item!=NULL) {
					mucce.iType = MUCC_EVENT_JOIN;
					mucce.dwFlags = MUCC_EF_ROOM_NICKNAMES;
					mucce.pszModule = jabberProtoName;
					mucce.pszID = from;
					mucce.pszName = item->roomName;
					mucce.pszNick = JabberXmlGetAttrValue(errorNode, "free");
					CallService(MS_MUCC_EVENT, 0, (LPARAM) &mucce);
				}
				break;
			case 601:
				item = JabberListGetItemPtr(LIST_CHATROOM, from);
				if (item!=NULL) {
					mucce.iType = MUCC_EVENT_JOIN;
					mucce.dwFlags = 0;
					mucce.pszModule = jabberProtoName;
					mucce.pszID = from;
					mucce.pszName = item->roomName;
					mucce.pszNick = NULL;
					CallService(MS_MUCC_EVENT, 0, (LPARAM) &mucce);
				}
				break;
		}
	}
	return 1;
}