INT_PTR StatusMenuCheckService(WPARAM wParam, LPARAM)
{
	PCheckProcParam pcpp = (PCheckProcParam)wParam;
	if (!pcpp)
		return TRUE;

	PMO_IntMenuItem timi = MO_GetIntMenuItem(pcpp->MenuItemHandle);
	if (!timi)
		return TRUE;

	StatusMenuExecParam *smep = (StatusMenuExecParam*)pcpp->MenuItemOwnerData;
	if (smep && !smep->status && smep->custom) {
		if (wildcmp(smep->svc, "*XStatus*")) {
			int XStatus;
			CUSTOM_STATUS cs = { sizeof(cs) };
			cs.flags = CSSF_MASK_STATUS;
			cs.status = &XStatus;
			if (CallProtoServiceInt(NULL, smep->proto, PS_GETCUSTOMSTATUSEX, 0, (LPARAM)&cs) != 0)
				XStatus = 0;

			char buf[255];
			mir_snprintf(buf, SIZEOF(buf), "*XStatus%d", XStatus);

			bool check = wildcmp(smep->svc, buf) != 0;
			bool reset = wildcmp(smep->svc, "*XStatus0") != 0;

			if (check)
				timi->mi.flags |= CMIF_CHECKED;
			else
				timi->mi.flags &= ~CMIF_CHECKED;

			if (reset || check) {
				PMO_IntMenuItem timiParent = MO_GetIntMenuItem(timi->mi.root);
				if (timiParent) {
					CLISTMENUITEM mi2 = { sizeof(mi2) };
					mi2.flags = CMIM_NAME | CMIF_TCHAR;
					mi2.ptszName = TranslateTH(timi->mi.hLangpack, timi->mi.hIcon ? timi->mi.ptszName : LPGENT("Custom status"));

					timiParent = MO_GetIntMenuItem(timi->mi.root);

					MenuItemData it = { 0 };

					if (FindMenuHandleByGlobalID(hStatusMenu, timiParent, &it)) {
						MENUITEMINFO mi = { 0 };
						TCHAR d[100];
						GetMenuString(it.OwnerMenu, it.position, d, SIZEOF(d), MF_BYPOSITION);

						mi.cbSize = sizeof(mi);
						mi.fMask = MIIM_STRING | MIIM_STATE;
						if (timi->iconId != -1) {
							mi.fMask |= MIIM_BITMAP;
							if (IsWinVerVistaPlus() && IsThemeActive()) {
								if (timi->hBmp == NULL)
									timi->hBmp = ConvertIconToBitmap(NULL, timi->parent->m_hMenuIcons, timi->iconId);
								mi.hbmpItem = timi->hBmp;
							}
							else mi.hbmpItem = HBMMENU_CALLBACK;
						}

						mi.fState |= (check && !reset ? MFS_CHECKED : MFS_UNCHECKED);
						mi.dwTypeData = mi2.ptszName;
						SetMenuItemInfo(it.OwnerMenu, it.position, TRUE, &mi);
					}

					Menu_ModifyItem(timi->mi.root, &mi2);
					timiParent->iconId = timi->iconId;
					if (timiParent->hBmp) DeleteObject(timiParent->hBmp);
					timiParent->hBmp = NULL;
				}
			}
		}
	}
	else if (smep && smep->status && !smep->custom) {
		int curProtoStatus = (smep->proto) ? CallProtoServiceInt(NULL, smep->proto, PS_GETSTATUS, 0, 0) : cli.pfnGetAverageMode(NULL);
		if (smep->status == curProtoStatus)
			timi->mi.flags |= CMIF_CHECKED;
		else
			timi->mi.flags &= ~CMIF_CHECKED;
	}
	else if ((!smep || smep->proto) && timi->mi.pszName) {
		int curProtoStatus = 0;
		BOOL IconNeedDestroy = FALSE;
		char* prot;
		if (smep)
			prot = smep->proto;
		else {
			char *prn = mir_u2a(timi->mi.ptszName);
			prot = NEWSTR_ALLOCA(prn);
			if (prn) mir_free(prn);
		}
		if (Proto_GetAccount(prot) == NULL)
			return TRUE;

		if ((curProtoStatus = CallProtoServiceInt(NULL, prot, PS_GETSTATUS, 0, 0)) == CALLSERVICE_NOTFOUND)
			curProtoStatus = 0;

		if (curProtoStatus >= ID_STATUS_OFFLINE && curProtoStatus < ID_STATUS_IDLE)
			timi->mi.hIcon = LoadSkinProtoIcon(prot, curProtoStatus);
		else {
			timi->mi.hIcon = (HICON)CallProtoServiceInt(NULL, prot, PS_LOADICON, PLI_PROTOCOL | PLIF_SMALL, 0);
			if (timi->mi.hIcon == (HICON)CALLSERVICE_NOTFOUND)
				timi->mi.hIcon = NULL;
			else
				IconNeedDestroy = TRUE;
		}

		if (timi->mi.hIcon) {
			timi->mi.flags |= CMIM_ICON;
			MO_ModifyMenuItem(timi, &timi->mi);
			if (IconNeedDestroy) {
				DestroyIcon(timi->mi.hIcon);
				timi->mi.hIcon = NULL;
			}
			else IcoLib_ReleaseIcon(timi->mi.hIcon, 0);
		}
	}

	return TRUE;
}