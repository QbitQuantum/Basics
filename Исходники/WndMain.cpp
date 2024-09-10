void CMainWnd::OnNetworkDisconnect()
{
	CChildWnd* pChild = GetWindow( RUNTIME_CLASS(CPagerWnd) );
	if ( pChild ) pChild->DestroyWindow();
	
	pChild = GetWindow( RUNTIME_CLASS(CMailWnd) );
	if ( pChild ) pChild->DestroyWindow();
	
	pChild = GetWindow( RUNTIME_CLASS(CClerkWnd) );
	if ( pChild ) pChild->DestroyWindow();
	
	pChild = GetWindow( RUNTIME_CLASS(CNetworkWnd) );
	if ( pChild ) ((CNetworkWnd*)pChild)->Disconnect();
}