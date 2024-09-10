BOOL CCrystalEditView::DoDropText(COleDataObject *pDataObject, const CPoint &ptClient)
{
	HGLOBAL hData = pDataObject->GetGlobalData(CF_TEXT);
	if (hData == NULL)
		return FALSE;

	CPoint ptDropPos = ClientToText(ptClient);
	if (IsDraggingText() && IsInsideSelection(ptDropPos))
	{
		SetAnchor(ptDropPos);
		SetSelection(ptDropPos, ptDropPos);
		SetCursorPos(ptDropPos);
		EnsureVisible(ptDropPos);
		return FALSE;
	}

	LPSTR pszText = (LPSTR) ::GlobalLock(hData);
	if (pszText == NULL)
		return FALSE;

	int x, y;
	USES_CONVERSION;
	m_pTextBuffer->InsertText(this, ptDropPos.y, ptDropPos.x, A2T(pszText), y, x, CE_ACTION_DRAGDROP); //	[JRT]
	CPoint ptCurPos(x, y);
	ASSERT_VALIDTEXTPOS(ptCurPos);
	SetAnchor(ptDropPos);
	SetSelection(ptDropPos, ptCurPos);
	SetCursorPos(ptCurPos);
	EnsureVisible(ptCurPos);

	::GlobalUnlock(hData);
	return TRUE;
}