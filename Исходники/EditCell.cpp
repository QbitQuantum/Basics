void 
CEditCell::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    BOOL Shift = GetKeyState(VK_SHIFT) < 0;
    switch (nChar)
    {
		case VK_ESCAPE :
		{
			if (Shift)
				// Shift+Escape -> disable autocomplete
				m_DoSuggest = FALSE;
			else {
				m_bEscape = TRUE;
				GetParent()->SetFocus();
			}
			return;
		}
		case VK_RETURN :
		{
			SetListText();
			if (m_SubItem == 0)
				m_pListCtrl->EditSubItem (m_Item, 1);
			else
				m_pListCtrl->EditSubItem (m_Item + 1, 0);
			return;
		}
		case VK_TAB :
		{
			if (Shift)
			{
				if (m_SubItem > 0)
					m_pListCtrl->EditSubItem (m_Item, m_SubItem - 1);
				else
				{
					if (m_Item > 0)
						m_pListCtrl->EditSubItem (m_Item - 1, 2);
				}
			}
			else
			{
				if (m_SubItem == 0)
					m_pListCtrl->EditSubItem (m_Item, 1);
				else if (m_SubItem < 2)
					m_pListCtrl->EditSubItem (m_Item, m_SubItem + 1);				
				else
					m_pListCtrl->EditSubItem (m_Item + 1, 0);
			}
			return;
		}
    }

    CEdit::OnChar (nChar, nRepCnt, nFlags);

    // Get text
    CString Text;
    GetWindowText(Text);

	// Make some suggestion
	if (m_DoSuggest && nChar != 8 && m_AutoComplete != NULL) {
		int iSelStart;
		int iSelEnd;
		GetSel(iSelStart, iSelEnd);
		CString sugg = GetSuggestion(Text);
		if (!sugg.IsEmpty()) {
			Text = sugg;
			SetWindowText(Text);
			SetSel(iSelStart, Text.GetLength());
		}
	}

    // Resize edit control if needed

    CWindowDC DC (this);
    CFont *pFont = GetParent()->GetFont();
    CFont *pFontDC = DC.SelectObject (pFont);
    CSize Size = DC.GetTextExtent (Text);
    DC.SelectObject (pFontDC);
    Size.cx += 5;			   	// add some extra buffer

    // Get client rect
    CRect Rect, ParentRect;
    GetClientRect (&Rect);
    GetParent()->GetClientRect (&ParentRect);

    // Transform rect to parent coordinates
    ClientToScreen (&Rect);
    GetParent()->ScreenToClient (&Rect);

    // Check whether control needs to be resized and whether there is space to grow
    if (Size.cx > Rect.Width())
    {
		if (Size.cx + Rect.left < ParentRect.right )
			Rect.right = Rect.left + Size.cx;
		else
			Rect.right = ParentRect.right;
		MoveWindow (&Rect);
    }
}