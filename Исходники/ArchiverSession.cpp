HRESULT ArchiverSession::CreateArchiveStore(const tstring& strUserName, const tstring& strServerName, LPMDB *lppArchiveStore)
{
	HRESULT hr = hrSuccess;
	MsgStorePtr ptrRemoteAdminStore;
	ECServiceAdminPtr ptrRemoteServiceAdmin;
	abentryid_t userId;
	ULONG cbStoreId = 0;
	EntryIdPtr ptrStoreId;
	ULONG cbRootId = 0;
	EntryIdPtr ptrRootId;
	MsgStorePtr ptrArchiveStore;
	MAPIFolderPtr ptrRoot;
	ULONG ulType;
	MAPIFolderPtr ptrIpmSubtree;
	SPropValuePtr ptrIpmSubtreeId;

	hr = GetUserInfo(strUserName, &userId, NULL, NULL);
	if (hr != hrSuccess)
		goto exit;

	hr = HrGetRemoteAdminStore(m_ptrSession, m_ptrAdminStore, strServerName.c_str(), fMapiUnicode, &ptrRemoteAdminStore);
	if (hr != hrSuccess)
		goto exit;

	hr = ptrRemoteAdminStore.QueryInterface(ptrRemoteServiceAdmin);
	if (hr != hrSuccess)
		goto exit;

	hr = ptrRemoteServiceAdmin->CreateEmptyStore(ECSTORE_TYPE_ARCHIVE, userId.size(), userId, EC_OVERRIDE_HOMESERVER, &cbStoreId, &ptrStoreId, &cbRootId, &ptrRootId);
	if (hr != hrSuccess)
		goto exit;

	// The entryids returned from CreateEmptyStore are unwrapped and unusable from external client code. So
	// we'll resolve the correct entryids through GetArchiveStoreEntryID.
	hr = ptrRemoteServiceAdmin->GetArchiveStoreEntryID(strUserName.c_str(), strServerName.c_str(), fMapiUnicode, &cbStoreId, &ptrStoreId);
	if (hr != hrSuccess)
		goto exit;

	hr = m_ptrSession->OpenMsgStore(0, cbStoreId, ptrStoreId, &ptrArchiveStore.iid, MDB_WRITE, &ptrArchiveStore);
	if (hr != hrSuccess)
		goto exit;

	hr = ptrArchiveStore->OpenEntry(0, NULL, &ptrRoot.iid, MAPI_MODIFY, &ulType, &ptrRoot);
	if (hr != hrSuccess)
		goto exit;

	hr = ptrRoot->CreateFolder(FOLDER_GENERIC, _T("IPM_SUBTREE"), _T(""), &IID_IMAPIFolder, fMapiUnicode, &ptrIpmSubtree);
	if (hr != hrSuccess)
		goto exit;

	hr = HrGetOneProp(ptrIpmSubtree, PR_ENTRYID, &ptrIpmSubtreeId);
	if (hr != hrSuccess)
		goto exit;

	ptrIpmSubtreeId->ulPropTag = PR_IPM_SUBTREE_ENTRYID;
	
	hr = ptrArchiveStore->SetProps(1, ptrIpmSubtreeId, NULL);
	if (hr != hrSuccess)
		goto exit;

	hr = ptrArchiveStore->QueryInterface(IID_IMsgStore, (LPVOID*)lppArchiveStore);

exit:
	return hr;
}