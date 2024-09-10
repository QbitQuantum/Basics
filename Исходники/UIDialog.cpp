void CUIDialog::_TogglePage(int page, BOOL bVisible)
{
	if(page < 0)
		return;

	POSITION p = m_groups.FindIndex(page);
	if(p != NULL)
	{
		__UIGroup *pGroup = m_groups.GetAt(p);
		ASSERT(pGroup != NULL);

		POSITION p1 = pGroup->m_items.GetHeadPosition();
		while(p1)
		{
			CWnd *pItem = pGroup->m_items.GetNext(p1);
			ASSERT(pItem != NULL);
			if(bVisible)
				pItem->ShowWindow(SW_SHOW);
			else
				pItem->ShowWindow(SW_HIDE);
		}

		if(pGroup->m_pFirst)
			pGroup->m_pFirst->SetFocus();
	}
}