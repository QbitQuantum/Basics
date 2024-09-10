void XYDrawbox::RefreshYPosScrollBar()
{
	scrollinfo.fMask = SIF_POS;
	scrollinfo.nPos = this->posYScroll;
	SetScrollInfo(this->hwndThis, SB_VERT, &scrollinfo, TRUE);
	GetScrollInfo(this->hwndThis, SB_VERT, &scrollinfo);
	this->posYScroll = scrollinfo.nPos;
}