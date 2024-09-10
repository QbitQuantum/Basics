// **************************************************************************
// OnChar ()
//
// Description:
//	Handle keyboard input.  Switch view on tab, etc.
//
// Parameters:
//  UINT		nChar		Character code
//	UINT		nRepCnt		repeat count
//	UINT		nFlags		Flags
//
// Returns:
//  void
// **************************************************************************
void CKListEdit::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) 
	{
	// Filter escape and return:
	if (nChar == VK_ESCAPE || nChar == VK_RETURN)	
		{		
		if (nChar == VK_ESCAPE)
			m_bESC = TRUE;		
		
		GetParent ()->SetFocus ();		
		return;	
		}

	// Perform default processing:
	CEdit::OnChar (nChar, nRepCnt, nFlags);	

	// Get text extent:
	CString strText;
	GetWindowText (strText);	

	CWindowDC dc (this);
	CFont *pFont = GetParent ()->GetFont ();
	CFont *pFontDC = dc.SelectObject (pFont);
	CSize size = dc.GetTextExtent (strText);	
	dc.SelectObject (pFontDC);

	// add some extra buffer	
	size.cx += 5;
	
	// Get client rectangle:
	CRect rect; 
	CRect parentrect;	

	GetClientRect (&rect);
	GetParent ()->GetClientRect (&parentrect);

	// Transform rectangle to parent coordinates:
	ClientToScreen (&rect);
	GetParent ()->ScreenToClient (&rect);

	// Check whether control needs to be resized and whether there is space to grow:	
	if (size.cx > rect.Width ())	
		{
		if (size.cx + rect.left < parentrect.right)
			rect.right = rect.left + size.cx;		
		else			
			rect.right = parentrect.right;

		MoveWindow (&rect);	
		}

	// Send notification to parent of the list control that edit was made:
	GetParent ()->GetParent ()->SendMessage (UM_LISTEDIT_ITEMCHANGE, m_iSubItem, m_iItem);
	}