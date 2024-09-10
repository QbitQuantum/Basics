CString CToolbarHelper::GetTip(UINT nID, LPPOINT pPoint) const
{
	if (!nID)
		return ""; // separator

	// are we over the dropbutton?
	BOOL bOverDropBtn = FALSE;

	if (pPoint)
	{
		CSize sizeBtn(m_pToolbar->GetToolBarCtrl().GetButtonSize());
		CRect rButton;

		m_pToolbar->GetToolBarCtrl().GetRect(nID, rButton);
		rButton.left += sizeBtn.cx;

		if (rButton.PtInRect(*pPoint))
			bOverDropBtn = TRUE;
	}

	CString sTip;

	// do we have a mapping for this
	THButton dm = { 0 };
				
	if (m_mapTHButtons.Lookup(nID, dm))
	{
		if (!bOverDropBtn)
		{
			// try the default item first
			if (dm.nDefCmdID && IsCmdEnabled(dm.nDefCmdID)/* && (dm.nDefCmdID != nID)*/)
			{
				sTip = GetTip(dm.nDefCmdID);

				if (!sTip.IsEmpty())
					return sTip;
			}
		}

		// try override tip
		if (lstrlen(dm.szTip))
			return dm.szTip;
	}

	return GetTip(nID);
}