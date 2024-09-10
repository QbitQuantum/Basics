	virtual void OnClick (CPoint /*point*/)
	{
		CBCGPBaseRibbonElement* pElement = (CBCGPBaseRibbonElement*) m_dwData;
		ASSERT_VALID (pElement);

		pElement->SetVisible (!pElement->IsVisible ());
		Redraw ();

		CBCGPRibbonBar* pRibbonStatusBar = pElement->GetParentRibbonBar ();
		ASSERT_VALID (pRibbonStatusBar);

		pRibbonStatusBar->RecalcLayout ();
		pRibbonStatusBar->RedrawWindow ();

		CFrameWnd* pParentFrame = pRibbonStatusBar->GetParentFrame ();
		ASSERT_VALID (pParentFrame);

		pParentFrame->RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);

		CRect rectScreen;
		pRibbonStatusBar->GetWindowRect (&rectScreen);

		CBCGPPopupMenu::UpdateAllShadows (rectScreen);
	}