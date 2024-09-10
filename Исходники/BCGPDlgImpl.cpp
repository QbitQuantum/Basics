//*************************************************************************
void CBCGPDlgImpl::UpdateCaption ()
{
	if (!IsOwnerDrawCaption ())
	{
		return;
	}

	if (m_lstCaptionSysButtons.IsEmpty ())
	{
		//------------------------
		// Create caption buttons:
		//------------------------
		const DWORD dwStyle = m_Dlg.GetStyle ();
		HMENU hSysMenu = NULL;
		CMenu* pSysMenu = m_Dlg.GetSystemMenu (FALSE);

		if (pSysMenu != NULL && ::IsMenu (pSysMenu->m_hMenu))
		{
			hSysMenu = pSysMenu->GetSafeHmenu ();
			if (!::IsMenu (hSysMenu) || (m_Dlg.GetStyle () & WS_SYSMENU) == 0)
			{
				hSysMenu = NULL;
			}
		}

		if (hSysMenu != NULL)
		{
			m_lstCaptionSysButtons.AddTail (new CBCGPFrameCaptionButton (HTCLOSE_BCG));

			if ((dwStyle & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX)
			{
				m_lstCaptionSysButtons.AddTail (new CBCGPFrameCaptionButton (HTMAXBUTTON_BCG));
			}

			if ((dwStyle & WS_MINIMIZEBOX) == WS_MINIMIZEBOX)
			{
				m_lstCaptionSysButtons.AddTail (new CBCGPFrameCaptionButton (HTMINBUTTON_BCG));
			}

#ifndef _BCGSUITE_
			if ((dwStyle & DS_CONTEXTHELP) == DS_CONTEXTHELP)
			{
				if (!m_Dlg.IsKindOf (RUNTIME_CLASS (CPropertySheet)))
				{
					m_lstCaptionSysButtons.AddTail (new CBCGPFrameCaptionButton (HTHELPBUTTON_BCG));
				}
			}
#endif
		}
	}

	CRect rectCaption = GetCaptionRect ();

#ifndef _BCGSUITE_
    if (!visualManagerMFC->OnUpdateNcButtons(&m_Dlg, m_lstCaptionSysButtons, rectCaption))
#endif
    {
	    CSize sizeButton = visualManagerMFC->GetNcBtnSize (FALSE);
	    sizeButton.cy = min (sizeButton.cy, rectCaption.Height () - 2);

	    int x = rectCaption.right - sizeButton.cx;
	    int y = rectCaption.top + max (0, (rectCaption.Height () - sizeButton.cy) / 2);

	    for (POSITION pos = m_lstCaptionSysButtons.GetHeadPosition (); pos != NULL;)
	    {
		    CBCGPFrameCaptionButton* pButton = (CBCGPFrameCaptionButton*)
			    m_lstCaptionSysButtons.GetNext (pos);
		    ASSERT_VALID (pButton);

		    pButton->SetRect (CRect (CPoint (x, y), sizeButton));

		    x -= sizeButton.cx;
	    }
    }

#ifndef _BCGSUITE_
    m_Dlg.SendMessage (BCGM_ONAFTERUPDATECAPTION);
#endif

	m_Dlg.RedrawWindow (NULL, NULL,
		RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
}