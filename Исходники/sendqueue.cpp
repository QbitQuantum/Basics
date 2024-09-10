int SendQueue::doSendLater(int iJobIndex, TWindowData *dat, MCONTACT hContact, bool fIsSendLater)
{
	bool  fAvail = sendLater->isAvail();

	const TCHAR *szNote = 0;

	if (fIsSendLater && dat) {
		if (fAvail)
			szNote = TranslateT("Message successfully queued for later delivery.\nIt will be sent as soon as possible and a popup will inform you about the result.");
		else
			szNote = TranslateT("The send later feature is not available on this protocol.");

		T2Utf utfText(szNote);
		DBEVENTINFO dbei;
		dbei.cbSize = sizeof(dbei);
		dbei.eventType = EVENTTYPE_MESSAGE;
		dbei.flags = DBEF_SENT | DBEF_UTF;
		dbei.szModule = GetContactProto(dat->hContact);
		dbei.timestamp = time(NULL);
		dbei.cbBlob = (int)mir_strlen(utfText) + 1;
		dbei.pBlob = (PBYTE)(char*)utfText;
		StreamInEvents(dat->hwnd, 0, 1, 1, &dbei);
		if (dat->hDbEventFirst == NULL)
			SendMessage(dat->hwnd, DM_REMAKELOG, 0, 0);
		dat->cache->saveHistory(0, 0);
		EnableSendButton(dat, FALSE);
		if (dat->pContainer->hwndActive == dat->hwnd)
			UpdateReadChars(dat);
		SendDlgItemMessage(dat->hwnd, IDC_SAVE, BM_SETIMAGE, IMAGE_ICON, (LPARAM)PluginConfig.g_buttonBarIcons[ICON_BUTTON_CANCEL]);
		SendDlgItemMessage(dat->hwnd, IDC_SAVE, BUTTONADDTOOLTIP, (WPARAM)pszIDCSAVE_close, BATF_TCHAR);
		dat->dwFlags &= ~MWF_SAVEBTN_SAV;

		if (!fAvail)
			return 0;
	}

	if (iJobIndex >= 0 && iJobIndex < NR_SENDJOBS) {
		SendJob *job = &m_jobs[iJobIndex];
		char szKeyName[20];
		TCHAR tszHeader[150];

		if (fIsSendLater) {
			time_t now = time(0);
			TCHAR tszTimestamp[30];
			_tcsftime(tszTimestamp, _countof(tszTimestamp), _T("%Y.%m.%d - %H:%M"), _localtime32((__time32_t *)&now));
			mir_snprintf(szKeyName, "S%d", now);
			mir_sntprintf(tszHeader, TranslateT("\n(Sent delayed. Original timestamp %s)"), tszTimestamp);
		}
		else mir_sntprintf(tszHeader, _T("M%d|"), time(0));

		T2Utf utf_header(tszHeader);
		size_t required = mir_strlen(utf_header) + mir_strlen(job->szSendBuffer) + 10;
		char *tszMsg = reinterpret_cast<char *>(mir_alloc(required));

		if (fIsSendLater) {
			mir_snprintf(tszMsg, required, "%s%s", job->szSendBuffer, utf_header);
			db_set_s(hContact ? hContact : job->hContact, "SendLater", szKeyName, tszMsg);
		}
		else {
			mir_snprintf(tszMsg, required, "%s%s", utf_header, job->szSendBuffer);
			sendLater->addJob(tszMsg, hContact);
		}
		mir_free(tszMsg);

		if (fIsSendLater) {
			int iCount = db_get_dw(hContact ? hContact : job->hContact, "SendLater", "count", 0);
			iCount++;
			db_set_dw(hContact ? hContact : job->hContact, "SendLater", "count", iCount);
			sendLater->addContact(hContact ? hContact : job->hContact);
		}
		return iJobIndex;
	}
	return -1;
}