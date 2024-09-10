void OwnerDrawBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC); 
	
	CRect rt;
	rt = lpDrawItemStruct->rcItem; //Get button rect

	UINT state = lpDrawItemStruct->itemState; //Get state of the button
	if ( (state & ODS_SELECTED) ) // If it is pressed
	{
		dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT); // Draw a sunken face
	}
	else
	{
		dc.DrawEdge(rt,EDGE_RAISED,BF_RECT); // Draw a raised face
	}

	CString strTemp;
	GetWindowText(strTemp);
	// Get the caption which have been set
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(strTemp,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 

}