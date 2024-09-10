CXTPDockingPaneCaptionButton* CXTPDockingPaneTabbedContainer::HitTestCaptionButton(CPoint point) const
{
	if (IsTitleVisible())
	{
		for (int i = 0; i < m_pCaptionButtons->GetSize(); i++)
		{
			CXTPDockingPaneCaptionButton* pButton = m_pCaptionButtons->GetAt(i);
			if (pButton->PtInRect(point))
				return pButton->IsEnabled() ? pButton : NULL;
		}
	}

	return NULL;
}