void WLTreeItemAL::OnLButtonDown(UINT /*nFlags*/, CPoint point) 
{
	SetFocus() ;
	m_bLButtonDown = TRUE ;
	HostToClient(&point) ;

	if (SendMessage(WM_CAN_YOU_DRAG, 0, 0))
	{
		if (GetCapture() != this)
			SetCapture() ;

		m_bPrepareDrag = TRUE ;
		m_dwPrepareDragTime = GetTickCount() ;
		m_ptPrepareDragPoint = point ;
	}
}