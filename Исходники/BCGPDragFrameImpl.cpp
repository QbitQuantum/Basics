//--------------------------------------------------------------------------------------//
void CBCGPDragFrameImpl::EndDrawDragFrame (BOOL bClearInternalRects)
{
	if (m_pDockManager == NULL)
	{
		return;
	}

    BOOL bSDockingIsOn = FALSE;
    CBCGPSmartDockingManager* pSDManager = NULL;

    if ((pSDManager = m_pDockManager->GetSDManagerPermanent()) != NULL
        && pSDManager->IsStarted())
    {
        bSDockingIsOn = TRUE;
        pSDManager->HidePlace ();
    }

	CRect rectEmpty; rectEmpty.SetRectEmpty ();
	CRect rectDocked = m_rectExpectedDocked.IsRectEmpty () ? m_rectDrag : 
															 m_rectExpectedDocked;

	// do not draw the final frame (meaning - clear) if it was not drawn because of tab
	if (m_nInsertedTabID == -1)
	{
        if (!bSDockingIsOn)
        {
		    DrawDragFrame (rectEmpty, rectDocked, 0, m_nOldThikness);
        }
	}
	else
	{
		m_bDockToTab = TRUE;
	}
	
	if (bClearInternalRects)
	{
        RemoveTabPreDocking ();

		m_rectExpectedDocked.SetRectEmpty ();
		m_rectDrag.SetRectEmpty ();

		m_pFinalTargetBar = m_pTargetBar;
		m_pTargetBar = NULL;
	}

	m_bDragStarted = FALSE;
	
	ASSERT (m_pDockManager != NULL);
	if (!bSDockingIsOn)
	{
		m_pDockManager->LockUpdate (FALSE);
	}
}