DROPEFFECT COleServerItem::DoDragDrop(LPCRECT lpItemRect, CPoint ptOffset,
	BOOL bIncludeLink, DWORD dwEffects, LPCRECT lpRectStartDrag)
{
	ASSERT(AfxIsValidAddress(lpItemRect, sizeof(RECT)));
	ASSERT_VALID(this);

	ASSERT_VALID(this);

	DROPEFFECT dropEffect = DROPEFFECT_NONE;
	COleDataSource *pDataSource = NULL;
	TRY
	{
		// get clipboard data for this item
		CSize sizeItem(
			lpItemRect->right - lpItemRect->left,
			lpItemRect->bottom - lpItemRect->top);
		pDataSource = OnGetClipboardData(bIncludeLink, &ptOffset, &sizeItem);

		// add DROPEFFECT_LINK if link source is available
		LPDATAOBJECT lpDataObject = (LPDATAOBJECT)
			pDataSource->GetInterface(&IID_IDataObject);
		ASSERT(lpDataObject != NULL);
		FORMATETC formatEtc;
		formatEtc.cfFormat = (CLIPFORMAT)_oleData.cfLinkSource;
		formatEtc.ptd = NULL;
		formatEtc.dwAspect = DVASPECT_CONTENT;
		formatEtc.lindex = -1;
		formatEtc.tymed = (TYMED)-1;
		if (lpDataObject->QueryGetData(&formatEtc) == S_OK)
			dwEffects |= DROPEFFECT_LINK;

		// calculate default sensitivity rectangle
		CRect rectDrag;
		if (lpRectStartDrag == NULL)
		{
			rectDrag.SetRect(lpItemRect->left, lpItemRect->top, lpItemRect->left,
				lpItemRect->top);
			lpRectStartDrag = &rectDrag;
		}

		// do drag drop operation
		dropEffect = pDataSource->DoDragDrop(dwEffects, lpRectStartDrag);
		pDataSource->InternalRelease();
	}
	CATCH_ALL(e)
	{
		if (pDataSource != NULL)
			pDataSource->InternalRelease();

		THROW_LAST();
	}
	END_CATCH_ALL

	return dropEffect;
}