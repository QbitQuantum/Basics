void CFrameAnimation::InvertHollowRect(CDC &dc,
	int iX1,int iY1,int iX2,int iY2)
{
	CRect rect;

	rect.SetRect(iX1,iY1,iX2,iY1+1);
	dc.InvertRect(&rect);

	rect.SetRect(iX1,iY2-1,iX2,iY2);
	dc.InvertRect(&rect);

	rect.SetRect(iX1,iY1,iX1+1,iY2);
	dc.InvertRect(&rect);

	rect.SetRect(iX2-1,iY1,iX2,iY2);
	dc.InvertRect(&rect);
}