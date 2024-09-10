BOOL CRoundSliderCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	BOOL bResult = TRUE;

	ScreenToClient(&pt);

	if(ChildWindowFromPoint(pt) == this)
	{
		bResult = CSliderCtrl::OnMouseWheel(nFlags, zDelta, pt);
		RedrawWindow();
	}

	return bResult;
}