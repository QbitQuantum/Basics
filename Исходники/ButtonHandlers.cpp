void CloseButtonMouseMoveHandler()
{
	TRACKMOUSEEVENT tme; 
	tme.cbSize = sizeof(tme); 
	tme.dwFlags = TME_HOVER|TME_LEAVE; 
	tme.dwHoverTime = 1;
	tme.hwndTrack = hCloseButton;
	TrackMouseEvent(&tme); 
}