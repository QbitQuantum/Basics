JABBER_LIST_ITEM *JabberListAdd(JABBER_LIST list, const char *jid)
{
	char *s, *p, *q;
	JABBER_LIST_ITEM *item;

	EnterCriticalSection(&csLists);
	if ((item=JabberListGetItemPtr(list, jid)) != NULL) {
		LeaveCriticalSection(&csLists);
		return item;
	}

	s = mir_strdup(jid); _strlwr(s);
	// strip resource name if any
	if ((p=strchr(s, '@')) != NULL) {
		if ((q=strchr(p, '/')) != NULL)
			*q = '\0';
	}

	lists = (JABBER_LIST_ITEM *) mir_realloc(lists, sizeof(JABBER_LIST_ITEM)*(count+1));
	item = &(lists[count]);
	memset(item, 0, sizeof(JABBER_LIST_ITEM));
	item->list = list;
	item->jid = s;
	item->nick = NULL;
	item->status = ID_STATUS_OFFLINE;
	item->statusMessage = NULL;
	item->group = NULL;
	item->messageEventIdStr = NULL;
	item->wantComposingEvent = FALSE;
	item->isTyping = FALSE;
//	item->type = NULL;
	item->ft = NULL;
	item->roomName = NULL;
	item->version = NULL;
	item->software = NULL;
	item->system = NULL;
	item->avatarHash = NULL;
	item->avatarFormat = PA_FORMAT_UNKNOWN;
	item->newAvatarDownloading = FALSE;
	item->versionRequested = FALSE;
	item->infoRequested = FALSE;
	count++;
	LeaveCriticalSection(&csLists);

	return item;
}