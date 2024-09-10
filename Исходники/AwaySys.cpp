INT_PTR srvVariablesHandler(WPARAM, LPARAM lParam)
{
	ARGUMENTSINFO *ai = (ARGUMENTSINFO*)lParam;
	ai->flags = AIF_DONTPARSE;
	TCString Result;
	if (!mir_tstrcmp(ai->targv[0], VAR_AWAYSINCE_TIME)) {
		GetTimeFormat(LOCALE_USER_DEFAULT, 0, g_ProtoStates[VarParseData.szProto].m_awaySince, (ai->argc > 1 && *ai->targv[1]) ? ai->targv[1] : _T("H:mm"), Result.GetBuffer(256), 256);
		Result.ReleaseBuffer();
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_AWAYSINCE_DATE)) {
		GetDateFormat(LOCALE_USER_DEFAULT, 0, g_ProtoStates[VarParseData.szProto].m_awaySince, (ai->argc > 1 && *ai->targv[1]) ? ai->targv[1] : NULL, Result.GetBuffer(256), 256);
		Result.ReleaseBuffer();
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_STATDESC)) {
		Result = (VarParseData.Flags & VPF_XSTATUS) ? STR_XSTATUSDESC : pcli->pfnGetStatusModeDescription(g_ProtoStates[VarParseData.szProto].m_status, 0);
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_MYNICK)) {
		if (g_MoreOptPage.GetDBValueCopy(IDC_MOREOPTDLG_MYNICKPERPROTO) && VarParseData.szProto)
			Result = db_get_s(NULL, VarParseData.szProto, "Nick", (TCHAR*)NULL);

		if (Result == NULL)
			Result = pcli->pfnGetContactDisplayName(NULL, 0);

		if (Result == NULL)
			Result = TranslateT("Stranger");
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_REQUESTCOUNT)) {
		mir_sntprintf(Result.GetBuffer(16), 16, _T("%d"), db_get_w(ai->fi->hContact, MOD_NAME, DB_REQUESTCOUNT, 0));
		Result.ReleaseBuffer();
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_MESSAGENUM)) {
		mir_sntprintf(Result.GetBuffer(16), 16, _T("%d"), db_get_w(ai->fi->hContact, MOD_NAME, DB_MESSAGECOUNT, 0));
		Result.ReleaseBuffer();
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_TIMEPASSED)) {
		ULARGE_INTEGER ul_AwaySince, ul_Now;
		SYSTEMTIME st;
		GetLocalTime(&st);
		SystemTimeToFileTime(&st, (LPFILETIME)&ul_Now);
		SystemTimeToFileTime(g_ProtoStates[VarParseData.szProto].m_awaySince, (LPFILETIME)&ul_AwaySince);
		ul_Now.QuadPart -= ul_AwaySince.QuadPart;
		ul_Now.QuadPart /= 10000000; // now it's in seconds
		Result.GetBuffer(256);
		if (ul_Now.LowPart >= 7200) // more than 2 hours
			mir_sntprintf(Result, 256, TranslateT("%d hours"), ul_Now.LowPart / 3600);
		else if (ul_Now.LowPart >= 120) // more than 2 minutes
			mir_sntprintf(Result, 256, TranslateT("%d minutes"), ul_Now.LowPart / 60);
		else
			mir_sntprintf(Result, 256, TranslateT("%d seconds"), ul_Now.LowPart);
		Result.ReleaseBuffer();
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_PREDEFINEDMESSAGE)) {
		ai->flags = 0; // reset AIF_DONTPARSE flag
		if (ai->argc != 2)
			return NULL;

		COptPage MsgTreeData(g_MsgTreePage);
		COptItem_TreeCtrl *TreeCtrl = (COptItem_TreeCtrl*)MsgTreeData.Find(IDV_MSGTREE);
		TreeCtrl->DBToMem(CString(MOD_NAME));

		for (int i = 0; i < TreeCtrl->m_value.GetSize(); i++) {
			if (!(TreeCtrl->m_value[i].Flags & TIF_GROUP) && !mir_tstrcmpi(TreeCtrl->m_value[i].Title, ai->targv[1])) {
				Result = TreeCtrl->m_value[i].User_Str1;
				break;
			}
		}
		if (Result == NULL) // if we didn't find a message with specified title
			return NULL; // return it now, as later we change NULL to ""
	}
	else if (!mir_tstrcmp(ai->targv[0], VAR_PROTOCOL)) {
		if (VarParseData.szProto) {
			CString AnsiResult;
			CallProtoService(VarParseData.szProto, PS_GETNAME, 256, (LPARAM)AnsiResult.GetBuffer(256));
			AnsiResult.ReleaseBuffer();
			Result = _A2T(AnsiResult);
		}
		if (Result == NULL) // if we didn't find a message with specified title
			return NULL; // return it now, as later we change NULL to ""
	}
	TCHAR *szResult = (TCHAR*)malloc((Result.GetLen() + 1) * sizeof(TCHAR));
	if (!szResult)
		return NULL;

	mir_tstrcpy(szResult, (Result != NULL) ? Result : _T(""));
	return (INT_PTR)szResult;
}