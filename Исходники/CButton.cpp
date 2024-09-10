void CCButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	RECT rect;
	dc.Attach(lpDrawItemStruct->hDC);
	rect=lpDrawItemStruct->rcItem;
	dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0)); 
    dc.FillSolidRect(&rect,color);//Here you can define the required color to appear on the Button.
    UINT state=lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 
    if((state & ODS_SELECTED))
	{
		dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
	}
	else
	{
		dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
	}

	dc.SetBkColor(color);   //Setting the Text Background color
	dc.SetTextColor(RGB(255,0,0));     //Setting the Text Color

	dc.Detach();  // Detach the Button DC        
	//AfxMessageBox("called");
	// TODO:  Add your code to draw the specified item
}