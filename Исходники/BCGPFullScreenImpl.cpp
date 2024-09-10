//*************************************************************************************
void CBCGPFullScreenImpl::RestoreState(CFrameWnd* pFrame) 
{
	ASSERT (m_uiFullScreenID != -1);

	if (m_uiFullScreenID == -1)
	{
		return;
	}

	// Destroy the toolbar
	CWnd*	pWnd	= m_pwndFullScreenBar->GetParentMiniFrame ();
	if (pWnd == NULL)
		pWnd	= m_pwndFullScreenBar;
	VERIFY (pWnd->DestroyWindow());

	delete m_pwndFullScreenBar; 
		
	m_pwndFullScreenBar = NULL;
	m_bFullScreen = FALSE;

	CBCGPMDIFrameWnd* pbcgMDIFrame = DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, pFrame);
		
	//Restore window pos
	pFrame->SetWindowPos (NULL, m_rectFramePrev.left, m_rectFramePrev.top,
		m_rectFramePrev.Width (), m_rectFramePrev.Height (), SWP_NOZORDER);

	//restore layout
	pFrame->SetRedraw (FALSE);

	g_pWorkspace->m_bLoadUserToolbars = FALSE;

	if (pbcgMDIFrame != NULL)
	{
		g_pWorkspace->LoadState (pbcgMDIFrame, m_strRegSection);
	}
	else
	{
		CBCGPFrameWnd* pbcgFrame = DYNAMIC_DOWNCAST (CBCGPFrameWnd, pFrame);
		if (pbcgFrame != NULL)
		{
			g_pWorkspace->LoadState (pbcgFrame, m_strRegSection);
		}
	}

	pFrame->SetRedraw (TRUE);
	pFrame->RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | 
								RDW_ERASE | RDW_ALLCHILDREN);

	if (!m_bShowMenu && m_bMenuBarWasVisible)
	{
		if (pbcgMDIFrame != NULL)
		{
			const CBCGPMenuBar* pMenuBar = pbcgMDIFrame->GetMenuBar ();

			if (pMenuBar != NULL)
			{
				pbcgMDIFrame->ShowControlBar ((CBCGPBaseControlBar*)pMenuBar, TRUE,FALSE, FALSE);
				if (pMenuBar->IsFloating ())
				{
					pbcgMDIFrame->SetFocus ();
				}
			}
		}
		else
		{
			CBCGPFrameWnd* pbcgFrame = DYNAMIC_DOWNCAST (CBCGPFrameWnd, pFrame);
			if (pbcgFrame != NULL)
			{
				const CBCGPMenuBar* pMenuBar = pbcgFrame->GetMenuBar ();
				if (pMenuBar != NULL)
				{
					pbcgFrame->ShowControlBar ((CBCGPBaseControlBar*)pMenuBar, TRUE,FALSE, FALSE);
					if (pMenuBar->IsFloating ())
					{
						pbcgFrame->SetFocus ();
					}
				}
			}
		}	
	}

	if (m_pImpl != NULL)
	{
		CBCGPMenuBar* pMenuBar = m_pImpl->GetMenuBar();
		if (pMenuBar != NULL && pMenuBar->IsPopupMode())
		{
			pMenuBar->ShowControlBar (FALSE, FALSE, FALSE);
		}
	}

	if (pbcgMDIFrame != NULL && pbcgMDIFrame->IsMDITabbedGroup ())
	{
		pbcgMDIFrame->AdjustClientArea ();
	}

	BOOL bDontCallChangeVM = FALSE;

#ifndef BCGP_EXCLUDE_RIBBON
	if (m_pImpl != NULL && 
		m_pImpl->m_pRibbonBar->GetSafeHwnd () != NULL)
	{
		if (m_pImpl->m_pRibbonBar->IsWindowVisible () &&
			m_pImpl->m_pRibbonBar->IsReplaceFrameCaption ())
		{
			m_pImpl->OnChangeVisualManager ();
			m_pImpl->m_pRibbonBar->DWMCompositionChanged ();
			
			bDontCallChangeVM = TRUE;
		}

		if (!m_pImpl->m_pRibbonBar->IsWindowVisible () &&
			pFrame->IsZoomed())
		{
			pFrame->SetWindowPos(NULL, -1, -1, -1, -1, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	}
#endif

	if (m_pImpl != NULL && !bDontCallChangeVM)
	{
		m_pImpl->OnChangeVisualManager ();
	}
}