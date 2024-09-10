WSERR WSurface::Create(HWND hWnd,WCanvas &canvas)
{
	if (data->ddraw) return WS_CREATEDDRAWFAIL;

	if (DirectDrawCreate(NULL,&(data->ddraw),NULL)!=DD_OK) {
		return WS_CREATEDDRAWFAIL;
	}
	LPDIRECTDRAW lpDD=data->ddraw;
    lpDD->SetCooperativeLevel(hWnd,DDSCL_NORMAL);

	lpDD->CreateClipper(0,&(data->clipper),0);
	data->clipper->SetHWnd(0,hWnd);

	m_hWnd=hWnd;
	Canvas=&canvas;
	data->window_style=::GetWindowLong(m_hWnd,GWL_STYLE);
	::GetWindowRect(m_hWnd,&(data->window_rect));

	return CreateSurface();
}