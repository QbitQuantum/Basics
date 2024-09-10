DWORD CViewGame::SetFullScreen()
{
    HRESULT             ddrval;
    ddrval = DirectDrawCreate( NULL, &FrontDD, NULL );
	if (ddrval)
		return GERR_DD;
    ddrval = FrontDD->SetCooperativeLevel(m_hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT);
	if (ddrval)
		return GERR_DDCL;
	ddrval = FrontDD->SetDisplayMode( 640, 480, 16 );
	if (ddrval)
		return GERR_DDDM;
	return 0;
}