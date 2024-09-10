BOOL CEditRoadLineDlg::InitDX()
{
	if(FAILED(DirectDrawCreateEx(NULL, (void**)&m_lpdds, IID_IDirectDraw7, NULL)))
	{
		return FALSE;
	}
	if(FAILED(m_lpdds->SetCooperativeLevel(GetDlgItem(IDC_STATIC_MAP)->GetSafeHwnd(), DDSCL_NORMAL)))
	{
		return FALSE;
	}
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.dwWidth = 1024;
	ddsd.dwHeight = 786;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	if(FAILED(m_lpdds->CreateSurface(&ddsd, &m_lpBack, NULL)))
	{
		return FALSE;
	}
	m_fExit = FALSE;
	m_hMainThread = CreateThread(NULL, 0, MainThread, this, 0, NULL);
	if(m_hMainThread == INVALID_HANDLE_VALUE)
	{
		OnCancel();
		return FALSE;
	}
	return TRUE;
}