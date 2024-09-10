BYTE GetCachedStatusMsg(TExtraCache *p, char *szProto)
{
	if (p == NULL)
		return 0;

	p->bStatusMsgValid = STATUSMSG_NOTFOUND;
	MCONTACT hContact = p->hContact;

	DBVARIANT dbv = {0};
	INT_PTR result = cfg::getTString(hContact, "CList", "StatusMsg", &dbv);
	if ( !result && lstrlen(dbv.ptszVal) > 0)
		p->bStatusMsgValid = STATUSMSG_CLIST;
	else {
		if ( !szProto)
			szProto = GetContactProto(hContact);
		if (szProto) {
			if ( !result )
				db_free( &dbv );
			if ( !( result = cfg::getTString(hContact, szProto, "YMsg", &dbv)) && lstrlen(dbv.ptszVal) > 0)
				p->bStatusMsgValid = STATUSMSG_YIM;
			else if ( !(result = cfg::getTString(hContact, szProto, "StatusDescr", &dbv)) && lstrlen(dbv.ptszVal) > 0)
				p->bStatusMsgValid = STATUSMSG_GG;
			else if ( !(result = cfg::getTString(hContact, szProto, "XStatusMsg", &dbv)) && lstrlen(dbv.ptszVal) > 0)
				p->bStatusMsgValid = STATUSMSG_XSTATUS;
		}
	}

	if (p->bStatusMsgValid == STATUSMSG_NOTFOUND) { // no status msg, consider xstatus name (if available)
		if ( !result )
			db_free( &dbv );
		result = cfg::getTString(hContact, szProto, "XStatusName", &dbv);
		if ( !result && lstrlen(dbv.ptszVal) > 1) {
			int iLen = lstrlen(dbv.ptszVal);
			p->bStatusMsgValid = STATUSMSG_XSTATUSNAME;
			p->statusMsg = (TCHAR *)realloc(p->statusMsg, (iLen + 2) * sizeof(TCHAR));
			_tcsncpy(p->statusMsg, dbv.ptszVal, iLen + 1);
		}
		else {
			int xStatus;
			WPARAM xStatus2;
			TCHAR xStatusName[128];

			CUSTOM_STATUS cst = { sizeof(cst) };
			cst.flags = CSSF_MASK_STATUS;
			cst.status = &xStatus;
			if (ProtoServiceExists(szProto, PS_GETCUSTOMSTATUSEX) && !ProtoCallService(szProto, PS_GETCUSTOMSTATUSEX, hContact, (LPARAM)&cst) && xStatus > 0) {
				cst.flags = CSSF_MASK_NAME | CSSF_DEFAULT_NAME | CSSF_TCHAR;
 				cst.wParam = &xStatus2;
				cst.ptszName = xStatusName;
				if ( !CallProtoService(szProto, PS_GETCUSTOMSTATUSEX, hContact, (LPARAM)&cst)) {
					TCHAR *szwXstatusName = TranslateTS(xStatusName);
					p->statusMsg = (TCHAR *)realloc(p->statusMsg, (lstrlen(szwXstatusName) + 2) * sizeof(TCHAR));
					_tcsncpy(p->statusMsg, szwXstatusName, lstrlen(szwXstatusName) + 1);
					p->bStatusMsgValid = STATUSMSG_XSTATUSNAME;
				}
			}
		}
	}

	if (p->bStatusMsgValid > STATUSMSG_XSTATUSNAME) {
		int j = 0;
		p->statusMsg = (TCHAR *)realloc(p->statusMsg, (lstrlen(dbv.ptszVal) + 2) * sizeof(TCHAR));
		for (int i = 0; dbv.ptszVal[i]; i++) {
			if (dbv.ptszVal[i] == (TCHAR)0x0d)
				continue;
			p->statusMsg[j] = dbv.ptszVal[i] == (wchar_t)0x0a ? (wchar_t)' ' : dbv.ptszVal[i];
			j++;
		}
		p->statusMsg[j] = 0;
	}
	if ( !result )
		db_free( &dbv );

	if (p->bStatusMsgValid != STATUSMSG_NOTFOUND) {
		WORD infoTypeC2[12];
		ZeroMemory(infoTypeC2, sizeof(WORD) * 12);
		int iLen = min(lstrlenW(p->statusMsg), 10);
		GetStringTypeW(CT_CTYPE2, p->statusMsg, iLen, infoTypeC2);
		p->dwCFlags &= ~ECF_RTLSTATUSMSG;
		for (int i = 0; i < 10; i++) {
			if (infoTypeC2[i] == C2_RIGHTTOLEFT) {
				p->dwCFlags |= ECF_RTLSTATUSMSG;
				break;
			}
		}
	}

	if (p->hTimeZone == NULL)
		TZ_LoadTimeZone(hContact, p, szProto);
	return p->bStatusMsgValid;
}