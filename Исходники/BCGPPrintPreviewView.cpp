//******************************************************************************
void CBCGPPrintPreviewView::SetToolbarSize ()
{
	if (m_wndToolBar.GetSafeHwnd () == NULL)
	{
		return;
	}

	ASSERT_VALID (m_pToolBar);

	CSize szSize = m_wndToolBar.CalcFixedLayout (TRUE, TRUE);

	//----------------------------------------------------------------------
	// Print toolbar should occupy the whole width of the mainframe (Win9x):
	//----------------------------------------------------------------------
	CFrameWnd* pParent = BCGPGetParentFrame (this);
	ASSERT_VALID (pParent);

	CRect rectParent;
	pParent->GetClientRect (rectParent);
	szSize.cx = rectParent.Width ();

	CRect rectToolBar;
	m_wndToolBar.GetWindowRect (rectToolBar);
	pParent->ScreenToClient (rectToolBar);

	m_pToolBar->SetWindowPos (NULL, rectToolBar.left, rectToolBar.top, szSize.cx, szSize.cy, 
				SWP_NOACTIVATE|SWP_SHOWWINDOW|SWP_NOZORDER);

	m_wndToolBar.SetWindowPos (NULL, 0, 0, szSize.cx, szSize.cy, 
				SWP_NOACTIVATE|SWP_SHOWWINDOW|SWP_NOZORDER);

	//----------------------------------------------------
	// Adjust parent toolbar (actually - dialog bar) size:
	//----------------------------------------------------
	m_pToolBar->m_sizeDefault.cy = szSize.cy;

	if (m_recentToolbarSize == szSize)
	{
		return;
	}

	m_recentToolbarSize = szSize;
	
	pParent->RecalcLayout();            // position and size everything
	pParent->UpdateWindow();
}