STDMETHODIMP_(MEVENT) CDbxKyoto::AddEvent(MCONTACT contactID, DBEVENTINFO *dbei)
{
	if (dbei == NULL || dbei->cbSize != sizeof(DBEVENTINFO)) return 0;
	if (dbei->timestamp == 0) return 0;

	DBEvent dbe;
	dbe.dwSignature = DBEVENT_SIGNATURE;
	dbe.contactID = contactID; // store native or subcontact's id
	dbe.ofsModuleName = GetModuleNameOfs(dbei->szModule);
	dbe.timestamp = dbei->timestamp;
	dbe.flags = dbei->flags;
	dbe.wEventType = dbei->eventType;
	dbe.cbBlob = dbei->cbBlob;
	BYTE *pBlob = dbei->pBlob;

	MCONTACT contactNotifyID = contactID;
	DBCachedContact *cc, *ccSub = NULL;
	if ((cc = m_cache->GetCachedContact(contactID)) == NULL)
		return 0;

	if (cc->IsSub()) {
		ccSub = cc;
		if ((cc = m_cache->GetCachedContact(cc->parentID)) == NULL)
			return 0;

		// set default sub to the event's source
		if (!(dbei->flags & DBEF_SENT))
			db_mc_setDefault(cc->contactID, contactID, false);
		contactID = cc->contactID; // and add an event to a metahistory
		if (db_mc_isEnabled())
			contactNotifyID = contactID;
	}

	if (m_safetyMode)
		if (NotifyEventHooks(hEventFilterAddedEvent, contactNotifyID, (LPARAM)dbei))
			return NULL;

	mir_ptr<BYTE> pCryptBlob;
	if (m_bEncrypted) {
		size_t len;
		BYTE *pResult = m_crypto->encodeBuffer(pBlob, dbe.cbBlob, &len);
		if (pResult != NULL) {
			pCryptBlob = pBlob = pResult;
			dbe.cbBlob = (DWORD)len;
			dbe.flags |= DBEF_ENCRYPTED;
		}
	}
	DWORD dwEventId;
	{
		mir_cslock lck(m_csDbAccess);
		dwEventId = ++m_dwMaxEventId;

		BYTE *pDest = (BYTE*)_alloca(sizeof(DBEvent) + dbe.cbBlob);
		memcpy(pDest, &dbe, sizeof(DBEvent));
		memcpy(pDest + sizeof(DBEvent), pBlob, dbe.cbBlob);
		m_dbEvents.set((LPCSTR)&dwEventId, sizeof(int), (LPCSTR)pDest, sizeof(DBEvent) + dbe.cbBlob);

		// add a sorting key
		DBEventSortingKey key2 = { contactID, dbe.timestamp, dwEventId };
		m_dbEventsSort.set((LPCSTR)&key2, sizeof(key2), "", 1);

		cc->Advance(dwEventId, dbe);
		m_dbContacts.set((LPCSTR)&contactID, sizeof(int), (LPCSTR)&cc->dbc, sizeof(DBContact));

		// insert an event into a sub's history too
		if (ccSub != NULL) {
			key2.dwContactId = ccSub->contactID;
			m_dbEventsSort.set((LPCSTR)&key2, sizeof(key2), "", 1);

			ccSub->Advance(dwEventId, dbe);
			m_dbContacts.set((LPCSTR)&ccSub->contactID, sizeof(int), (LPCSTR)&ccSub->dbc, sizeof(DBContact));
		}
	}

	// Notify only in safe mode or on really new events
	if (m_safetyMode)
		NotifyEventHooks(hEventAddedEvent, contactNotifyID, dwEventId);

	return dwEventId;
}