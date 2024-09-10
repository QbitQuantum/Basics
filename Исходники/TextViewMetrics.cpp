HDC TextViewMetrics::ClientToText( HDC hdc, POINT* oldOrigin ) const
{
	POINT clientOrigin = { 0, 0 };
	clientOrigin = ClientToText( clientOrigin );

	GetWindowOrgEx( hdc, oldOrigin );
	SetWindowOrgEx( hdc, oldOrigin->x + clientOrigin.x, oldOrigin->y + clientOrigin.y, oldOrigin );
	return hdc;
}