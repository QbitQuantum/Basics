STDMETHODIMP_(BOOL) CDb3Mmap::DeleteContactSetting(MCONTACT contactID, LPCSTR szModule, LPCSTR szSetting)
{
	if (!szModule || !szSetting)
		return 1;

	// the db format can't tolerate more than 255 bytes of space (incl. null) for settings+module name
	int settingNameLen = (int)mir_strlen(szSetting);
	int moduleNameLen = (int)mir_strlen(szModule);
	if (settingNameLen > 0xFE) {
#ifdef _DEBUG
		OutputDebugStringA("DeleteContactSetting() got a > 255 setting name length. \n");
#endif
		return 1;
	}
	if (moduleNameLen > 0xFE) {
#ifdef _DEBUG
		OutputDebugStringA("DeleteContactSetting() got a > 255 module name length. \n");
#endif
		return 1;
	}

	MCONTACT saveContact = contactID;
	{
		mir_cslock lck(m_csDbAccess);
		char *szCachedSettingName = m_cache->GetCachedSetting(szModule, szSetting, moduleNameLen, settingNameLen);
		if (szCachedSettingName[-1] == 0) { // it's not a resident variable
			DWORD ofsModuleName = GetModuleNameOfs(szModule);
			DWORD ofsContact = GetContactOffset(contactID);
			DBContact *dbc = (DBContact*)DBRead(ofsContact, NULL);
			if (dbc->signature != DBCONTACT_SIGNATURE)
				return 1;

			// make sure the module group exists
			DWORD ofsSettingsGroup = GetSettingsGroupOfsByModuleNameOfs(dbc, ofsModuleName);
			if (ofsSettingsGroup == 0)
				return 1;

			// find if the setting exists
			DWORD ofsBlobPtr = ofsSettingsGroup + offsetof(DBContactSettings, blob);
			int bytesRemaining;
			PBYTE pBlob = (PBYTE)DBRead(ofsBlobPtr, &bytesRemaining);
			while (pBlob[0]) {
				NeedBytes(settingNameLen + 1);
				if (pBlob[0] == settingNameLen && !memcmp(pBlob + 1, szSetting, settingNameLen))
					break;
				NeedBytes(1);
				MoveAlong(pBlob[0] + 1);
				NeedBytes(3);
				MoveAlong(1 + GetSettingValueLength(pBlob));
				NeedBytes(1);
			}
			if (!pBlob[0]) //setting didn't exist
				return 1;

			// bin it
			MoveAlong(1 + settingNameLen);
			NeedBytes(3);
			int nameLen = 1 + settingNameLen;
			int valLen = 1 + GetSettingValueLength(pBlob);
			DWORD ofsSettingToCut = ofsBlobPtr - nameLen;
			MoveAlong(valLen);
			NeedBytes(1);
			while (pBlob[0]) {
				MoveAlong(pBlob[0] + 1);
				NeedBytes(3);
				MoveAlong(1 + GetSettingValueLength(pBlob));
				NeedBytes(1);
			}
			DBMoveChunk(ofsSettingToCut, ofsSettingToCut + nameLen + valLen, ofsBlobPtr + 1 - ofsSettingToCut);
			DBFlush(1);

			// remove a value from cache anyway
			m_cache->GetCachedValuePtr(saveContact, szCachedSettingName, -1);
		}
		else { // resident variable
			// if a value doesn't exist, simply return error
			if (m_cache->GetCachedValuePtr(saveContact, szCachedSettingName, -1) == NULL)
				return 1;
		}
	}

	// notify
	DBCONTACTWRITESETTING dbcws = { 0 };
	dbcws.szModule = szModule;
	dbcws.szSetting = szSetting;
	dbcws.value.type = DBVT_DELETED;
	NotifyEventHooks(hSettingChangeEvent, saveContact, (LPARAM)&dbcws);
	return 0;
}