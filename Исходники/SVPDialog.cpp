void CSVPDialog::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r,cr;

	{ //New UI
		CRect rc;
		GetWindowRect(&rc);
		rc-=rc.TopLeft();



		// destroy old region
		if((HRGN)m_rgn)
		{
			m_rgn.DeleteObject();
		}

		m_rgn.CreateRoundRectRgn(0,0,rc.Width()-1,rc.Height()-1, 3,3);                 // rounded rect w/50 pixel corners

		m_rgnBorder.CreateRoundRectRgn(1,1,rc.Width()-2,rc.Height()-2, 3,3);            

		SetWindowRgn(m_rgn,TRUE);

		m_btnClose.MoveWindow( rc.right-16,rc.top+3, 12, 12);
	}

	
}