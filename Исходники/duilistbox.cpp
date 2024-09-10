BOOL CDUIListBox::SetTopIndex(INT nIndex)
{
	IDUIControl* pControl = GetControlByIndex(nIndex);
	if(pControl == NULL
		|| !(pControl->IsVisible()))
	{
		DUI_ASSERT(FALSE);
		return FALSE;
	}

	IDUIScrollBar* pSB = GetVerticalSB();
	if(pSB == NULL 
		|| !(pSB->IsVisible()))
	{
		return FALSE;
	}

	INT nTempY(0);
	INT nCount = m_arChildControl.size();
	for(INT i=0; i<nIndex; ++i)
	{
		if(m_arChildControl[i]->IsVisible())
		{
			nTempY += m_arChildControl[i]->GetFixedSize().cy;
		}
	}	

	SCROLLINFO si = {0};
	pSB->GetScrollBarInfo(&si);
	si.nPos = nTempY;
	si.fMask = SIF_POS;
	pSB->SetScrollBarInfo(&si);

	UpdateLayout(TRUE);

	return TRUE;
}