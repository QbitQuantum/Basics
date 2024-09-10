//-------------------------------------------------------------------------------//
void CBCGPAutoHideToolBar::DoPaint(CDC* pDC)
{
	ASSERT_VALID (pDC);

	CBCGPMemDC memDC (*pDC, this);
	
	CBCGPControlBar::DoPaint (&memDC.GetDC ());

	CBCGPAutoHideButton* pBtnTop = NULL;
	
	for (POSITION pos = m_lstAutoHideButtons.GetHeadPosition (); pos != NULL;)
	{
		CBCGPAutoHideButton* pBtn = (CBCGPAutoHideButton*) m_lstAutoHideButtons.GetNext (pos);
		ASSERT_VALID (pBtn);
		if (pBtn->IsTop ())
		{
			pBtnTop = pBtn;
		}
		else if (pBtn->IsVisible ())
		{
			pBtn->OnDraw (&memDC.GetDC ());
		}
	}

	if (pBtnTop != NULL && pBtnTop->IsVisible ())
	{
		pBtnTop->OnDraw (&memDC.GetDC ());
	}
}