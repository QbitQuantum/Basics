void CGuiSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (bSelected==TRUE)
		return;
	CRect rc;
	GetClientRect(&rc);
	if (rc.PtInRect(point))
	{
		bSelected=TRUE;
		Invalidate();
		UpdateWindow();
		SetTimer(1,100,NULL);
	}
	CSliderCtrl::OnMouseMove(nFlags, point);
}