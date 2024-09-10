void CODMenu::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rect;
	UINT state = (((CODMenuData*)(lpDIS->itemData))->nFlags);
	if(state & MF_SEPARATOR){
		rect.CopyRect(&lpDIS->rcItem);
		rect.top+=rect.Height()>>1;
		pDC->DrawEdge(&rect,EDGE_ETCHED,BF_TOP);
	}