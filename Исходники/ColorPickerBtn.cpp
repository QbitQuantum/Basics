LRESULT CColorPickerBtn::OnClicked (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled) 
{
	//
	// Mark button as active and invalidate button to force a redraw
	//
	m_fPopupActive = TRUE;
	InvalidateRect (NULL);

	//
	// Get the parent window
	//

	HWND hWndParent = GetParent ();

	//
	// Send the drop down notification to the parent
	//

	SendNotification (CPN_DROPDOWN, m_clrCurrent, TRUE); 

	//
	// Save the current color for future reference
	//

    COLORREF clrOldColor = m_clrCurrent;

	//
	// Display the popup
	//

	BOOL fOked = Picker (true);

	//
	// Cancel the popup
	//

	m_fPopupActive = FALSE;

	//
	// If the popup was canceled without a selection
	//

	if (!fOked)
	{

		//
		// If we are tracking, restore the old selection
		//

		if (m_fTrackSelection)
		{
			if (clrOldColor != m_clrCurrent)
			{
				m_clrCurrent = clrOldColor;
				SendNotification (CPN_SELCHANGE, m_clrCurrent, TRUE); 
			}
		}
		SendNotification (CPN_CLOSEUP, m_clrCurrent, TRUE); 
		SendNotification (CPN_SELENDCANCEL, m_clrCurrent, TRUE); 
	}
	else
	{
		bSetInvisible = false;
		if (clrOldColor != m_clrCurrent)
		{
			SendNotification (CPN_SELCHANGE, m_clrCurrent, TRUE); 
		}
		SendNotification (CPN_CLOSEUP, m_clrCurrent, TRUE); 
		SendNotification (CPN_SELENDOK, m_clrCurrent, TRUE); 
	}

	//
	// Invalidate button to force repaint
	//

	InvalidateRect (NULL);
	return TRUE;
}