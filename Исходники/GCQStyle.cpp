//****************************************************************************************
void CGCQStyle::OnFillBarBackground  (CDC* pDC, CControlBar* pBar,
										CRect rectClient, CRect rectClip,
										BOOL bNCArea)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pBar);

	if (!bNCArea)
	{
		CRgn rgn;
		rgn.CreateRectRgnIndirect (&rectClient);

		pDC->SelectClipRgn (&rgn);
	}

	CBCGDrawManager dm (*pDC);

	CRect rectFill = rectClient;

	if (!pBar->IsFloating () &&
		!pBar->IsKindOf (RUNTIME_CLASS (CBCGPopupMenuBar)))
	{
		CRect rectMainFrame;
		pBar->GetTopLevelFrame ()->GetWindowRect (rectMainFrame);

		pBar->ScreenToClient (&rectMainFrame);
		rectFill = rectMainFrame;

		if (bNCArea)
		{
			CRect rectWindow;
			pBar->GetWindowRect (rectWindow);

			pBar->ScreenToClient (rectWindow);

			CRect rectClientActual;
			pBar->GetClientRect (rectClientActual);

			rectFill.left += rectClientActual.left - rectWindow.left;
			rectFill.top += rectClientActual.top - rectWindow.top;
			rectFill.right += 10;
		}
	}

	dm.FillGradient (rectFill, CGCQLApp::sm_BackgroundColor1, CGCQLApp::sm_BackgroundColor2, FALSE);

	if (!bNCArea)
	{
		pDC->SelectClipRgn (NULL);
	}

	//pDC->SetTextColor( RGB(255,255,255) );
}