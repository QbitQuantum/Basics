/*============================================================================*/
	void CustomButton::
DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)               		/*

	Custom draw the item specified in lpDrawItemStruct: here a button.
	Invoked by the view for the owner-drawn button in response to the
	WM_DRAWITEM system message. An owner-drawn button has the BS_OWNERDRAW
	style set. Also see the BS_ style values.
	
	Note: this procedure can show the focus rectangle of the button when the
	button has focus. Howeever, the focus does not appear to be cancelled
	when another control recieves the focus, and the non-owner-draw form
	of push buttons does not have this rectangle present when pressed
*-----------------------------------------------------------------------------*/
{
	  // get the device context and attach the button handle to it
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC); 
	  // determine the button rectangle
	CRect rect = lpDrawItemStruct->rcItem;
	  // draw in the button text
	dc.DrawText(GetWindowText(), -1, rect, DT_CENTER | DT_VCENTER |
	    DT_SINGLELINE);
	  // get the current state of the button
	UINT state = lpDrawItemStruct->itemState;
	if ( (state & ODS_SELECTED) )	// if it is pressed
	{
		dc.DrawEdge(rect, EDGE_SUNKEN, BF_RECT); // draw a sunken face
	}
	else
	{
		dc.DrawEdge(rect, EDGE_RAISED, BF_RECT); // draw a raised face
	}
	  // draw the focus rectangle, a dotted rectangle just inside the
	  // button rectangle when the button has the focus.
	if (lpDrawItemStruct->itemAction & ODA_FOCUS)
	{
		int iChange = 3;
		rect.top    += iChange;
		rect.left   += iChange;
		rect.right  -= iChange;
		rect.bottom -= iChange;
		dc.DrawFocusRect(rect);
	}
	dc.Detach();
}