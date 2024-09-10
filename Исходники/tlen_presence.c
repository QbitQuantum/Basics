static void JabberSendPresenceTo(TlenProtocol *proto, int status, char *to)
{
	char *showBody, *statusMsg, *presenceType;
	char *ptr = NULL;

	if (!proto->isOnline) return;

	// Send <presence/> update for status (we won't handle ID_STATUS_OFFLINE here)
	// Note: jabberModeMsg is already encoded using JabberTextEncode()
	EnterCriticalSection(&proto->modeMsgMutex);

	showBody = NULL;
	statusMsg = NULL;
	presenceType = NULL;
	switch (status) {
	case ID_STATUS_ONLINE:
		showBody = "available";
		statusMsg = proto->modeMsgs.szOnline;
		break;
	case ID_STATUS_AWAY:
	case ID_STATUS_ONTHEPHONE:
	case ID_STATUS_OUTTOLUNCH:
		showBody = "away";
		statusMsg = proto->modeMsgs.szAway;
		break;
	case ID_STATUS_NA:
		showBody = "xa";
		statusMsg = proto->modeMsgs.szNa;
		break;
	case ID_STATUS_DND:
	case ID_STATUS_OCCUPIED:
		showBody = "dnd";
		statusMsg = proto->modeMsgs.szDnd;
		break;
	case ID_STATUS_FREECHAT:
		showBody = "chat";
		statusMsg = proto->modeMsgs.szFreechat;
		break;
	case ID_STATUS_INVISIBLE:
		presenceType = "invisible";
		statusMsg = proto->modeMsgs.szInvisible;
		break;
	case ID_STATUS_OFFLINE:
		presenceType = "unavailable";
		if (DBGetContactSettingByte(NULL, proto->iface.m_szModuleName, "LeaveOfflineMessage", FALSE)) {
			int offlineMessageOption = DBGetContactSettingWord(NULL, proto->iface.m_szModuleName, "OfflineMessageOption", 0);
			if (offlineMessageOption == 0) {
				switch (proto->iface.m_iStatus) {
					case ID_STATUS_ONLINE:
						ptr = mir_strdup(proto->modeMsgs.szOnline);
						break;
					case ID_STATUS_AWAY:
					case ID_STATUS_ONTHEPHONE:
					case ID_STATUS_OUTTOLUNCH:
						ptr = mir_strdup(proto->modeMsgs.szAway);
						break;
					case ID_STATUS_NA:
						ptr = mir_strdup(proto->modeMsgs.szNa);
						break;
					case ID_STATUS_DND:
					case ID_STATUS_OCCUPIED:
						ptr = mir_strdup(proto->modeMsgs.szDnd);
						break;
					case ID_STATUS_FREECHAT:
						ptr = mir_strdup(proto->modeMsgs.szFreechat);
						break;
					case ID_STATUS_INVISIBLE:
						ptr = mir_strdup(proto->modeMsgs.szInvisible);
						break;
				}
			} else if (offlineMessageOption == 99) {

			} else if (offlineMessageOption < 7) {
				DBVARIANT dbv;
				const char *statusNames[] = {"OnDefault", "AwayDefault", "NaDefault", "DndDefault", "FreeChatDefault", "InvDefault"};
				if (!DBGetContactSetting(NULL, "SRAway", statusNames[offlineMessageOption-1], &dbv)) {
					int i;
					char substituteStr[128];
					ptr = mir_strdup(dbv.pszVal);
					DBFreeVariant(&dbv);
					for(i=0;ptr[i];i++) {
						if(ptr[i]!='%') continue;
						if(!_strnicmp(ptr+i,"%time%",6))
							GetTimeFormatA(LOCALE_USER_DEFAULT,TIME_NOSECONDS,NULL,NULL,substituteStr,sizeof(substituteStr));
						else if(!_strnicmp(ptr+i,"%date%",6))
							GetDateFormatA(LOCALE_USER_DEFAULT,DATE_SHORTDATE,NULL,NULL,substituteStr,sizeof(substituteStr));
						else continue;
						if(strlen(substituteStr)>6) ptr=(char*)mir_realloc(ptr,strlen(ptr)+1+strlen(substituteStr)-6);
						MoveMemory(ptr+i+strlen(substituteStr),ptr+i+6,strlen(ptr)-i-5);
						CopyMemory(ptr+i,substituteStr,strlen(substituteStr));
					}
				}
			}
		}
		statusMsg = ptr;
		break;
	default:
		// Should not reach here
		break;
	}
	proto->iface.m_iStatus = status;
	if (presenceType) {
		if (statusMsg)
			JabberSend(proto, "<presence type='%s'><status>%s</status></presence>", presenceType, statusMsg);
		else
			JabberSend(proto, "<presence type='%s'></presence>", presenceType);
	} else {
		if (statusMsg)
			JabberSend(proto, "<presence><show>%s</show><status>%s</status></presence>", showBody, statusMsg);
		else
			JabberSend(proto, "<presence><show>%s</show></presence>", showBody);
	}
	if (ptr) {
		mir_free(ptr);
	}
	LeaveCriticalSection(&proto->modeMsgMutex);
}