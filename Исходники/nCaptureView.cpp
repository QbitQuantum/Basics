void CNCaptureView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pImage)
	{
		CRect rcDrawTarget = m_rcDrawTarget;
		rcDrawTarget.OffsetRect(-rcDrawTarget.TopLeft());
		CPoint ptLogical = point;
		ClientToDoc(&ptLogical);
		if (rcDrawTarget.PtInRect(ptLogical))
		{
			CDrawCanvas<CNCaptureView>::OnLButtonDown(nFlags, point);
			_SetSelectRectClipInfo(point);
		}
	}
	SetMsgHandled(FALSE);
}