void gxEditCell::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    BOOL Shift = GetKeyState (VK_SHIFT) < 0;
    switch (nChar)
    {
		case VK_ESCAPE :
		{
			if (nChar == VK_ESCAPE)
				bEscape = TRUE;
			GetParent()->SetFocus();
			return;
		}
		case VK_RETURN :
		{
			SetListText();
			pListCtrl->EditSubItem (Item + 1, 0);
			return;
		}
		case VK_TAB :
		{
	/*		if (Shift)
			{
				if (SubItem > 0)
					pListCtrl->EditSubItem (Item, SubItem - 1);
				else
				{
					if (Item > 0)
						pListCtrl->EditSubItem (Item - 1, 2);
				}
			}
			else
			{
				if (SubItem < 2)
					pListCtrl->EditSubItem (Item, SubItem + 1);
				else
					pListCtrl->EditSubItem (Item + 1, 0);
			}*/
			return;
		}
    }

    CEdit::OnChar (nChar, nRepCnt, nFlags);

    // Resize edit control if needed

    // Get text extent
    CString Text;

    GetWindowText (Text);
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