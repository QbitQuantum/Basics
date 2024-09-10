STDMETHODIMP COlePropertiesDialog::XOleUIObjInfo::GetConvertInfo(
	DWORD dwObject, CLSID* lpClassID, WORD* lpwFormat,
	CLSID*, LPCLSID*, UINT*)
{
	COleClientItem* pItem = (COleClientItem*)dwObject;
	ASSERT_VALID(pItem);

	if (lpClassID != NULL)
	{
		if (pItem->GetType() == OT_LINK ||
			S_OK != ReadClassStg(pItem->m_lpStorage, lpClassID))
		{
			pItem->GetClassID(lpClassID);
		}
	}
	if (lpwFormat != NULL)
	{
		*lpwFormat = 0;
		CLIPFORMAT cf;
		if (ReadFmtUserTypeStg(pItem->m_lpStorage, &cf, NULL) == S_OK)
			*lpwFormat = (WORD)cf;
	}

	// Note: leave rest at default

	return S_OK;
}