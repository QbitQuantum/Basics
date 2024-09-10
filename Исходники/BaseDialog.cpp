void CBaseDialog::OnNotificationsOn()
{
	HRESULT			hRes = S_OK;

	if (m_lpBaseAdviseSink || !m_lpMapiObjects) return;

	LPMDB			lpMDB = m_lpMapiObjects->GetMDB(); // do not release
	LPMAPISESSION	lpMAPISession = m_lpMapiObjects->GetSession(); // do not release
	LPADRBOOK		lpAB = m_lpMapiObjects->GetAddrBook(false); // do not release

	CEditor MyData(
		this,
		IDS_NOTIFICATIONS,
		IDS_NOTIFICATIONSPROMPT,
		3,
		CEDITOR_BUTTON_OK | CEDITOR_BUTTON_CANCEL);
	MyData.SetPromptPostFix(AllFlagsToString(flagNotifEventType, true));
	MyData.InitPane(0, CreateSingleLinePane(IDS_EID, NULL, false));
	MyData.InitPane(1, CreateSingleLinePane(IDS_ULEVENTMASK, NULL, false));
	MyData.SetHex(1, fnevNewMail);
	UINT uidDropDown[] = {
		IDS_DDMESSAGESTORE,
		IDS_DDSESSION,
		IDS_DDADDRESSBOOK
	};
	MyData.InitPane(2, CreateDropDownPane(IDS_OBJECTFORADVISE, _countof(uidDropDown), uidDropDown, true));

	WC_H(MyData.DisplayDialog());

	if (S_OK == hRes)
	{
		if ((0 == MyData.GetDropDown(2) && !lpMDB) ||
			(1 == MyData.GetDropDown(2) && !lpMAPISession) ||
			(2 == MyData.GetDropDown(2) && !lpAB))
		{
			ErrDialog(__FILE__, __LINE__, IDS_EDADVISE);
			return;
		}

		LPENTRYID	lpEntryID = NULL;
		size_t		cbBin = NULL;
		WC_H(MyData.GetEntryID(0, false, &cbBin, &lpEntryID));
		// don't actually care if the returning lpEntryID is NULL - Advise can work with that

		m_lpBaseAdviseSink = new CAdviseSink(m_hWnd, NULL);

		if (m_lpBaseAdviseSink)
		{
			switch (MyData.GetDropDown(2))
			{
			case 0:
				EC_MAPI(lpMDB->Advise(
					(ULONG)cbBin,
					lpEntryID,
					MyData.GetHex(1),
					(IMAPIAdviseSink *)m_lpBaseAdviseSink,
					&m_ulBaseAdviseConnection));
				m_lpBaseAdviseSink->SetAdviseTarget(lpMDB);
				m_ulBaseAdviseObjectType = MAPI_STORE;
				break;
			case 1:
				EC_MAPI(lpMAPISession->Advise(
					(ULONG)cbBin,
					lpEntryID,
					MyData.GetHex(1),
					(IMAPIAdviseSink *)m_lpBaseAdviseSink,
					&m_ulBaseAdviseConnection));
				m_ulBaseAdviseObjectType = MAPI_SESSION;
				break;
			case 2:
				EC_MAPI(lpAB->Advise(
					(ULONG)cbBin,
					lpEntryID,
					MyData.GetHex(1),
					(IMAPIAdviseSink *)m_lpBaseAdviseSink,
					&m_ulBaseAdviseConnection));
				m_lpBaseAdviseSink->SetAdviseTarget(lpAB);
				m_ulBaseAdviseObjectType = MAPI_ADDRBOOK;
				break;
			}

			if (SUCCEEDED(hRes))
			{
				if (0 == MyData.GetDropDown(2) && lpMDB)
				{
					// Try to trigger some RPC to get the notifications going
					LPSPropValue lpProp = NULL;
					WC_MAPI(HrGetOneProp(
						lpMDB,
						PR_TEST_LINE_SPEED,
						&lpProp));
					if (MAPI_E_NOT_FOUND == hRes)
					{
						// We're not on an Exchange server. We don't need to generate RPC after all.
						hRes = S_OK;
					}
					MAPIFreeBuffer(lpProp);
				}
			}
			else // if we failed to advise, then we don't need the advise sink object
			{
				if (m_lpBaseAdviseSink) m_lpBaseAdviseSink->Release();
				m_lpBaseAdviseSink = NULL;
				m_ulBaseAdviseObjectType = NULL;
				m_ulBaseAdviseConnection = NULL;
			}
		}
		delete[] lpEntryID;
	}
} // CBaseDialog::OnNotificationsOn