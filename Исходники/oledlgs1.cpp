COleConvertDialog::COleConvertDialog(COleClientItem* pItem, DWORD dwFlags,
	CLSID* pClassID, CWnd* pParentWnd) : COleDialog(pParentWnd)
{
	if (pItem != NULL)
		ASSERT_VALID(pItem);
	ASSERT(pClassID == NULL || AfxIsValidAddress(pClassID, sizeof(CLSID), FALSE));

	memset(&m_cv, 0, sizeof(m_cv)); // initialize structure to 0/NULL
	if (pClassID != NULL)
		m_cv.clsid = *pClassID;

	// fill in common part
	m_cv.cbStruct = sizeof(m_cv);
	m_cv.dwFlags = dwFlags;
	if (!afxData.bWin4 && AfxHelpEnabled())
		m_cv.dwFlags |= CF_SHOWHELPBUTTON;
	m_cv.lpfnHook = AfxOleHookProc;
	m_nIDHelp = AFX_IDD_CONVERT;

	// specific to this dialog
	m_cv.fIsLinkedObject = pItem->GetType() == OT_LINK;
	m_cv.dvAspect = pItem->GetDrawAspect();
	if (pClassID == NULL && !m_cv.fIsLinkedObject)
	{
		// for embeddings, attempt to get class ID from the storage
		if (ReadClassStg(pItem->m_lpStorage, &m_cv.clsid) == S_OK)
			pClassID = &m_cv.clsid;

		// attempt to get user type from storage
		CLIPFORMAT cf = 0;
		LPOLESTR lpOleStr = NULL;
		ReadFmtUserTypeStg(pItem->m_lpStorage, &cf, &lpOleStr);
		m_cv.lpszUserType = TASKSTRINGOLE2T(lpOleStr);

		m_cv.wFormat = (WORD)cf;
	}
	// get class id if neded
	if (pClassID == NULL)
	{
		// no class ID in the storage, use class ID of the object
		pItem->GetClassID(&m_cv.clsid);
	}

	// get user type if needed
	if (m_cv.lpszUserType == NULL)
	{
		// no user type in storge, get user type from class ID
		LPTSTR lpszUserType = NULL;
		LPOLESTR lpOleStr = NULL;
		if (OleRegGetUserType(m_cv.clsid, USERCLASSTYPE_FULL,
			&lpOleStr) == S_OK)
		{
			lpszUserType = TASKSTRINGOLE2T(lpOleStr);
		}
		else
		{
			lpszUserType = (LPTSTR)CoTaskMemAlloc(256 * sizeof(TCHAR));
			if (lpszUserType != NULL)
			{
				lpszUserType[0] = '?';
				lpszUserType[1] = 0;
				VERIFY(AfxLoadString(AFX_IDS_UNKNOWNTYPE, lpszUserType) != 0);
			}
		}
		m_cv.lpszUserType = lpszUserType;
	}
	m_cv.hMetaPict = pItem->GetIconicMetafile();
}