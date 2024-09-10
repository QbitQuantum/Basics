static int ModifyStatusIcon(WPARAM wParam, LPARAM lParam) {
	HANDLE hContact = (HANDLE)wParam;

	StatusIconData *sid = (StatusIconData *)lParam;
	struct StatusIconListNode *current = status_icon_list;

	while(current) {
		if(strcmp(current->sid.szModule, sid->szModule) == 0 && current->sid.dwId == sid->dwId) {
			if(!hContact) {
				current->sid.flags = sid->flags;
				if(sid->hIcon) {
					DestroyIcon(current->sid.hIcon);
					current->sid.hIcon = DuplicateIcon(NULL, sid->hIcon);
				}
				if(sid->hIconDisabled) {
					DestroyIcon(current->sid.hIconDisabled);
					current->sid.hIconDisabled = DuplicateIcon(NULL, sid->hIconDisabled);
				}
				if(sid->szTooltip) {
					if(current->sid.szTooltip) mir_free(current->sid.szTooltip);
					current->sid.szTooltip = mir_strdup(sid->szTooltip);
				}

				WindowList_Broadcast(g_dat->hParentWindowList, DM_STATUSICONCHANGE, 0, 0);
			} else {
				char buff[256];
				HWND hwnd;
				sprintf(buff, "SRMMStatusIconFlags%d", (int)sid->dwId);
				DBWriteContactSettingByte(hContact, sid->szModule, buff, (BYTE)sid->flags);
				hwnd = WindowList_Find(g_dat->hMessageWindowList, hContact);
				if (hwnd == NULL) {
					hwnd = SM_FindWindowByContact(hContact);

				}
				if (hwnd != NULL) {
					PostMessage(GetParent(hwnd), DM_STATUSICONCHANGE, 0, 0);
				}
			}
			return 0;
		}

		current = current->next;
	}

	return 1;
}