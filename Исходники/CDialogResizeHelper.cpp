void CDialogResizeHelper::OnSize(UINT, CSize newSize)
{
	if (m_thisWnd != NULL) {
		HDWP hWinPosInfo = BeginDeferWindowPos( m_table.get_size() + (m_sizeGrip != NULL ? 1 : 0) );
		for(t_size n = 0; n < m_table.get_size(); ++n) {
			CRect rcOrig;
			const Param & e = m_table[n];
			CWindow wndItem = m_thisWnd.GetDlgItem(e.id);
			if (m_origRects.query(e.id, rcOrig) && wndItem != NULL) {
				int dest_x = rcOrig.left, dest_y = rcOrig.top, 
					dest_cx = rcOrig.Width(), dest_cy = rcOrig.Height();

				int delta_x = newSize.cx - m_rcOrigClient.right,
					delta_y = newSize.cy - m_rcOrigClient.bottom;

				dest_x += pfc::rint32( e.snapLeft * delta_x );
				dest_cx += pfc::rint32( (e.snapRight - e.snapLeft) * delta_x );
				dest_y += pfc::rint32( e.snapTop * delta_y );
				dest_cy += pfc::rint32( (e.snapBottom - e.snapTop) * delta_y );
				
				DeferWindowPos(hWinPosInfo, wndItem, 0,dest_x,dest_y,dest_cx,dest_cy,SWP_NOZORDER);
			}
		}
		if (m_sizeGrip != NULL)
		{
			RECT rc, rc_grip;
			if (m_thisWnd.GetClientRect(&rc) && m_sizeGrip.GetWindowRect(&rc_grip)) {
				DeferWindowPos(hWinPosInfo, m_sizeGrip, NULL, rc.right - (rc_grip.right - rc_grip.left), rc.bottom - (rc_grip.bottom - rc_grip.top), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
		}
		EndDeferWindowPos(hWinPosInfo);
	}
	SetMsgHandled(FALSE);
}