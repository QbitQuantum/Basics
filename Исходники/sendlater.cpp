// fills the list of jobs with current contents of the job queue
// filters by m_hFilter (contact handle)
//
void CSendLater::qMgrFillList(bool fClear)
{
	TCHAR *formatTime = _T("%Y.%m.%d - %H:%M");

	if (fClear) {
		::SendMessage(m_hwndList, LVM_DELETEALLITEMS, 0, 0);
		::SendMessage(m_hwndFilter, CB_RESETCONTENT, 0, 0);
	}

	m_sel = 0;
	::SendMessage(m_hwndFilter, CB_INSERTSTRING, -1, 
				  LPARAM(TranslateT("<All contacts>")));
	::SendMessage(m_hwndFilter, CB_SETITEMDATA, 0, 0);

	LVITEM lvItem = { 0 };
	lvItem.cchTextMax = 255;

	BYTE bCode = '-';
	unsigned uIndex = 0;
	for (int i = 0; i < m_sendLaterJobList.getCount(); i++) {
		CSendLaterJob *p = m_sendLaterJobList[i];
		CContactCache *c = CContactCache::getContactCache(p->hContact);
		if (c) {
			const TCHAR *tszNick = c->getNick();
			if (m_hFilter && m_hFilter != p->hContact) {
				qMgrAddFilter(c->getContact(), tszNick);
				continue;
			}

			lvItem.mask = LVIF_TEXT|LVIF_PARAM;
			TCHAR tszBuf[255];
			mir_sntprintf(tszBuf, 255, _T("%s [%s]"), tszNick, c->getRealAccount());
			lvItem.pszText = tszBuf;
			lvItem.iItem = uIndex++;
			lvItem.iSubItem = 0;
			lvItem.lParam = LPARAM(p);
			::SendMessage(m_hwndList, LVM_INSERTITEM, 0, LPARAM(&lvItem));
			qMgrAddFilter(c->getContact(), tszNick);

			lvItem.mask = LVIF_TEXT;
			TCHAR tszTimestamp[30];
			_tcsftime(tszTimestamp, 30, formatTime, _localtime32((__time32_t *)&p->created));
			tszTimestamp[29] = 0;
			lvItem.pszText = tszTimestamp;
			lvItem.iSubItem = 1;
			::SendMessage(m_hwndList, LVM_SETITEM, 0, LPARAM(&lvItem));

			TCHAR *msg = mir_utf8decodeT(p->sendBuffer);
			TCHAR *preview = Utils::GetPreviewWithEllipsis(msg, 255);
			lvItem.pszText = preview;
			lvItem.iSubItem = 2;
			::SendMessage(m_hwndList, LVM_SETITEM, 0, LPARAM(&lvItem));
			mir_free(preview);
			mir_free(msg);

			const TCHAR *tszStatusText = 0;
			if (p->fFailed) {
				tszStatusText = p->bCode == CSendLaterJob::JOB_REMOVABLE ? 
					TranslateT("Removed") : TranslateT("Failed");
			}
			else if (p->fSuccess)
				tszStatusText = TranslateT("Sent OK");
			else {
				switch(p->bCode) {
				case CSendLaterJob::JOB_DEFERRED:
					tszStatusText = TranslateT("Deferred");
					break;
				case CSendLaterJob::JOB_AGE:
					tszStatusText = TranslateT("Failed");
					break;
				case CSendLaterJob::JOB_HOLD:
					tszStatusText = TranslateT("Suspended");
					break;
				default:
					tszStatusText = TranslateT("Pending");
					break;
				}
			}
			if (p->bCode)
				bCode = p->bCode;
			
			TCHAR tszStatus[20];
			mir_sntprintf(tszStatus, 20, _T("X/%s[%c] (%d)"), tszStatusText, bCode, p->iSendCount);
			tszStatus[0] = p->szId[0];
			lvItem.pszText = tszStatus;
			lvItem.iSubItem = 3;
			::SendMessage(m_hwndList, LVM_SETITEM, 0, LPARAM(&lvItem));

			if (p->lastSent == 0)
				mir_sntprintf(tszTimestamp, 30, _T("%s"), _T("Never"));
			else {
				_tcsftime(tszTimestamp, 30, formatTime, _localtime32((__time32_t *)&p->lastSent));
				tszTimestamp[29] = 0;
			}
			lvItem.pszText = tszTimestamp;
			lvItem.iSubItem = 4;
			::SendMessage(m_hwndList, LVM_SETITEM, 0, LPARAM(&lvItem));
		}
	}

	if (m_hFilter == 0)
		::SendMessage(m_hwndFilter, CB_SETCURSEL, 0, 0);
	else
		::SendMessage(m_hwndFilter, CB_SETCURSEL, m_sel, 0);
}