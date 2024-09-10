// OnEndPrintPreview is here for swap tuning reasons
//  (see viewprev.cpp for complete preview mode implementation)
void CView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo,
			POINT, CPreviewView* pView)
{
	ASSERT_VALID(pDC);
	ASSERT_VALID(pView);

	if (pView->m_pPrintView != NULL)
		pView->m_pPrintView->OnEndPrinting(pDC, pInfo);

	CFrameWnd* pParent = (CFrameWnd*)AfxGetThread()->m_pMainWnd;
	ASSERT_VALID(pParent);
	ASSERT(pParent->IsKindOf(RUNTIME_CLASS(CFrameWnd)));

	// restore the old main window
	pParent->OnSetPreviewMode(FALSE, pView->m_pPreviewState);

	// Force active view back to old one
	pParent->SetActiveView(pView->m_pPreviewState->pViewActiveOld);
	if (pParent != GetParentFrame())
		OnActivateView(TRUE, this, this);   // re-activate view in real frame
	pView->DestroyWindow();     // destroy preview view
			// C++ object will be deleted in PostNcDestroy

	// restore main frame layout and idle message
	pParent->RecalcLayout();
	pParent->SendMessage(WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE, 0L);
	pParent->UpdateWindow();
}