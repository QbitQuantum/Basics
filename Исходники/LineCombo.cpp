void CLineCombo::DrawItem(LPDRAWITEMSTRUCT lpMIS) 
{
	CDC *pDC = CDC::FromHandle(lpMIS->hDC);
	RECT *pRect = &lpMIS->rcItem;
	int H = pRect->bottom - pRect->top;
	int W = pRect->right - pRect->left;

	CPoint pt1,pt2;
	pt1.x = 4;
	pt1.y = pRect->top + H/2;
	pt2.x = W-4;
	pt2.y = pRect->top + H/2;

/*	CPen pen;
	if (!pen.CreatePen(PS_DASHDOT, 1, RGB(0,0,0)))
		return;
	CPen* pOldPen=pDC->SelectObject(&pen);*/

	int i=lpMIS->itemID;
	CADLType* pLType=(CADLType*)m_pGraphics->m_LTypes.GetAt(i);
//	return;
	CreatePenStyle(pDC,pLType);

	if (lpMIS->itemAction & ODA_DRAWENTIRE)
	{
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2); 
	}
	if ((lpMIS->itemState & ODS_SELECTED) &&
	(lpMIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush br(0x6A240A);
		pDC->FillRect(&lpMIS->rcItem,&br);
		pDC->DrawFocusRect(&lpMIS->rcItem);
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2); 
	}
	if (!(lpMIS->itemState & ODS_SELECTED) &&
		(lpMIS->itemAction & ODA_SELECT))
	{
		CBrush br(RGB(255,255,255));
		pDC->FillRect(&lpMIS->rcItem,&br);
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2); 
	}
}