void CTrayMenuBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rClient;
	GetClientRect(rClient);

	if(point.x >= rClient.left && point.x <= rClient.right &&
		point.y >= rClient.top && point.y <= rClient.bottom)
	{
		SetCapture();

		if(!m_bNoHover)
			m_bMouseOver = true;
		Invalidate();
	}
	else
	{
		if(m_bParentCapture)
		{
			CWnd *pParent = GetParent();
			if(pParent)
				pParent->SetCapture();
			else
				ReleaseCapture();
		}
		else
			ReleaseCapture();

		m_bMouseOver = false;
		Invalidate();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}