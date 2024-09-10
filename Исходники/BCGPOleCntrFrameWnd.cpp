//*************************************************************************************
void CBCGPOleCntrFrameWnd::RecalcLayout (BOOL bNotify)
{
	AdjustClientArea();
	m_dockManager.AdjustDockingLayout ();
	m_dockManager.RecalcLayout (bNotify);

	CView* pView = GetActiveView ();
	if (pView != NULL && pView->IsKindOf (RUNTIME_CLASS (CBCGPPrintPreviewView)) && 
		m_dockManager.IsPrintPreviewValid ())
	{
		CRect rectClient = m_dockManager.GetClientAreaBounds ();
		pView->SetWindowPos (NULL, rectClient.left, rectClient.top, 
								rectClient.Width (), rectClient.Height (),
								SWP_NOZORDER  | SWP_NOACTIVATE);
	}

	m_pInPlaceFrame->RecalcLayout (bNotify);
}