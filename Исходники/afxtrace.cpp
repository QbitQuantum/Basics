static void AFXAPI TraceDDE(LPCTSTR lpszPrefix, const MSG* pMsg)
{
	ENSURE_ARG(pMsg != NULL);
	if (pMsg->message == WM_DDE_EXECUTE)
	{
		UINT_PTR nDummy;
		HGLOBAL hCommands;
		if (!UnpackDDElParam(WM_DDE_EXECUTE, pMsg->lParam,
			&nDummy, (UINT_PTR*)&hCommands))
		{
			TRACE(traceAppMsg, 0, "Warning: Unable to unpack WM_DDE_EXECUTE lParam %08lX.\n",
				pMsg->lParam);
			return;
		}
		ASSERT(hCommands != NULL);

		LPCTSTR lpszCommands = (LPCTSTR)::GlobalLock(hCommands);
		ENSURE_THROW(lpszCommands != NULL, ::AfxThrowMemoryException() );
		TRACE(traceAppMsg, 0, _T("%s: Execute '%s'.\n"), lpszPrefix, lpszCommands);
		::GlobalUnlock(hCommands);
	}
	else if (pMsg->message == WM_DDE_ADVISE)
	{
		UINT_PTR nItem;
		ATOM aItem;
		HGLOBAL hAdvise;
		if (!UnpackDDElParam(WM_DDE_ADVISE, pMsg->lParam,
			(UINT_PTR*)&hAdvise, &nItem))
		{
			TRACE(traceAppMsg, 0, "Warning: Unable to unpack WM_DDE_ADVISE lParam %08lX.\n",
				pMsg->lParam);
			return;
		}
		aItem = (ATOM)nItem;
		ASSERT(aItem != NULL);
		ASSERT(hAdvise != NULL);

		DDEADVISE* lpAdvise = (DDEADVISE*)::GlobalLock(hAdvise);
		ENSURE_THROW(lpAdvise != NULL, ::AfxThrowMemoryException() );
		TCHAR szItem[80];
		szItem[0] = '\0';

		if (aItem != 0)
			::GlobalGetAtomName(aItem, szItem, _countof(szItem));

		TCHAR szFormat[80];
		szFormat[0] = '\0';
		if (((UINT)0xC000 <= (UINT)lpAdvise->cfFormat) &&
				((UINT)lpAdvise->cfFormat <= (UINT)0xFFFF))
		{
			::GetClipboardFormatName(lpAdvise->cfFormat,
				szFormat, _countof(szFormat));

			// User defined clipboard formats have a range of 0xC000->0xFFFF
			// System clipboard formats have other ranges, but no printable
			// format names.
		}

		AfxTrace(
			_T("%s: Advise item='%s', Format='%s', Ack=%d, Defer Update= %d\n"),
			 lpszPrefix, szItem, szFormat, lpAdvise->fAckReq,
			lpAdvise->fDeferUpd);
		::GlobalUnlock(hAdvise);
	}
}