struct CListEvent* cli_AddEvent(CLISTEVENT *cle)
{
	struct CListEvent* p = corecli.pfnAddEvent(cle);
	if (p == NULL)
		return NULL;

	if (p->cle.hContact != 0 && p->cle.hDbEvent != (HANDLE) 1 && !(p->cle.flags & CLEF_ONLYAFEW)) {
		MENUITEMINFO mii = { sizeof(mii) };
		mii.fMask = MIIM_DATA | MIIM_BITMAP | MIIM_ID;
		if (p->cle.pszService && 
			(!strncmp("SRMsg/ReadMessage", p->cle.pszService, SIZEOF("SRMsg/ReadMessage")) ||
			 !strncmp("GChat/DblClickEvent", p->cle.pszService, SIZEOF("GChat/DblClickEvent"))))
		{
			// dup check only for msg events
			for (int j = 0; j < GetMenuItemCount(g_CluiData.hMenuNotify); j++) {
				if (GetMenuItemInfo(g_CluiData.hMenuNotify, j, TRUE, &mii) != 0) {
					NotifyMenuItemExData *nmi = (struct NotifyMenuItemExData *) mii.dwItemData;
					if (nmi != 0 && (HANDLE) nmi->hContact == (HANDLE) p->cle.hContact && nmi->iIcon == p->imlIconIndex)
						return p;
		}	}	}

		char *szProto = GetContactProto(p->cle.hContact);
		TCHAR *szName = pcli->pfnGetContactDisplayName(p->cle.hContact, 0);
		if (szProto && szName) {
			NotifyMenuItemExData *nmi = (struct NotifyMenuItemExData *) malloc(sizeof(struct NotifyMenuItemExData));
			if (nmi) {
				TCHAR szBuffer[128];
				TCHAR* szStatus = pcli->pfnGetStatusModeDescription(db_get_w(p->cle.hContact, szProto, "Status", ID_STATUS_OFFLINE), 0);
				TCHAR szwProto[64];
				MultiByteToWideChar(CP_ACP, 0, szProto, -1, szwProto, 64);
				szwProto[63] = 0;
				mir_sntprintf(szBuffer, SIZEOF(szBuffer), _T("%s: %s (%s)"), szwProto, szName, szStatus);
				szBuffer[127] = 0;
				AppendMenu(g_CluiData.hMenuNotify, MF_BYCOMMAND | MF_STRING, g_CluiData.wNextMenuID, szBuffer);
				mii.hbmpItem = HBMMENU_CALLBACK;
				nmi->hContact = p->cle.hContact;
				nmi->iIcon = p->imlIconIndex;
				nmi->hIcon = p->cle.hIcon;
				nmi->hDbEvent = p->cle.hDbEvent;
				mii.dwItemData = (ULONG_PTR) nmi;
				mii.wID = g_CluiData.wNextMenuID;
				SetMenuItemInfo(g_CluiData.hMenuNotify, g_CluiData.wNextMenuID, FALSE, &mii);
				p-> menuId = g_CluiData.wNextMenuID;
				g_CluiData.wNextMenuID++;
				if (g_CluiData.wNextMenuID > 0x7fff)
					g_CluiData.wNextMenuID = 1;
				g_CluiData.iIconNotify = p->imlIconIndex;
			}
		}
	}
	else if (p->cle.hContact != 0 && (p->cle.flags & CLEF_ONLYAFEW)) {
		g_CluiData.iIconNotify = p->imlIconIndex;
		g_CluiData.hUpdateContact = p->cle.hContact;
	}

	if (pcli->events.count > 0) {
		g_CluiData.bEventAreaEnabled = TRUE;
		if (g_CluiData.bNotifyActive == FALSE) {
			g_CluiData.bNotifyActive = TRUE;
			EventArea_HideShowNotifyFrame();
		}
	}

	CLUI__cliInvalidateRect(g_CluiData.hwndEventFrame, NULL, FALSE);
	return p;
}