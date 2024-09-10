void CKofDlgImpl::UpdateCaptionButtons()
{
	if ((m_Dlg.GetStyle () & WS_SYSMENU) == 0)
	{
		return;
	}

	CMenu* pSysMenu = m_Dlg.GetSystemMenu (FALSE);

	if (pSysMenu == NULL || !::IsMenu (pSysMenu->m_hMenu))
	{
		return;
	}

	for (POSITION pos = m_lstCaptionSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CMFCCaptionButtonEx* pButton = (CMFCCaptionButtonEx*)m_lstCaptionSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (pButton->GetHit () == AFX_HTCLOSE)
		{
			BOOL bGrayed = pSysMenu->GetMenuState (SC_CLOSE, MF_BYCOMMAND) & MF_GRAYED;
			pButton->m_bEnabled = bGrayed ? FALSE : TRUE;
		}

		if (pButton->GetHit () == AFX_HTMAXBUTTON)
		{
			BOOL bGrayed = pSysMenu->GetMenuState (SC_MAXIMIZE, MF_BYCOMMAND) & MF_GRAYED;
			pButton->m_bEnabled = bGrayed ? FALSE : TRUE;
		}

		if (pButton->GetHit () == AFX_HTMINBUTTON)
		{
			BOOL bGrayed = pSysMenu->GetMenuState (SC_MINIMIZE, MF_BYCOMMAND) & MF_GRAYED;
			pButton->m_bEnabled = bGrayed ? FALSE : TRUE;
		}
	}


	m_Dlg.RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
}