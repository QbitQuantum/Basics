int __fastcall CLVM_GetContactHiddenStatus(MCONTACT hContact, char *szProto, ClcData *dat)
{
	int dbHidden = db_get_b(hContact, "CList", "Hidden", 0);		// default hidden state, always respect it.
	int filterResult = 1;
	int searchResult = 0;
	DBVARIANT dbv = { 0 };
	char szTemp[64];
	TCHAR szGroupMask[256];
	DWORD dwLocalMask;
	ClcCacheEntry *pdnce = pcli->pfnGetCacheEntry(hContact);
	// always hide subcontacts (but show them on embedded contact lists)

	if (dat != NULL && dat->IsMetaContactsEnabled && db_mc_isSub(hContact))
		return -1; //subcontact
	if (pdnce && pdnce->isUnknown && dat != NULL && !dat->force_in_dialog)
		return 1; //'Unknown Contact'
	if (dat != NULL && dat->filterSearch && pdnce && pdnce->tszName) {
		// search filtering
		TCHAR *lowered_name = CharLowerW(NEWTSTR_ALLOCA(pdnce->tszName));
		TCHAR *lowered_search = CharLowerW(NEWTSTR_ALLOCA(dat->szQuickSearch));
		searchResult = _tcsstr(lowered_name, lowered_search) ? 0 : 1;
	}
	if (pdnce && g_CluiData.bFilterEffective && dat != NULL && !dat->force_in_dialog) {
		if (szProto == NULL)
			szProto = GetContactProto(hContact);
		// check stickies first (priority), only if we really have stickies defined (CLVM_STICKY_CONTACTS is set).
		if (g_CluiData.bFilterEffective & CLVM_STICKY_CONTACTS) {
			if ((dwLocalMask = db_get_dw(hContact, CLVM_MODULE, g_CluiData.current_viewmode, 0)) != 0) {
				if (g_CluiData.bFilterEffective & CLVM_FILTER_STICKYSTATUS) {
					WORD wStatus = db_get_w(hContact, szProto, "Status", ID_STATUS_OFFLINE);
					return !((1 << (wStatus - ID_STATUS_OFFLINE)) & HIWORD(dwLocalMask)) | searchResult;
				}
				return 0 | searchResult;
			}
		}
		// check the proto, use it as a base filter result for all further checks
		if (g_CluiData.bFilterEffective & CLVM_FILTER_PROTOS) {
			mir_snprintf(szTemp, "%s|", szProto);
			filterResult = strstr(g_CluiData.protoFilter, szTemp) ? 1 : 0;
		}
		if (g_CluiData.bFilterEffective & CLVM_FILTER_GROUPS) {
			if (!db_get_ts(hContact, "CList", "Group", &dbv)) {
				mir_sntprintf(szGroupMask, _T("%s|"), &dbv.ptszVal[0]);
				filterResult = (g_CluiData.filterFlags & CLVM_PROTOGROUP_OP) ? (filterResult | (_tcsstr(g_CluiData.groupFilter, szGroupMask) ? 1 : 0)) : (filterResult & (_tcsstr(g_CluiData.groupFilter, szGroupMask) ? 1 : 0));
				mir_free(dbv.ptszVal);
			}
			else if (g_CluiData.filterFlags & CLVM_INCLUDED_UNGROUPED)
				filterResult = (g_CluiData.filterFlags & CLVM_PROTOGROUP_OP) ? filterResult : filterResult & 1;
			else
				filterResult = (g_CluiData.filterFlags & CLVM_PROTOGROUP_OP) ? filterResult : filterResult & 0;
		}
		if (g_CluiData.bFilterEffective & CLVM_FILTER_STATUS) {
			WORD wStatus = db_get_w(hContact, szProto, "Status", ID_STATUS_OFFLINE);
			filterResult = (g_CluiData.filterFlags & CLVM_GROUPSTATUS_OP) ? ((filterResult | ((1 << (wStatus - ID_STATUS_OFFLINE)) & g_CluiData.statusMaskFilter ? 1 : 0))) : (filterResult & ((1 << (wStatus - ID_STATUS_OFFLINE)) & g_CluiData.statusMaskFilter ? 1 : 0));
		}
		if (g_CluiData.bFilterEffective & CLVM_FILTER_LASTMSG) {
			if (pdnce->dwLastMsgTime != -1) {
				DWORD now = g_CluiData.t_now;
				now -= g_CluiData.lastMsgFilter;
				if (g_CluiData.bFilterEffective & CLVM_FILTER_LASTMSG_OLDERTHAN)
					filterResult = filterResult & (pdnce->dwLastMsgTime < now);
				else if (g_CluiData.bFilterEffective & CLVM_FILTER_LASTMSG_NEWERTHAN)
					filterResult = filterResult & (pdnce->dwLastMsgTime > now);
			}
		}
		return (dbHidden | !filterResult | searchResult);
	}

	return dbHidden | searchResult;
}