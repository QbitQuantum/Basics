void CMFECToolTip::ShowToolTip( CPoint& point )
{	
#if 1
	CWnd* pWnd = m_pParentWnd->ChildWindowFromPoint(point);
	if( pWnd )
	{
		UINT	nControlID = (UINT)pWnd->GetDlgCtrlID();
		if( m_currentControlID != nControlID && pWnd->IsWindowVisible())
		{
			ErasePreviousToolTipDisplay(m_currentControlID);
			ShowToolTip( nControlID );
		}
	}
#endif
}