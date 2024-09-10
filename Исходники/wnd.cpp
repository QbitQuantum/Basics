bool CWnd::IsVisible()
{
	CWnd* pWnd = this;
	while ( pWnd->m_dwFlags & WsVisible )
	{
		pWnd = pWnd->GetParent();
		if ( !pWnd )
			return true;
	}
	return false;
}