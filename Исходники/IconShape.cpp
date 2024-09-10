void MutIconShapeClass<T>::OnDraw (wxDC & dc) 
{
	wxRect size = this->GetRect();
#if __WXMSW__
	if (wxWindow::FindFocus() == this) {
		// MSW doesn't allow to change the border
		for (int i = 0 ; i < maxBorderSize.x - 1 ; i++) {
			dc.DrawLine(i,i,size.width-i,i);
			dc.DrawLine(i,size.height-i,size.width-i,size.height-i);
		}
		for (int i = 0 ; i < maxBorderSize.y - 1 ; i++) {
			dc.DrawLine(size.width-i,i,size.width-i,size.height-i);
			dc.DrawLine(i,i,i,size.height-i);
		}
	}
#endif 

	DEBUGLOG (other, _T("Checking icon"));

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG (other, _T("Checking icon again"));

	}
	DEBUGLOG (other, _T("Icon ok."));

	int y = borderOffset.y;
	wxPoint center(size.width/2,y + GetIcon().GetHeight()/2);

	for (mutpointlist::iterator i = usedperimeterpoints.begin();
	     i != usedperimeterpoints.end();++i) {
		DrawPerimeterPoint(dc,center, *i);
	}

	if (GetIcon().IsOk()) {
		int x = 0;
		DEBUGLOG (other, _T("Size: %dx%d"),GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
#if __WXMAC__ || __WXGTK__
		x -= maxBorderSize.x - borderOffset.x;
#endif
		dc.DrawIcon(GetIcon(), x, y);
	}

	DEBUGLOG (other, _T("Focus %p and this %p"),(void*)this->FindFocus(),(void*)this);
/*  Draw a black bock around focused item 
	if (FindFocus() == this) {
		DEBUGLOG (other, _T("Painting Box"));
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(0,0,size.width,size.height);
	}
*/
}